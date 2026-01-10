# C++ Cheatsheet

[![C++](https://img.shields.io/badge/C%2B%2B-17/20/23-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.10+-blue.svg)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![CI](https://github.com/thewaqasgondal/cpp-concepts/workflows/CI/badge.svg)](https://github.com/thewaqasgondal/cpp-concepts/actions)

A comprehensive reference guide for C++ programming concepts, syntax, and best practices.

## Table of Contents

1. [Basics](#basics)
2. [Data Types](#data-types)
3. [Control Flow](#control-flow)
4. [Functions](#functions)
5. [Arrays and Vectors](#arrays-and-vectors)
6. [Pointers and References](#pointers-and-references)
7. [Strings](#strings)
8. [Templates](#templates)
9. [Exception Handling](#exception-handling)
10. [Object-Oriented Programming](#object-oriented-programming)
11. [Memory Management](#memory-management)
12. [Standard Library](#standard-library)
13. [Modern C++ Features](#modern-c-features)
14. [File I/O](#file-io)
15. [Concurrency](#concurrency)
16. [Move Semantics](#move-semantics)
17. [Algorithms](#algorithms)
18. [Design Patterns](#design-patterns)
19. [Serialization](#serialization)
20. [Memory Pools](#memory-pools)
21. [Template Metaprogramming](#template-metaprogramming)
22. [Performance Optimization](#performance-optimization)
23. [Plugin System](#plugin-system)
24. [Coroutines](#coroutines)
25. [Concepts](#concepts)
26. [Ranges](#ranges)
27. [Parallel Algorithms](#parallel-algorithms)
28. [SIMD Operations](#simd-operations)
29. [Advanced Topics](#advanced-topics)
30. [Examples](#examples)

---

## Examples

This repository includes runnable C++ examples for each major concept. The examples are organized in the `examples/` directory.

### Building and Running Examples

#### Using Make (Recommended)
```bash
# Build all examples
make

# Build specific example
make examples/basics/hello_world

# Run all examples
make run-all

# Clean build artifacts
make clean
```

#### Using CMake
```bash
# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run examples from build directory
./examples/basics/hello_world
./examples/data_types/data_types_demo
# ... etc
```

### Available Examples

- **basics/hello_world.cpp** - Basic "Hello World" program
- **data_types/data_types_demo.cpp** - Demonstrates all primitive data types
- **control_flow/control_flow_demo.cpp** - Shows all control flow statements
- **functions/functions_demo.cpp** - Function declarations, overloading, and recursion
- **arrays_vectors/arrays_vectors_demo.cpp** - Arrays and dynamic vectors
- **pointers_references/pointers_references_demo.cpp** - Pointers, references, and memory addressing
- **strings/strings_demo.cpp** - String operations, manipulation, and algorithms
- **templates/templates_demo.cpp** - Function and class templates, specialization
- **exceptions/exceptions_demo.cpp** - Exception handling, custom exceptions, RAII
- **oop/oop_demo.cpp** - Classes, inheritance, polymorphism, and encapsulation
- **memory_management/memory_demo.cpp** - Dynamic allocation and smart pointers
- **stl/stl_demo.cpp** - Standard Template Library containers and algorithms
- **advanced/concurrency/concurrency_demo.cpp** - Threads, condition_variable, and producer/consumer example
- **advanced/modern_cpp/modern_cpp_demo.cpp** - Move semantics, smart pointers, and RVO demonstration
- **advanced/templates/templates_demo.cpp** - C++20/C++23 concepts, type traits, and constexpr examples
- **advanced/dsa/dsa_demo.cpp** - Data structures & algorithms: BFS, DFS, and Dijkstra
- **modern_cpp/modern_cpp_demo.cpp** - Modern C++ features (auto, lambdas, smart pointers, etc.)
- **file_io/file_io_demo.cpp** - File input/output operations and filesystem library
- **concurrency/concurrency_demo.cpp** - Threading, mutexes, condition variables, futures
- **move_semantics/move_semantics_demo.cpp** - Rvalue references and move semantics
- **algorithms/algorithms_demo.cpp** - Advanced STL algorithms (sorting, searching, modifying)
- **design_patterns/design_patterns_demo.cpp** - Common design patterns (Singleton, Factory, Observer, etc.)
- **serialization/serialization_demo.cpp** - Data serialization (JSON, binary, XML, CSV)
- **memory_pools/memory_pools_demo.cpp** - Custom memory allocators, object pools, and arena allocation
- **template_metaprogramming/template_metaprogramming_demo.cpp** - Type traits, SFINAE, constexpr, and expression templates
- **performance_optimization/performance_optimization_demo.cpp** - Cache-friendly code, branch prediction, and profiling
- **plugin_system/plugin_system_demo.cpp** - Dynamic plugin loading and management system
- **coroutines/modern_coroutines_demo.cpp** - C++20 coroutines, generators, async tasks, and cooperative multitasking
- **concepts/concepts_demo.cpp** - C++20 concepts for template constraints and better error messages
- **ranges/ranges_demo.cpp** - C++20 ranges for functional-style programming and lazy evaluation
- **parallel_algorithms/parallel_algorithms_demo.cpp** - C++17 parallel algorithms with execution policies
- **simd_operations/simd_operations_demo.cpp** - SIMD operations, vectorization, and performance optimization

Each example includes detailed comments explaining the concepts being demonstrated.

---

## Basics

### Hello World
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

### Comments
```cpp
// Single-line comment
/* Multi-line
   comment */
```

---

## Data Types

### Primitive Types
```cpp
int age = 25;              // Integer (-2^31 to 2^31-1)
unsigned int count = 100;  // Unsigned integer (0 to 2^32-1)
float pi = 3.14f;          // Single precision floating point
double gravity = 9.8;      // Double precision floating point
char letter = 'A';         // Single character
bool isTrue = true;        // Boolean (true/false)
```

### Const and Static
```cpp
const int MAX_SIZE = 100;  // Constant value
static int counter = 0;    // Static variable (persistent)
```

---

## Control Flow

### If-Else
```cpp
if (x > 10) {
    cout << "x is greater than 10" << endl;
} else if (x == 10) {
    cout << "x equals 10" << endl;
} else {
    cout << "x is less than 10" << endl;
}
```

### Switch Statement
```cpp
switch (day) {
    case 1:
        cout << "Monday" << endl;
        break;
    case 2:
        cout << "Tuesday" << endl;
        break;
    default:
        cout << "Unknown day" << endl;
}
```

### Loops
```cpp
// For loop
for (int i = 0; i < 10; i++) {
    cout << i << endl;
}

// While loop
while (condition) {
    // code
}

// Do-While loop
do {
    // code
} while (condition);

// Range-based for loop (C++11)
for (int num : {1, 2, 3, 4, 5}) {
    cout << num << endl;
}
```

---

## Functions

### Function Declaration and Definition
```cpp
// Declaration
int add(int a, int b);

// Definition
int add(int a, int b) {
    return a + b;
}

// Function with default parameters
void greet(string name = "World") {
    cout << "Hello, " << name << endl;
}

// Function overloading
int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}
```

### Inline Functions
```cpp
inline int square(int x) {
    return x * x;
}
```

---

## Arrays and Vectors

### Arrays
```cpp
int arr[5] = {1, 2, 3, 4, 5};  // Fixed-size array
int arr2[] = {10, 20, 30};     // Size inferred from initialization
int matrix[3][3];              // 2D array
```

### Vectors (Dynamic Arrays)
```cpp
#include <vector>

vector<int> v;          // Empty vector
vector<int> v(5, 10);   // Vector with 5 elements, all initialized to 10

// Common vector operations
v.push_back(20);        // Add element at end
v.pop_back();           // Remove last element
v.size();               // Get size
v.empty();              // Check if empty
v[0];                   // Access element
v.at(0);                // Safe access with bounds checking
v.clear();              // Remove all elements

// Iteration
for (int num : v) {
    cout << num << endl;
}
```

---

## Pointers and References

### Pointers
```cpp
int x = 10;
int* ptr = &x;         // Pointer to x

cout << *ptr;          // Dereference: prints 10
cout << ptr;           // Address of x

int* ptr2 = nullptr;   // Null pointer

// Pointer arithmetic
int arr[5] = {1, 2, 3, 4, 5};
int* p = arr;
p++;                   // Points to arr[1]
*(p + 2);              // Access arr[3]
```

### References
```cpp
int x = 10;
int& ref = x;          // Reference to x

ref = 20;              // x is now 20
cout << &ref;          // Same address as x

// References in functions
void increment(int& num) {
    num++;
}
```

### Const Pointers
```cpp
const int* ptr1;       // Pointer to const int (can change pointer, not value)
int* const ptr2;       // Const pointer to int (can change value, not pointer)
const int* const ptr3; // Const pointer to const int
```

---

## Strings

### String Basics
```cpp
#include <string>

string str1 = "Hello";
string str2 = "World";
string str3 = str1 + " " + str2;  // Concatenation

// String operations
str1.length();         // Get length
str1.substr(0, 3);     // Substring
str1.find("ll");       // Find substring
str1.replace(0, 2, "Hi");  // Replace
str1[0];               // Access character
```

### String Comparison
```cpp
if (str1 == str2) {
    cout << "Strings are equal" << endl;
}

str1.compare(str2);    // Returns 0 if equal, <0 or >0 if different
```

---

## Templates

### Function Templates
```cpp
// Function template
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Usage
int maxInt = maximum(5, 10);
double maxDouble = maximum(3.14, 2.71);
```

### Class Templates
```cpp
template <typename T>
class Container {
private:
    T data;
public:
    void set(T val) { data = val; }
    T get() { return data; }
};

// Usage
Container<int> intContainer;
Container<string> stringContainer;
```

### Template Specialization
```cpp
template <>
class Container<string> {
    // Specialized implementation for strings
};
```

---

## Exception Handling

### Basic Try-Catch
```cpp
try {
    // Code that may throw exceptions
    if (denominator == 0) {
        throw runtime_error("Division by zero");
    }
} catch (const runtime_error& e) {
    cout << "Error: " << e.what() << endl;
}
```

### Multiple Catch Blocks
```cpp
try {
    // Risky code
} catch (const invalid_argument& e) {
    // Handle invalid arguments
} catch (const out_of_range& e) {
    // Handle out of range errors
} catch (const exception& e) {
    // Handle any other standard exceptions
} catch (...) {
    // Handle any exception
}
```

### Custom Exceptions
```cpp
class MyException : public exception {
public:
    const char* what() const noexcept override {
        return "My custom error message";
    }
};
```

---

## Object-Oriented Programming

### Class Definition
```cpp
class Person {
private:
    string name;
    int age;

public:
    // Constructor
    Person(string n, int a) : name(n), age(a) {}

    // Destructor
    ~Person() {}

    // Getter and Setter
    string getName() const {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    // Method
    void display() {
        cout << name << " is " << age << " years old" << endl;
    }
};

// Using the class
Person p("John", 30);
p.display();
```

### Inheritance
```cpp
class Animal {
public:
    virtual void sound() {
        cout << "Some sound" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        cout << "Woof!" << endl;
    }
};

Dog dog;
dog.sound();  // Prints "Woof!"
```

### Polymorphism
```cpp
void makeSound(Animal& animal) {
    animal.sound();  // Calls appropriate method based on object type
}
```

### Encapsulation
```cpp
class BankAccount {
private:
    double balance;

public:
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    double getBalance() const {
        return balance;
    }
};
```

---

## Memory Management

### Dynamic Memory Allocation
```cpp
// Using new
int* ptr = new int;
int* arr = new int[10];

// Delete to free memory
delete ptr;
delete[] arr;

ptr = nullptr;  // Good practice
```

### Smart Pointers (C++11+)
```cpp
#include <memory>

// unique_ptr - exclusive ownership
unique_ptr<int> ptr1(new int(10));
// or
auto ptr2 = make_unique<int>(10);

// shared_ptr - shared ownership
shared_ptr<int> ptr3 = make_shared<int>(20);
shared_ptr<int> ptr4 = ptr3;  // Both point to same memory

// Automatic cleanup when out of scope
```

---

## Standard Library

### Containers
```cpp
#include <map>
#include <set>
#include <queue>
#include <stack>

// Map
map<string, int> m;
m["apple"] = 5;
cout << m["apple"];

// Set (unique elements)
set<int> s = {1, 2, 3, 3, 4};  // Only {1, 2, 3, 4}

// Queue (FIFO)
queue<int> q;
q.push(10);
q.front();
q.pop();

// Stack (LIFO)
stack<int> st;
st.push(10);
st.top();
st.pop();
```

### Algorithms
```cpp
#include <algorithm>

vector<int> v = {5, 2, 8, 1, 9};

// Sorting
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>());  // Descending

// Finding
auto it = find(v.begin(), v.end(), 8);

// For each
for_each(v.begin(), v.end(), [](int x) {
    cout << x << " ";
});
```

### File I/O
```cpp
#include <fstream>

// Write to file
ofstream outfile("output.txt");
outfile << "Hello, File!" << endl;
outfile.close();

// Read from file
ifstream infile("output.txt");
string line;
while (getline(infile, line)) {
    cout << line << endl;
}
infile.close();
```

---

## Modern C++ Features

### Auto and Decltype
```cpp
auto x = 42;        // int
auto y = 3.14;      // double
decltype(x) z = x;  // int (same type as x)
```

### Lambdas
```cpp
auto add = [](int a, int b) { return a + b; };
auto result = add(5, 3);  // result = 8
```

### Smart Pointers
```cpp
auto ptr = make_unique<int>(42);
auto shared = make_shared<string>("hello");
```

---

## File I/O

### Text File Operations
```cpp
// Writing
ofstream outfile("file.txt");
outfile << "Hello, World!" << endl;

// Reading
ifstream infile("file.txt");
string line;
while (getline(infile, line)) {
    cout << line << endl;
}
```

### Binary File Operations
```cpp
vector<int> data = {1, 2, 3, 4, 5};
ofstream binfile("data.bin", ios::binary);
binfile.write(reinterpret_cast<const char*>(data.data()),
              data.size() * sizeof(int));
```

---

## Concurrency

### Threads
```cpp
thread t([]() {
    cout << "Hello from thread!" << endl;
});
t.join();
```

### Mutex
```cpp
mutex mtx;
int shared_data = 0;

void worker() {
    lock_guard<mutex> lock(mtx);
    shared_data++;
}
```

### Futures
```cpp
auto future = async([]() { return 42; });
int result = future.get();
```

---

## Move Semantics

### Rvalue References
```cpp
int&& rref = 42;  // rvalue reference
string&& str_ref = string("temp");  // rvalue reference
```

### Move Constructor
```cpp
class MyClass {
    MyClass(MyClass&& other) noexcept {
        // Move resources from other
        data = other.data;
        other.data = nullptr;
    }
};
```

### std::move
```cpp
string s1 = "hello";
string s2 = move(s1);  // s1 is now empty
```

---

## Algorithms

### Non-modifying Algorithms
```cpp
vector<int> nums = {1, 2, 3, 4, 5};

// Check if all elements satisfy condition
bool all_even = all_of(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });

// Check if any element satisfies condition
bool has_even = any_of(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });

// Check if no elements satisfy condition
bool none_even = none_of(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });

// Count elements
int count_even = count_if(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
```

### Modifying Algorithms
```cpp
vector<int> nums = {1, 2, 3, 4, 5};
vector<int> result;

// Transform elements
transform(nums.begin(), nums.end(), back_inserter(result), [](int x) { return x * 2; });

// Copy elements
vector<int> copy;
copy_if(nums.begin(), nums.end(), back_inserter(copy), [](int x) { return x > 3; });
```

### Sorting Algorithms
```cpp
vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

// Sort in ascending order
sort(nums.begin(), nums.end());

// Sort in descending order
sort(nums.rbegin(), nums.rend());

// Stable sort (preserves relative order of equal elements)
stable_sort(nums.begin(), nums.end());

// Partial sort (sort first n elements)
partial_sort(nums.begin(), nums.begin() + 3, nums.end());
```

---

## Design Patterns

### Singleton Pattern
```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};
```

### Factory Pattern
```cpp
class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override { cout << "Drawing circle" << endl; }
};

class ShapeFactory {
public:
    static Shape* createShape(const string& type) {
        if (type == "circle") return new Circle();
        return nullptr;
    }
};
```

### Observer Pattern
```cpp
class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    vector<Observer*> observers;

public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void notify() {
        for (auto obs : observers) {
            obs->update();
        }
    }
};
```

---

## Serialization

### JSON Serialization
```cpp
// Simple JSON-like structure
struct Person {
    string name;
    int age;
    vector<string> hobbies;
};

// Serialize to JSON string
string toJson(const Person& p) {
    return "{\"name\":\"" + p.name + "\",\"age\":" + to_string(p.age) + "}";
}

// Deserialize from JSON (simplified)
Person fromJson(const string& json) {
    // Parse JSON string...
    return Person{"John", 30, {"reading"}};
}
```

### Binary Serialization
```cpp
// Serialize data to binary file
void serialize(ofstream& out, const Person& p) {
    size_t nameSize = p.name.size();
    out.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
    out.write(p.name.c_str(), nameSize);
    out.write(reinterpret_cast<const char*>(&p.age), sizeof(p.age));
}

// Deserialize from binary file
void deserialize(ifstream& in, Person& p) {
    size_t nameSize;
    in.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    p.name.resize(nameSize);
    in.read(&p.name[0], nameSize);
    in.read(reinterpret_cast<char*>(&p.age), sizeof(p.age));
}
```

### XML Serialization
```cpp
string toXml(const Person& p) {
    string xml = "<person>\n";
    xml += "  <name>" + p.name + "</name>\n";
    xml += "  <age>" + to_string(p.age) + "</age>\n";
    xml += "</person>\n";
    return xml;
}
```

---

## Memory Pools

Custom memory allocation strategies for improved performance and memory usage patterns.

### Object Pool
```cpp
template<typename T>
class ObjectPool {
private:
    vector<T*> available;
    vector<T*> inUse;

public:
    T* acquire() {
        if (available.empty()) {
            return new T();
        }
        T* obj = available.back();
        available.pop_back();
        inUse.push_back(obj);
        return obj;
    }

    void release(T* obj) {
        auto it = find(inUse.begin(), inUse.end(), obj);
        if (it != inUse.end()) {
            inUse.erase(it);
            available.push_back(obj);
        }
    }
};
```

### Arena Allocator
```cpp
class ArenaAllocator {
private:
    vector<char*> blocks;
    char* currentBlock;
    size_t currentOffset;
    size_t blockSize;

public:
    ArenaAllocator(size_t blockSize = 4096) : blockSize(blockSize) {
        allocateBlock();
    }

    void* allocate(size_t size) {
        if (currentOffset + size > blockSize) {
            allocateBlock();
        }
        void* ptr = currentBlock + currentOffset;
        currentOffset += size;
        return ptr;
    }

    void reset() {
        currentOffset = 0;
    }
};
```

---

## Template Metaprogramming

Compile-time programming using C++ templates.

### Type Traits
```cpp
template<typename T>
struct is_pointer : false_type {};

template<typename T>
struct is_pointer<T*> : true_type {};
```

### Constexpr Functions
```cpp
constexpr unsigned long long factorial(unsigned int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}
```

### SFINAE
```cpp
template<typename T>
enable_if_t<is_integral_v<T>, void>
print_integral(const T& value) {
    cout << "Integral: " << value << endl;
}
```

---

## Performance Optimization

Techniques for writing high-performance C++ code.

### Cache-Friendly Data Structures
```cpp
// Array of Structures (AOS) - cache unfriendly
struct ParticleAOS {
    float x, y, z, vx, vy, vz, mass;
};

// Structure of Arrays (SOA) - cache friendly
struct ParticleSOA {
    vector<float> x, y, z;
    vector<float> vx, vy, vz;
    vector<float> mass;
};
```

### Branch Prediction Optimization
```cpp
// Branchy version (hard to predict)
if (x > 0) sum += x; else sum -= x;

// Branchless version (predictable)
int sign = (x > 0) ? 1 : -1;
sum += sign * abs(x);
```

---

## Plugin System

Dynamic loading of shared libraries at runtime.

### Plugin Interface
```cpp
class Plugin {
public:
    virtual ~Plugin() = default;
    virtual string getName() const = 0;
    virtual string getVersion() const = 0;
    virtual void execute() = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
};
```

### Plugin Manager
```cpp
class PluginManager {
private:
    unordered_map<string, void*> loadedLibraries;
    unordered_map<string, unique_ptr<Plugin>> loadedPlugins;

public:
    bool loadPlugin(const string& pluginName);
    bool unloadPlugin(const string& pluginName);
    bool executePlugin(const string& pluginName);
};
```

---

## Coroutines

C++20 feature for cooperative multitasking and asynchronous programming.

### Basic Coroutine
```cpp
#include <coroutine>
#include <iostream>

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task simpleCoroutine() {
    std::cout << "Coroutine started" << std::endl;
    co_await std::suspend_always{};
    std::cout << "Coroutine resumed" << std::endl;
}
```

### Generator Coroutine
```cpp
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        Generator get_return_object() { return {}; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> handle;
    // ... implementation
};

Generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        int temp = a;
        a = b;
        b = temp + b;
    }
}
```

---

## Concepts

C++20 feature for constraining template parameters.

### Basic Concepts
```cpp
#include <concepts>

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept Number = Integral<T> || FloatingPoint<T>;
```

### Constrained Templates
```cpp
template<Number T>
T add(T a, T b) {
    return a + b;
}

template<Integral T>
T multiply(T a, T b) {
    return a * b;
}
```

### Container Concept
```cpp
template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::iterator;
    { t.begin() } -> std::same_as<typename T::iterator>;
    { t.end() } -> std::same_as<typename T::iterator>;
    { t.size() } -> std::integral;
};
```

---

## Ranges

C++20 feature for functional-style programming with sequences.

### Basic Range Operations
```cpp
#include <ranges>
#include <vector>
#include <algorithm>

std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Filter even numbers
auto even_numbers = numbers | std::views::filter([](int x) { return x % 2 == 0; });

// Transform to squares
auto squares = numbers | std::views::transform([](int x) { return x * x; });

// Chain operations
auto result = numbers
             | std::views::filter([](int x) { return x > 3; })
             | std::views::transform([](int x) { return x * 2; })
             | std::views::take(3);
```

### Range Algorithms
```cpp
#include <ranges>

// Using ranges with algorithms
std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};

// Sort using ranges
std::ranges::sort(data);

// Find using ranges
auto found = std::ranges::find(data, 5);
```

---

## Parallel Algorithms

C++17 feature for parallel execution of standard algorithms.

### Execution Policies
```cpp
#include <execution>
#include <vector>
#include <algorithm>

std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};

// Sequential sort
std::sort(data.begin(), data.end());

// Parallel sort
std::sort(std::execution::par, data.begin(), data.end());

// Parallel unsequenced sort (may reorder operations)
std::sort(std::execution::par_unseq, data.begin(), data.end());
```

### Parallel Transform
```cpp
#include <execution>
#include <vector>
#include <algorithm>

std::vector<double> input = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> output(input.size());

// Parallel transform
std::transform(std::execution::par, input.begin(), input.end(), output.begin(),
               [](double x) { return std::sqrt(x); });
```

### Parallel Reduce
```cpp
#include <execution>
#include <vector>
#include <numeric>

std::vector<int> data(1000000, 1);

// Parallel sum
int sum = std::reduce(std::execution::par, data.begin(), data.end(), 0);
```

---

## SIMD Operations

Single Instruction, Multiple Data operations for performance.

### Compiler Vectorization
```cpp
#include <vector>

// This loop may be auto-vectorized by the compiler
void vector_add(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
    for (size_t i = 0; i < a.size(); ++i) {
        c[i] = a[i] + b[i];
    }
}
```

### Structure of Arrays (SoA)
```cpp
// Array of Structures (AoS) - may have cache misses
struct Particle_AoS {
    float x, y, z, mass;
};
std::vector<Particle_AoS> particles_aos;

// Structure of Arrays (SoA) - better for SIMD
struct Particles_SoA {
    std::vector<float> x, y, z, mass;
};
Particles_SoA particles_soa;
```

### Memory Alignment
```cpp
#include <cstdlib>

// Allocate aligned memory for SIMD operations
float* aligned_data = static_cast<float*>(std::aligned_alloc(32, size * sizeof(float)));
// Use aligned_data...
std::free(aligned_data);
```

### SIMD-Friendly Code
```cpp
// Branchless operations are SIMD-friendly
float branchless_abs(float x) {
    // Use bit manipulation instead of branching
    uint32_t bits = *reinterpret_cast<uint32_t*>(&x);
    bits &= 0x7FFFFFFF;  // Clear sign bit
    return *reinterpret_cast<float*>(&bits);
}
```

---

## Advanced Topics

### Templates
```cpp
// Function template
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Class template
template <typename T>
class Container {
private:
    T data;

public:
    void set(T val) { data = val; }
    T get() { return data; }
};

// Usage
Container<int> c;
c.set(42);
```

### Exception Handling
```cpp
try {
    if (denominator == 0) {
        throw invalid_argument("Denominator cannot be zero");
    }
    int result = numerator / denominator;
} catch (invalid_argument& e) {
    cout << "Error: " << e.what() << endl;
} catch (...) {
    cout << "Unknown error" << endl;
}
```

### Lambdas (C++11+)
```cpp
// Basic lambda
auto add = [](int a, int b) { return a + b; };
cout << add(3, 5);  // Prints 8

// Capturing variables
int x = 10;
auto multiply = [x](int y) { return x * y; };
cout << multiply(5);  // Prints 50

// Capture all by value [=] or by reference [&]
```

### Auto Keyword (C++11+)
```cpp
auto x = 42;           // int
auto y = 3.14;         // double
auto str = "hello";    // const char*
auto v = vector<int>{1, 2, 3};
```

### Range-based For Loop (C++11+)
```cpp
vector<int> v = {1, 2, 3, 4, 5};
for (auto num : v) {
    cout << num << endl;
}
```

---

## Quick Reference

### Operators
```cpp
// Arithmetic
+ - * / %

// Comparison
== != < > <= >=

// Logical
&& || !

// Bitwise
& | ^ ~ << >>

// Assignment
= += -= *= /= %=
```

### Escape Sequences
```cpp
\n  // Newline
\t  // Tab
\\  // Backslash
\"  // Double quote
\'  // Single quote
\0  // Null character
```

---

## Resources

- [cppreference.com](https://en.cppreference.com/) - Comprehensive C++ reference
- [C++ Standard](https://isocpp.org/) - Official C++ standards organization
- [Compiler Explorer](https://godbolt.org/) - Online C++ compiler

---

**Last Updated:** January 6, 2026