# pybind11 Demo

Modern C++ Python binding using pybind11 with CMake.

## Features

- Modern CMake (3.15+) with proper targets
- C++20
- pybind11 for Python bindings
- pytest for testing

## Requirements

- CMake >= 3.15
- C++20 compatible compiler
- Python >= 3.8
- pybind11

## Build

```bash
# Create build directory
mkdir build && cd build

# Configure (adjust Python version if needed)
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DPython3_EXECUTABLE=$(which python3)

# Build
cmake --build . -j$(nproc)

# Install (optional)
cmake --install . --prefix ~/.local
# Or pip install build directory
pip install .
```

## Usage

```python
import pymylib

# Create calculator instance
calc = pymylib.Calculator()

# Basic math
print(calc.add(1, 2))           # 3
print(calc.multiply(3, 4))      # 12

# Compute statistics
result = calc.compute_stats([1, 2, 3, 4, 5])
print(result.value)              # 3.0
print(result.description)        # mean=3.00, min=1.00, max=5.00

# Get version
print(pymylib.Calculator.version())  # 1.0.0
```

## Test

```bash
cd build
ctest --output-on-failure

# Or pytest directly
python -m pytest ../tests/ -v
```

## Project Structure

```
pybind11-demo/
├── CMakeLists.txt
├── src/
│   ├── math_utils.h      # Header file
│   ├── math_utils.cpp    # Implementation
│   └── binding.cpp      # pybind11 binding
└── tests/
    └── test_mylib.py     # Python tests
```
