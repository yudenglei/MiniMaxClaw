# gRPC Demo

Modern C++ gRPC service using CMake.

## Features

- Modern CMake (3.16+)
- C++20
- gRPC with Protocol Buffers
- All RPC types: Unary, Server Streaming, Client Streaming, Bidirectional Streaming

## Requirements

- CMake >= 3.16
- C++20 compatible compiler
- Protobuf
- gRPC

### Install Dependencies

**Ubuntu/Debian:**
```bash
apt install cmake build-essential libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc
```

**macOS:**
```bash
brew install cmake protobuf grpc
```

**Or build from source:**
```bash
# See https://github.com/grpc/grpc for build instructions
```

## Build

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . -j$(nproc)
```

## Run

**Start Server:**
```bash
./server
# Server listening on 0.0.0.0:50051
```

**Run Client (in another terminal):**
```bash
./client [localhost:50051]
```

## Example Output

```
=== gRPC Demo Client ===
Connecting to localhost:50051

--- Unary RPCs ---
Add(10, 5) = 15
Multiply(10, 5) = 50

--- Server Streaming RPC ---
Range(1, 5): 1 2 3 4 5 

--- Client Streaming RPC ---
Sum([1, 2, 3, 4, 5]) = 15

--- Bidirectional Streaming RPC ---
10 + 5 = 15
10 - 5 = 5
10 * 5 = 50
10 / 5 = 2
```

## Project Structure

```
grpc-demo/
├── CMakeLists.txt
├── proto/
│   └── math.proto       # Protocol Buffers definition
└── src/
    ├── server.cpp        # gRPC server
    ├── client.cpp        # gRPC client
    ├── math_service_impl.h
    └── math_service_impl.cpp
```

## API Definition

| Method | Type | Description |
|--------|------|-------------|
| Add | Unary | a + b |
| Multiply | Unary | a * b |
| Range | Server Stream | Generate range [start, end] |
| Sum | Client Stream | Sum all values |
| Compute | Bidirectional Stream | Perform multiple operations |

## Protocol Buffers

The `math.proto` file defines the service and messages. Code is generated using:
```bash
protoc --grpc_out=. --cpp_out=. -I. proto/math.proto
```
