# C++ Examples

This directory contains runnable C++ examples demonstrating key programming concepts.

## Directory Structure

```
examples/
├── basics/                 # Basic C++ programs
│   └── hello_world.cpp    # Simple "Hello World" program
├── data_types/            # Data types and variables
│   └── data_types_demo.cpp # All primitive types, const, static
├── control_flow/          # Control flow statements
│   └── control_flow_demo.cpp # if-else, switch, loops
├── functions/             # Functions and procedures
│   └── functions_demo.cpp # Function overloading, recursion, references
├── arrays_vectors/        # Arrays and dynamic arrays
│   └── arrays_vectors_demo.cpp # Static arrays, vectors, 2D arrays
├── pointers_references/   # Memory addressing
│   └── pointers_references_demo.cpp # Pointers, references, const pointers
├── oop/                   # Object-oriented programming
│   └── oop_demo.cpp       # Classes, inheritance, polymorphism
├── memory_management/     # Dynamic memory
│   └── memory_demo.cpp    # new/delete, smart pointers, RAII
└── stl/                   # Standard Template Library
    └── stl_demo.cpp       # Containers, algorithms, iterators
└── advanced/              # Advanced examples (concurrency, modern C++, templates)
    └── concurrency/
    └── modern_cpp/
    └── templates/
```

## Building

Use the provided Makefile in the root directory:

```bash
# Build all examples
make

# Build specific example
make examples/basics/hello_world

# Run all examples
make run-all
```

Or use CMake:

```bash
mkdir build && cd build
cmake ..
make
```

## Running Examples

Each example can be run directly after building:
./examples/advanced/concurrency/concurrency_demo
./examples/advanced/modern_cpp/modern_cpp_demo
./examples/advanced/templates/templates_demo

```bash
./examples/basics/hello_world
./examples/stl/stl_demo
```

## Learning Path

Start with the basics and progress through the directories in order:

1. **basics** - Get started with C++
2. **data_types** - Understand variables and types
3. **control_flow** - Learn program flow control
4. **functions** - Modular programming
5. **arrays_vectors** - Working with collections
6. **pointers_references** - Memory management basics
7. **oop** - Object-oriented design
8. **memory_management** - Advanced memory handling
9. **stl** - Standard library usage

Each example includes detailed comments explaining the concepts being demonstrated.