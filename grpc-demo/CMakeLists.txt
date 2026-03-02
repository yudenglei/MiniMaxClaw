cmake_minimum_required(VERSION 3.16)
project(grpc_demo VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find gRPC
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Generate proto files
# In your build, run: cmake --build . --target generate_proto
# Or include generated.cmake if using gRPC's CMake config

# Proto file
set(PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/proto/math.proto
)

# Generate C++ code from proto
set(PROTO_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(PROTO_SRCS ${PROTO_GENERATED_DIR}/math.pb.cc ${PROTO_GENERATED_DIR}/math.grpc.pb.cc)
set(PROTO_HDRS ${PROTO_GENERATED_DIR}/math.pb.h ${PROTO_GENERATED_DIR}/math.grpc.pb.h)

add_custom_command(
    OUTPUT ${PROTO_SRCS}
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS --grpc_out=${PROTO_GENERATED_DIR}
         --cpp_out=${PROTO_GENERATED_DIR}
         -I ${CMAKE_CURRENT_SOURCE_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/proto/math.proto
    DEPENDS ${PROTO_FILES}
    COMMENT "Generating gRPC C++ code from proto"
)

add_custom_target(generate_proto ALL DEPENDS ${PROTO_SRCS})

# Server
add_executable(server 
    src/server.cpp
    src/math_service_impl.cpp
    ${PROTO_SRCS}
)
target_link_libraries(server 
    PRIVATE 
    grpc::grpc++
    protobuf::libprotobuf
)

# Client
add_executable(client 
    src/client.cpp
    ${PROTO_SRCS}
)
target_link_libraries(client 
    PRIVATE 
    grpc::grpc++
    protobuf::libprotobuf
)

# Installation
install(TARGETS server client RUNTIME DESTINATION bin)
