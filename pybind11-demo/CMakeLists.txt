cmake_minimum_required(VERSION 3.15)
project(pybind11_demo VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find pybind11
find_package(pybind11 REQUIRED)

# Python version
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')"
    OUTPUT_VARIABLE PYTHON_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Demo library
add_library(mylib STATIC
    src/math_utils.cpp
    src/math_utils.h
)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Python binding
pybind11_add_module(pymylib 
    src/binding.cpp
)
target_link_libraries(pymylib PRIVATE mylib)

# Installation
install(TARGETS pymylib LIBRARY DESTINATION ${PYTHON_INSTALL_DIR})

# Tests
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_test(NAME test_mylib 
    COMMAND ${Python3_EXECUTABLE} -m pytest tests/ -v
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
