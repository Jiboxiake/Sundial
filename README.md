Sundial
=======

Sundial is a distributed OLTP database management system (DBMS). It supports a number of traditional/modern distributed concurrency control protocols, including WAIT_DIE, NO_WAIT, F1 (Google), MaaT, and TicToc. Sundial is implemented on top of [DBx1000](https://github.com/yxymit/DBx1000). 

My original gRPC implementation (cf144e7468389da95c5321b47fe0e322f1422f6d) is abandoned in favor of a cleaner version and more efficient version of gRPC implementation from https://github.com/ScarletGuo/Sundial/tree/grpc-20201008

The following two papers describe Sundial and DBx1000, respectively: 

[Sundial Paper](http://xiangyaoyu.net/pubs/sundial.pdf)  
Xiangyao Yu, Yu Xia, Andrew Pavlo, Daniel Sanchez, Larry Rudolph, Srinivas Devadas  
Sundial: Harmonizing Concurrency Control and Caching in a Distributed OLTP Database Management System  
VLDB 2018
    
[DBx1000 Paper](http://www.vldb.org/pvldb/vol8/p209-yu.pdf)  
Xiangyao Yu, George Bezerra, Andrew Pavlo, Srinivas Devadas, Michael Stonebraker  
Staring into the Abyss: An Evaluation of Concurrency Control with One Thousand Cores  
VLDB 2014
