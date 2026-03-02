# MiniMaxClaw

Modern C++ demos with CMake, pybind11, and gRPC.

## Projects

### 1. pybind11-demo
Python bindings for modern C++ using pybind11.

- Modern CMake + pybind11
- C++20
- Python extension module
- pytest testing

**Quick Start:**
```bash
cd pybind11-demo
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
python -m pytest ../tests/ -v
```

### 2. grpc-demo
gRPC service with all RPC types.

- Modern CMake + gRPC
- C++20
- Protocol Buffers
- Unary, Server Streaming, Client Streaming, Bidirectional Streaming

**Quick Start:**
```bash
cd grpc-demo
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Terminal 1: Start server
./server

# Terminal 2: Run client
./client
```

## Requirements

- CMake >= 3.15
- C++20 compatible compiler
- Python 3.8+ (for pybind11-demo)
- pybind11 (for pybind11-demo)
- gRPC + Protobuf (for grpc-demo)

## License

MIT
