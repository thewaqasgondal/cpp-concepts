cmake_minimum_required(VERSION 3.10)
project(CppConceptsExamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all example subdirectories
add_subdirectory(examples/basics)
add_subdirectory(examples/data_types)
add_subdirectory(examples/control_flow)
add_subdirectory(examples/functions)
add_subdirectory(examples/arrays_vectors)
add_subdirectory(examples/pointers_references)
add_subdirectory(examples/strings)
add_subdirectory(examples/templates)
add_subdirectory(examples/exceptions)
add_subdirectory(examples/oop)
add_subdirectory(examples/memory_management)
add_subdirectory(examples/stl)
add_subdirectory(examples/modern_cpp)
add_subdirectory(examples/file_io)
add_subdirectory(examples/concurrency)
add_subdirectory(examples/move_semantics)

# Add tests
add_subdirectory(test)