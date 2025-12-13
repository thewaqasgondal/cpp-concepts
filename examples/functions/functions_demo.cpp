#include <iostream>
using namespace std;

// Function declarations
int add(int a, int b);
void greet(string name = "World");
int multiply(int a, int b);
double multiply(double a, double b);
inline int square(int x);
int factorial(int n);  // Added declaration

// Function definitions
int add(int a, int b) {
    return a + b;
}

void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}

inline int square(int x) {
    return x * x;
}

// Function with reference parameter
void increment(int& num) {
    num++;
}

// Function returning reference
int& getElement(int arr[], int index) {
    return arr[index];
}

int main() {
    cout << "=== Functions Demo ===\n" << endl;

    // Basic function call
    cout << "1. Basic Function Call:" << endl;
    int result = add(5, 3);
    cout << "add(5, 3) = " << result << endl;

    // Function with default parameters
    cout << "\n2. Function with Default Parameters:" << endl;
    greet();           // Uses default parameter
    greet("Alice");    // Overrides default parameter

    // Function overloading
    cout << "\n3. Function Overloading:" << endl;
    cout << "multiply(3, 4) = " << multiply(3, 4) << endl;
    cout << "multiply(3.5, 2.0) = " << multiply(3.5, 2.0) << endl;

    // Inline function
    cout << "\n4. Inline Function:" << endl;
    cout << "square(5) = " << square(5) << endl;
    cout << "square(7) = " << square(7) << endl;

    // Pass by reference
    cout << "\n5. Pass by Reference:" << endl;
    int value = 10;
    cout << "Before increment: value = " << value << endl;
    increment(value);
    cout << "After increment: value = " << value << endl;

    // Returning reference
    cout << "\n6. Returning Reference:" << endl;
    int array[] = {10, 20, 30, 40, 50};
    cout << "Original array[2] = " << array[2] << endl;
    getElement(array, 2) = 99;  // Modify through reference
    cout << "After modification: array[2] = " << array[2] << endl;

    // Recursive function
    cout << "\n7. Recursive Function:" << endl;
    cout << "Factorial of 5 = " << factorial(5) << endl;

    return 0;
}

// Recursive function definition
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}