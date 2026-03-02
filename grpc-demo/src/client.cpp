#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "math.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using math::AddRequest;
using math::AddReply;
using math::MultiplyRequest;
using math::MultiplyReply;
using math::RangeRequest;
using math::RangeReply;
using math::SumRequest;
using math::SumReply;
using math::ComputeRequest;
using math::ComputeReply;
using math::MathService;

class MathClient {
public:
    MathClient(std::shared_ptr<Channel> channel)
        : stub_(MathService::NewStub(channel)) {}
    
    // Unary RPC
    int64_t Add(int64_t a, int64_t b) {
        AddRequest request;
        request.set_a(a);
        request.set_b(b);
        
        AddReply reply;
        ClientContext context;
        
        Status status = stub_->Add(&context, request, &reply);
        
        if (status.ok()) {
            return reply.result();
        } else {
            std::cerr << "Add RPC failed: " << status.error_message() << std::endl;
            return 0;
        }
    }
    
    int64_t Multiply(int64_t a, int64_t b) {
        MultiplyRequest request;
        request.set_a(a);
        request.set_b(b);
        
        MultiplyReply reply;
        ClientContext context;
        
        Status status = stub_->Multiply(&context, request, &reply);
        
        if (status.ok()) {
            return reply.result();
        } else {
            std::cerr << "Multiply RPC failed: " << status.error_message() << std::endl;
            return 0;
        }
    }
    
    // Server streaming RPC
    void Range(int64_t start, int64_t end) {
        RangeRequest request;
        request.set_start(start);
        request.set_end(end);
        
        std::unique_ptr<grpc::ClientReader<RangeReply>> reader(
            stub_->Range(&context_, request, &reply_));
        
        RangeReply reply;
        std::cout << "Range(" << start << ", " << end << "): ";
        while (reader->Read(&reply)) {
            std::cout << reply.value() << " ";
        }
        std::cout << std::endl;
        
        Status status = reader->Finish();
        if (!status.ok()) {
            std::cerr << "Range RPC failed: " << status.error_message() << std::endl;
        }
    }
    
    // Client streaming RPC
    int64_t Sum(const std::vector<int64_t>& values) {
        ClientContext context;
        
        std::unique_ptr<grpc::ClientWriter<SumRequest>> writer(
            stub_->Sum(&context_, &reply_));
        
        for (int64_t v : values) {
            SumRequest request;
            request.set_value(v);
            if (!writer->Write(request)) {
                break;
            }
        }
        writer->WritesDone();
        
        Status status = writer->Finish();
        if (status.ok()) {
            return reply_.result();
        } else {
            std::cerr << "Sum RPC failed: " << status.error_message() << std::endl;
            return 0;
        }
    }
    
    // Bidirectional streaming RPC
    void Compute(const std::vector<std::tuple<ComputeRequest::Operation, int64_t, int64_t>>& ops) {
        ClientContext context;
        
        std::shared_ptr<grpc::ClientReaderWriter<ComputeReply, ComputeRequest>> stream(
            stub_->Compute(&context));
        
        for (const auto& [op, a, b] : ops) {
            ComputeRequest request;
            request.set_op(op);
            request.set_a(a);
            request.set_b(b);
            stream->Write(request);
            
            ComputeReply reply;
            if (stream->Read(&reply)) {
                std::cout << reply.description() << " = " << reply.result() << std::endl;
            }
        }
        
        stream->WritesDone();
        
        Status status = stream->Finish();
        if (!status.ok()) {
            std::cerr << "Compute RPC failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<MathService::Stub> stub_;
    ClientContext context_;
    SumReply reply_;
};

int main(int argc, char** argv) {
    // Create channel
    std::string target_addr = "localhost:50051";
    if (argc > 1) {
        target_addr = argv[1];
    }
    
    MathClient client(grpc::CreateChannel(
        target_addr, grpc::InsecureChannelCredentials()));
    
    std::cout << "=== gRPC Demo Client ===" << std::endl;
    std::cout << "Connecting to " << target_addr << std::endl;
    
    // Unary RPCs
    std::cout << "\n--- Unary RPCs ---" << std::endl;
    std::cout << "Add(10, 5) = " << client.Add(10, 5) << std::endl;
    std::cout << "Multiply(10, 5) = " << client.Multiply(10, 5) << std::endl;
    
    // Server streaming RPC
    std::cout << "\n--- Server Streaming RPC ---" << std::endl;
    client.Range(1, 5);
    
    // Client streaming RPC
    std::cout << "\n--- Client Streaming RPC ---" << std::endl;
    std::cout << "Sum([1, 2, 3, 4, 5]) = " << client.Sum({1, 2, 3, 4, 5}) << std::endl;
    
    // Bidirectional streaming RPC
    std::cout << "\n--- Bidirectional Streaming RPC ---" << std::endl;
    client.Compute({
        {ComputeRequest::ADD, 10, 5},
        {ComputeRequest::SUBTRACT, 10, 5},
        {ComputeRequest::MULTIPLY, 10, 5},
        {ComputeRequest::DIVIDE, 10, 5},
    });
    
    return 0;
}
