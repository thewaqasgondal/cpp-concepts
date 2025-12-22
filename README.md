# C++ Cheatsheet

A comprehensive reference guide for C++ programming concepts, syntax, and best practices.

## Table of Contents

1. [Basics](#basics)
2. [Data Types](#data-types)
3. [Control Flow](#control-flow)
4. [Functions](#functions)
5. [Arrays and Vectors](#arrays-and-vectors)
6. [Pointers and References](#pointers-and-references)
7. [Strings](#strings)
8. [Object-Oriented Programming](#object-oriented-programming)
9. [Memory Management](#memory-management)
10. [Standard Library](#standard-library)
11. [Advanced Topics](#advanced-topics)
12. [Examples](#examples)

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
- **oop/oop_demo.cpp** - Classes, inheritance, polymorphism, and encapsulation
- **memory_management/memory_demo.cpp** - Dynamic allocation and smart pointers
- **stl/stl_demo.cpp** - Standard Template Library containers and algorithms
- **advanced/concurrency/concurrency_demo.cpp** - Threads, condition_variable, and producer/consumer example
- **advanced/modern_cpp/modern_cpp_demo.cpp** - Move semantics, smart pointers, and RVO demonstration
- **advanced/templates/templates_demo.cpp** - C++20/C++23 concepts, type traits, and constexpr examples
- **advanced/dsa/dsa_demo.cpp** - Data structures & algorithms: BFS, DFS, and Dijkstra

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

**Last Updated:** December 13, 2025