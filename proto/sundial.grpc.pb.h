// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: sundial.proto
#ifndef GRPC_sundial_2eproto__INCLUDED
#define GRPC_sundial_2eproto__INCLUDED

#include "sundial.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace sundial_rpc {

class SundialRPC final {
 public:
  static constexpr char const* service_full_name() {
    return "sundial_rpc.SundialRPC";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::sundial_rpc::SundialResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::sundial_rpc::SundialResponse>> AsynccontactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::sundial_rpc::SundialResponse>>(AsynccontactRemoteRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::sundial_rpc::SundialResponse>> PrepareAsynccontactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::sundial_rpc::SundialResponse>>(PrepareAsynccontactRemoteRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void contactRemote(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::sundial_rpc::SundialResponse* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void contactRemote(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::sundial_rpc::SundialResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void contactRemote(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::sundial_rpc::SundialResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::sundial_rpc::SundialResponse>* AsynccontactRemoteRaw(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::sundial_rpc::SundialResponse>* PrepareAsynccontactRemoteRaw(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::sundial_rpc::SundialResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::sundial_rpc::SundialResponse>> AsynccontactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::sundial_rpc::SundialResponse>>(AsynccontactRemoteRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::sundial_rpc::SundialResponse>> PrepareAsynccontactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::sundial_rpc::SundialResponse>>(PrepareAsynccontactRemoteRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response, std::function<void(::grpc::Status)>) override;
      void contactRemote(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::sundial_rpc::SundialResponse* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void contactRemote(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void contactRemote(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::sundial_rpc::SundialResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void contactRemote(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::sundial_rpc::SundialResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::sundial_rpc::SundialResponse>* AsynccontactRemoteRaw(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::sundial_rpc::SundialResponse>* PrepareAsynccontactRemoteRaw(::grpc::ClientContext* context, const ::sundial_rpc::SundialRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_contactRemote_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status contactRemote(::grpc::ServerContext* context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_contactRemote : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_contactRemote() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_contactRemote() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status contactRemote(::grpc::ServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestcontactRemote(::grpc::ServerContext* context, ::sundial_rpc::SundialRequest* request, ::grpc::ServerAsyncResponseWriter< ::sundial_rpc::SundialResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_contactRemote<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_contactRemote : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_contactRemote() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::sundial_rpc::SundialRequest, ::sundial_rpc::SundialResponse>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::sundial_rpc::SundialRequest* request, ::sundial_rpc::SundialResponse* response) { return this->contactRemote(context, request, response); }));}
    void SetMessageAllocatorFor_contactRemote(
        ::grpc::experimental::MessageAllocator< ::sundial_rpc::SundialRequest, ::sundial_rpc::SundialResponse>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::sundial_rpc::SundialRequest, ::sundial_rpc::SundialResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_contactRemote() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status contactRemote(::grpc::ServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* contactRemote(
      ::grpc::CallbackServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* contactRemote(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_contactRemote<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_contactRemote<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_contactRemote : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_contactRemote() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_contactRemote() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status contactRemote(::grpc::ServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_contactRemote : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_contactRemote() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_contactRemote() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status contactRemote(::grpc::ServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestcontactRemote(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_contactRemote : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_contactRemote() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->contactRemote(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_contactRemote() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status contactRemote(::grpc::ServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* contactRemote(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* contactRemote(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_contactRemote : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_contactRemote() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::sundial_rpc::SundialRequest, ::sundial_rpc::SundialResponse>(
            [this](::grpc_impl::ServerContext* context,
                   ::grpc_impl::ServerUnaryStreamer<
                     ::sundial_rpc::SundialRequest, ::sundial_rpc::SundialResponse>* streamer) {
                       return this->StreamedcontactRemote(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_contactRemote() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status contactRemote(::grpc::ServerContext* /*context*/, const ::sundial_rpc::SundialRequest* /*request*/, ::sundial_rpc::SundialResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedcontactRemote(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::sundial_rpc::SundialRequest,::sundial_rpc::SundialResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_contactRemote<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_contactRemote<Service > StreamedService;
};

}  // namespace sundial_rpc


#endif  // GRPC_sundial_2eproto__INCLUDED
