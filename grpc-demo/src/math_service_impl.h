#ifndef MATH_SERVICE_IMPL_H
#define MATH_SERVICE_IMPL_H

#include "math.grpc.pb.h"
#include <memory>
#include <vector>

namespace math {

class MathServiceImpl final : public MathService::Service {
public:
    // Unary RPCs
    ::grpc::Status Add(::grpc::ServerContext* context,
                        const ::math::AddRequest* request,
                        ::math::AddReply* response) override;
    
    ::grpc::Status Multiply(::grpc::ServerContext* context,
                            const ::math::MultiplyRequest* request,
                            ::math::MultiplyReply* response) override;
    
    // Server streaming RPC
    ::grpc::Status Range(::grpc::ServerContext* context,
                         const ::math::RangeRequest* request,
                         ::grpc::ServerWriter<::math::RangeReply>* writer) override;
    
    // Client streaming RPC
    ::grpc::Status Sum(::grpc::ServerContext* context,
                       ::grpc::ServerReader<::math::SumRequest>* reader,
                       ::math::SumReply* response) override;
    
    // Bidirectional streaming RPC
    ::grpc::Status Compute(::grpc::ServerContext* context,
                           ::grpc::ServerReaderWriter<::math::ComputeReply,
                                                    ::math::ComputeRequest>* stream) override;
};

} // namespace math

#endif // MATH_SERVICE_IMPL_H
