#include "math_service_impl.h"
#include <stdexcept>
#include <sstream>

namespace math {

::grpc::Status MathServiceImpl::Add(::grpc::ServerContext* context,
                                    const ::math::AddRequest* request,
                                    ::math::AddReply* response) {
    response->set_result(request->a() + request->b());
    return ::grpc::Status::OK;
}

::grpc::Status MathServiceImpl::Multiply(::grpc::ServerContext* context,
                                         const ::math::MultiplyRequest* request,
                                         ::math::MultiplyReply* response) {
    response->set_result(request->a() * request->b());
    return ::grpc::Status::OK;
}

::grpc::Status MathServiceImpl::Range(::grpc::ServerContext* context,
                                       const ::math::RangeRequest* request,
                                       ::grpc::ServerWriter<::math::RangeReply>* writer) {
    for (int64_t i = request->start(); i <= request->end(); ++i) {
        ::math::RangeReply reply;
        reply.set_value(i);
        writer->Write(reply);
    }
    return ::grpc::Status::OK;
}

::grpc::Status MathServiceImpl::Sum(::grpc::ServerContext* context,
                                     ::grpc::ServerReader<::math::SumRequest>* reader,
                                     ::math::SumReply* response) {
    ::math::SumRequest request;
    int64_t sum = 0;
    while (reader->Read(&request)) {
        sum += request.value();
    }
    response->set_result(sum);
    return ::grpc::Status::OK;
}

::grpc::Status MathServiceImpl::Compute(::grpc::ServerContext* context,
                                        ::grpc::ServerReaderWriter<::math::ComputeReply,
                                                                  ::math::ComputeRequest>* stream) {
    ::math::ComputeRequest request;
    while (stream->Read(&request)) {
        ::math::ComputeReply reply;
        
        switch (request.op()) {
            case ::math::ComputeRequest::ADD:
                reply.set_result(request.a() + request.b());
                reply.set_description(std::to_string(request.a()) + " + " + 
                                    std::to_string(request.b()));
                break;
            case ::math::ComputeRequest::SUBTRACT:
                reply.set_result(request.a() - request.b());
                reply.set_description(std::to_string(request.a()) + " - " + 
                                    std::to_string(request.b()));
                break;
            case ::math::ComputeRequest::MULTIPLY:
                reply.set_result(request.a() * request.b());
                reply.set_description(std::to_string(request.a()) + " * " + 
                                    std::to_string(request.b()));
                break;
            case ::math::ComputeRequest::DIVIDE:
                if (request.b() != 0) {
                    reply.set_result(request.a() / request.b());
                    reply.set_description(std::to_string(request.a()) + " / " + 
                                        std::to_string(request.b()));
                }
                break;
            default:
                break;
        }
        
        stream->Write(reply);
    }
    return ::grpc::Status::OK;
}

} // namespace math
