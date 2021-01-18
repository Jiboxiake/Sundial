#include "row.h"
#include "txn.h"
#include "row_lock.h"
#include "manager.h"
#include "lock_manager.h"
#include "f1_manager.h"

#if CC_ALG == WAIT_DIE || CC_ALG == NO_WAIT || CC_ALG == WOUND_WAIT

#if CC_ALG == WAIT_DIE
bool Row_lock::Compare::operator()(const LockEntry &en1, const LockEntry &en2) const
{
    // returns true if the first argument goes before the second argument
    // begin(): txn with the largest ts (yongest)
    // end(): txn with the smallest ts (oldest)
    return en1.txn->_ts > en2.txn->_ts;
    //return true;
}
#endif

#if CC_ALG == WOUND_WAIT
bool Row_lock::Compare::operator()(const LockEntry &en1, const LockEntry &en2) const
{
    // returns true if the first argument goes before the second argument
    // begin(): txn with the smallest ts (oldest)
    // end(): txn with the largest ts (youngest)
    return en1.txn->_ts < en2.txn->_ts;
    //return true;
}
#endif

Row_lock::Row_lock()
{
    _row = NULL;
    pthread_mutex_init(&_latch, NULL);
    //_lock_type = LOCK_NONE;
    _max_num_waits = g_max_num_waits;
    _upgrading_txn = NULL;
}

Row_lock::Row_lock(row_t *row)
    : Row_lock()
{
    _row = row;
}

void Row_lock::latch()
{
    pthread_mutex_lock(&_latch);
}

void Row_lock::unlatch()
{
    pthread_mutex_unlock(&_latch);
}

void Row_lock::init(row_t *row)
{
    exit(0);
    _row = row;
    pthread_mutex_init(&_latch, NULL);
    _lock_type = LOCK_NONE;
    _max_num_waits = g_max_num_waits;
}
#if CC_ALG == WAIT_DIE
void Row_lock::wait(LockType type, TxnManager *txn)
{
    txn->_lock_ready = false;
    _waiting_set.insert(LockEntry{type, txn});
    unlatch();
    while (!txn->_lock_ready)
    {
        //spin wait
    }
    latch();
}
#endif
#if CC_ALG == WOUND_WAIT
//handles wound_wait, everything is done under latch
RC Row_lock::promote_wait()
{
    if (_waiting_set.empty())
    {
        return RCOK;
    }
    if (_locking_set.empty() || !conflict_lock(_waiting_set.begin()->type, _locking_set.begin()->type) || _waiting_set.begin()->txn->_ts <= _locking_set.begin()->txn->_ts)
    {
        std::set<LockEntry>::iterator head = _waiting_set.begin();
        head->txn->_lock_ready = true;
        _waiting_set.erase(head);
        //printf("wake up 1\n");
    }
    return RCOK;
}
RC Row_lock::promote_multiple()
{
    if (_waiting_set.empty())
    {
        return RCOK;
    }
    for (std::set<LockEntry>::iterator it = _waiting_set.begin(); it != _waiting_set.end(); it++)
    {
        //no conflict, can wake up
        if (!conflict_lock(it->type, _locking_set.begin()->type))
        {
            it->txn->_lock_ready = true;
            _waiting_set.erase(it);
            //printf("wake up multiple\n");
        }
        else
        {
            return RCOK;
        }
    }
    return RCOK;
}
#endif

RC Row_lock::lock_get(LockType type, TxnManager *txn, bool need_latch)
{
    RC rc = RCOK;
    //printf("grabing lock %p \n",this);
    if (txn == NULL)
    {
        assert(false);
    }
    if (need_latch)
        latch();
        //latch();
#if CC_ALG == NO_WAIT

    if (!_locking_set.empty())
    {
        if (_locking_set.begin()->type == LOCK_EX)
        {
            //only one can grab the ex lock
            // if(_locking_set.size()!=1){
            //printf("locking set size is %d \n",_locking_set.size());
            // assert(false);

            assert(_locking_set.size() == 1);
        }
    }
    LockEntry *entry = NULL;
    for (std::set<LockEntry>::iterator it = _locking_set.begin(); it != _locking_set.end(); it++)
        if (it->txn == txn)
            entry = (LockEntry *)&(*it);
    if (entry)
    { // the txn is alreayd a lock owner
        if (entry->type != type)
        {
            assert(type == LOCK_EX && entry->type == LOCK_SH);
            if (_locking_set.size() == 1)
                entry->type = type;
            else
                rc = ABORT;
        }
        else{
            //assert(false);
        }
    }
    else
    {
        if (!_locking_set.empty() && conflict_lock(type, _locking_set.begin()->type))
            rc = ABORT;
        else
            _locking_set.insert(LockEntry{type, txn});
    }
#elif CC_ALG == WAIT_DIE
    //check if txn already exists
    LockEntry *entry = NULL;
    for (std::set<LockEntry>::iterator it = _locking_set.begin(); it != _locking_set.end(); it++)
        if (it->txn == txn)
            entry = (LockEntry *)&(*it);
    if (entry)
    {
        if (entry->type != type)
        {
            assert(type == LOCK_EX && entry->type == LOCK_SH);
            //if current txn is the only txn holding a lock, just upgrade it
            if (_locking_set.size() == 1)
                entry->type = type;
            //if there are other txns holding the lock
            else
            {
                std::set<LockEntry>::iterator end = _locking_set.end();
                end--;
                assert(txn->_ts>= end->txn->_ts);
                assert(end->type==LOCK_SH);
                //if the txn is older than the oldest lock holder,wait
                if (txn->_ts== end->txn->_ts)
                {
                    
                    while (_locking_set.size() != 1)
                    {
                        wait(type,txn);
                    }
                    assert(_locking_set.begin()->txn == txn);
                    entry->type = type;
                }
                else
                {
                    rc=ABORT;
                }
            }
        }  
    }
    else
    { 
        if (_locking_set.empty() || !conflict_lock(type, _locking_set.begin()->type))
        {
            if(_locking_set.size()==1){
            std::set<LockEntry>::iterator begin = _locking_set.begin();
            std::set<LockEntry>::iterator end = _locking_set.end();
            end--;
            assert (begin==end);
            }
            //double check waiting set
            bool waited=false;
            if(!_waiting_set.empty()&&txn->_ts<_waiting_set.begin()->txn->_ts){
                if(_locking_set.empty()){
                    assert(_locking_set.begin()->type==LOCK_EX);
                }
                wait(type,txn);
                waited=true;
            }
            if(waited){
               rc=lock_get(type,txn,false);
            }else{
                _locking_set.insert(LockEntry{type, txn});
            }
        }else{
            bool waited=false;
            std::set<LockEntry>::iterator end = _locking_set.end();
            end--;
            TxnManager* end_txn=end->txn;
            assert(txn->_ts!=end->txn->_ts);
            //txn is older than the oldest lock holder, can wait
            if(txn->_ts<end_txn->_ts){
                wait(type,txn);
                waited=true;
            }else{
                rc=ABORT;
            }
            if(waited){
                rc=lock_get(type,txn,false);
            }
        }
        
    }

#elif CC_ALG == WOUND_WAIT
    if (txn->is_killed())
    {
        //printf("abort 1\n");
        if (need_latch)
            unlatch();
        return ABORT;
    }
    LockEntry entry = LockEntry{type, txn};
    pthread_cond_t local_cv;
    entry.cv = &local_cv;
    ///two situations you can just grab the lock
    if (_locking_set.size() == 0)
    {
        _locking_set.insert(entry);
        if (need_latch)
        {
            unlatch();
        }
        return RCOK;
    }
    //may need optimization, do we want to actively remove transactions or let them know they need to abort and release the lock
    //we also want to know if we want to kill transactions even though we have to wait first
    bool has_conflict = false;
    while (!_locking_set.empty() && conflict_lock(_locking_set.begin()->type, type))
    {
        has_conflict = false;
        if (txn->is_killed())
        {
            if (need_latch)
                unlatch();
            return ABORT;
        }
        if (_locking_set.size() == 1)
        {
            if (_locking_set.begin()->txn == txn)
            {
                assert(type == LOCK_EX);
                assert(_locking_set.begin()->type == LOCK_SH);
                std::set<LockEntry>::iterator head = _locking_set.begin();
                _locking_set.erase(head);
                _locking_set.insert(entry);
                assert(_locking_set.size() == 1);
                if (need_latch)
                {
                    unlatch();
                }
                return RCOK;
            }
        }
        for (std::set<LockEntry>::iterator it = _locking_set.begin();
             it != _locking_set.end(); it++)
        {
            if (conflict_lock(type, it->type))
            {
                has_conflict = true;
                txn->_lock_ready = false;
            }
            if (has_conflict && txn->_ts < it->txn->_ts)
            {
                //if trying to kill a committing transaction, abort yourself
                it->txn->latch();
                if (it->txn->is_protected())
                {
                    it->txn->unlatch();
                    if (need_latch)
                    {
                        unlatch();
                    }

                    return ABORT;
                }
                it->txn->wound();
                it->txn->unlatch();
            }
        }
        if (has_conflict)
        {
            _waiting_set.insert(entry);
            unlatch();

            //wait till conflicting ones release the lock
            while ((!txn->_lock_ready) && (!txn->is_killed()))
            {
                //just wait bro
            }

            //printf("get out of wait\n");
            latch();
        }
        if (txn->is_killed())
        {
            if (need_latch)
                unlatch();
            return ABORT;
        }
    }
    _locking_set.insert(entry);
    assert(!_locking_set.empty());
    //after inserting a new entry we can check if we can wake up more.
    promote_multiple();
#endif
    if (need_latch)
        unlatch();
    return rc;
}

RC Row_lock::lock_release(TxnManager *txn, RC rc)
{
    //printf("lock release\n");
    assert(rc == COMMIT || rc == ABORT);
    latch();
    //printf("txn %d is releasing %d\n",txn->get_txn_id(),this);
#if CC_ALG == NO_WAIT
    //printf("txn=%ld releases this=%ld\n", txn->get_txn_id(), (uint64_t)this);
    LockEntry entry = {LOCK_NONE, NULL};
    int flag = 0;
    for (std::set<LockEntry>::iterator it = _locking_set.begin();
         it != _locking_set.end(); it++)
    {
        if (it->txn == txn)
        {
            flag = 1;
            entry = *it;
            assert(entry.txn);
            _locking_set.erase(it);
            break;
        }
    }
    //assert(flag);
#if CONTROLLED_LOCK_VIOLATION
    // NOTE
    // entry.txn can be NULL. This happens because Row_lock manager locates in
    // each bucket of the hash index. Records with different keys may map to the
    // same bucket and therefore share the manager. They will all call lock_release()
    // during commit. Namely, one txn may call lock_release() multiple times on
    // the same Row_lock manager. For now, we simply ignore calls except the
    // first one.
    if (rc == COMMIT && entry.txn)
    {
        // DEBUG
        /*if (!entry.txn) {
            cout << "txn_id=" << txn->get_txn_id() << ", _row=" << (int64)_row << endl;
            for (auto en : _locking_set)
                cout << "en.txn_id=" << en.txn->get_txn_id() << ", en.type=" << en.type << endl;
        }
        assert(entry.txn);*/
        _weak_locking_queue.push_back(LockEntry{entry.type, txn});
        for (auto en : _weak_locking_queue)
        {
            if (en.txn == entry.txn)
                break;
            if (conflict_lock(entry.type, en.type))
            {
                // if the current txn has any pending dependency, incr_semaphore
                txn->dependency_semaphore->incr();
                break;
            }
        }
    }
#endif

#elif CC_ALG == WAIT_DIE
    int flag = 0;
    // remove from locking set
    for (std::set<LockEntry>::iterator it = _locking_set.begin();
         it != _locking_set.end(); it++)
    {
        if (it->txn == txn)
        {
            assert(it->txn->get_txn_id()==txn->get_txn_id());
            //entry = *it;
            //printf("found\n");
            _locking_set.erase(it);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("error\n");
    }
    //if waiting set is not empty, we can check if we can wake it up
    if (!_waiting_set.empty())
    {
        //printf("try to wake up!!!\n");
        //if locking set is empty or no conflict between waiting set's head and locking set's head
        if (_locking_set.empty() || !conflict_lock(_waiting_set.begin()->type, _locking_set.begin()->type))
        {
            //if waiting set's head is ex
            if (_waiting_set.begin()->type == LOCK_EX)
            {
                std::set<LockEntry>::iterator it = _waiting_set.begin();
                //wake 1 ex wait
                it->txn->_lock_ready=true;
                _waiting_set.erase(it);
            } //all we can wake up multiple SH lock threads
            else if (_waiting_set.begin()->type == LOCK_SH)
            {
                for (std::set<LockEntry>::iterator it = _waiting_set.begin(); it != _waiting_set.end(); it++)
                {
                    if (it->type == LOCK_SH)
                    {
                        it->txn->_lock_ready=true;
                        _waiting_set.erase(it);
                        //printf("return is %d\n",o);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }else if(_locking_set.size()==1&&_locking_set.begin()->txn==_waiting_set.begin()->txn){
            assert(_locking_set.begin()->type==LOCK_SH&&_waiting_set.begin()->type==LOCK_EX);
            std::set<LockEntry>::iterator it = _waiting_set.begin();
                //wake 1 ex wait
            it->txn->_lock_ready=true;
            _waiting_set.erase(it);
        }
    }
#elif CC_ALG == WOUND_WAIT
    int flag = 0;
    // remove from locking set
    for (std::set<LockEntry>::iterator it = _locking_set.begin();
         it != _locking_set.end(); it++)
    {
        assert(it->txn);
        if (it->txn == txn)
        {
            _locking_set.erase(it);
            flag = 1;
            break;
        }
    }
    assert(flag == 1);
    promote_wait();
    /*LockEntry entry {LOCK_NONE, NULL};
    // remove from locking set
    for (std::set<LockEntry>::iterator it = _locking_set.begin();
         it != _locking_set.end(); it ++)
        if (it->txn == txn) {
            entry = *it;
            _locking_set.erase(it);
            break;
        }

    #if CONTROLLED_LOCK_VIOLATION
    //if (_row && txn->get_txn_id() <= 5)
    //    printf("entry.txn=%lx, type=%d\n", (uint64_t)entry.txn, entry.type);
    if (rc == COMMIT) {
        assert(entry.txn);
        if (!_weak_locking_queue.empty())
            assert(_weak_locking_queue.front().type == LOCK_EX);
        if (!_weak_locking_queue.empty() || entry.type == LOCK_EX) {
            _weak_locking_queue.push_back( LockEntry {entry.type, txn} );
            // mark that the txn has one more unsolved dependency
            LockManager * lock_manager = (LockManager *) txn->get_cc_manager();
            lock_manager->increment_dependency();
            //if (_row)
            //    printf("txn %ld retires to weak queue. tuple=%ld\n", txn->get_txn_id(), _row->get_primary_key());
        }
    }
    #endif
    // remove from waiting set
    for (std::set<LockEntry>::iterator it = _waiting_set.begin();
         it != _waiting_set.end(); it ++)
        if (it->txn == txn) {
            _waiting_set.erase(it);
            break;
        }

    // try to upgrade LOCK_UPGRADING to LOCK_EX
    if (_locking_set.size() == 1 && _locking_set.begin()->type == LOCK_UPGRADING) {
        LockEntry * entry = (LockEntry *) &(*_locking_set.begin());
        entry->type = LOCK_EX;
        entry->txn->set_txn_ready(RCOK);
    }
    // try to move txns from waiting set to locking set
    bool done = false;
    while (!done) {
        std::set<LockEntry>::reverse_iterator rit = _waiting_set.rbegin();
        if (rit != _waiting_set.rend() &&
            (_locking_set.empty()
             || !conflict_lock(rit->type, _locking_set.begin()->type)))
        {
            _locking_set.insert( LockEntry {rit->type, rit->txn} );
            //if (_row && txn->get_txn_id() <= 5)
            //    printf("--txn %ld wakes up txn %ld\n", txn->get_txn_id(), rit->txn->get_txn_id());
            rit->txn->set_txn_ready(RCOK);
            //_waiting_set.erase( rit );
            _waiting_set.erase( --rit.base() );
        } else
            done = true;
    }*/
#endif

    unlatch();
    // printf("release return\n");
    return RCOK;
}

#if CONTROLLED_LOCK_VIOLATION
// In the current CLV architecture, if a txn calls lock_cleanup(), it must be
// the first txn in the _weak_locking_queue; we simply dequeue it.
// However, the complication comes when some readonly txns depend on a
// dequeueing txn. In this case, we need to check whether all the dependency
// information of the readonly txn has been cleared and commit it if so.
RC Row_lock::lock_cleanup(TxnManager *txn) //, std::set<TxnManager *> &ready_readonly_txns)
{
    latch();

    //assert(!_weak_locking_queue.empty());
    // Find the transaction in the _weak_locking_queue and remove it.
    auto it = _weak_locking_queue.begin();
    for (; it != _weak_locking_queue.end(); it++)
    {
        if (it->txn == txn)
            break;
    }
    // txn does not exist in the _weak_locking_queue when two index nodes map to
    // the same hash bucket. Only one entry is inserted into _weak_locking_queue.
    // Cleanup for the second index node will miss.
    if (it != _weak_locking_queue.end())
    {
        LockType type = it->type;
        if (type == LOCK_EX)
            assert(it == _weak_locking_queue.begin());
        if (type == LOCK_SH)
            for (auto it2 = _weak_locking_queue.begin(); it2 != it; it2++)
                assert(it2->type == LOCK_SH);
        _weak_locking_queue.erase(it);

        // notify dependent transactions
        // If the new leading lock is LOCK_EX, wake it up.
        // Else if the removed txn has LOCK_EX, wake up leading txns with LOCK_SH
        if (_weak_locking_queue.front().type == LOCK_EX)
            _weak_locking_queue.front().txn->dependency_semaphore->decr();
        else if (type == LOCK_EX)
        {
            for (auto entry : _weak_locking_queue)
            {
                if (entry.type == LOCK_SH)
                    entry.txn->dependency_semaphore->decr();
                else
                    break;
            }
        }
    }

    unlatch();
    return RCOK;
}
#endif

bool Row_lock::conflict_lock(LockType l1, LockType l2)
{
    if (l1 == LOCK_EX || l2 == LOCK_EX)
        return true;
    else if (l1 == LOCK_UPGRADING && l2 == LOCK_UPGRADING)
        return true;
    else
        return false;
}

#endif
