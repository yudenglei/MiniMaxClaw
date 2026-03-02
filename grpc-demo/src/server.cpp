#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "math.grpc.pb.h"
#include "math_service_impl.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using math::MathService;

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    
    math::MathServiceImpl service;
    
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    std::cout << "Press Ctrl+C to stop the server..." << std::endl;
    
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
