#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function template
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Function template with multiple parameters
template <typename T, typename U>
void printPair(T first, U second) {
    cout << "(" << first << ", " << second << ")" << endl;
}

// Class template
template <typename T>
class Container {
private:
    T data;

public:
    Container(T val) : data(val) {}

    void set(T val) { data = val; }
    T get() const { return data; }

    void display() const {
        cout << "Container holds: " << data << endl;
    }
};

// Template specialization
template <>
class Container<string> {
private:
    string data;

public:
    Container(string val) : data(val) {}

    void set(string val) { data = val; }
    string get() const { return data; }

    void display() const {
        cout << "String container holds: \"" << data << "\"" << endl;
    }

    size_t length() const { return data.length(); }
};

// Variadic template function
template <typename... Args>
void printAll(Args... args) {
    cout << "Arguments: ";
    ((cout << args << " "), ...);
    cout << endl;
}

// Template with non-type parameter
template <typename T, size_t N>
class Array {
private:
    T arr[N];

public:
    Array() {
        for (size_t i = 0; i < N; ++i) {
            arr[i] = T();
        }
    }

    T& operator[](size_t index) { return arr[index]; }
    const T& operator[](size_t index) const { return arr[index]; }

    size_t size() const { return N; }

    void display() const {
        cout << "Array: [";
        for (size_t i = 0; i < N; ++i) {
            cout << arr[i];
            if (i < N - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

void demonstrateFunctionTemplates() {
    cout << "=== Function Templates ===\n" << endl;

    cout << "maximum(5, 10): " << maximum(5, 10) << endl;
    cout << "maximum(3.14, 2.71): " << maximum(3.14, 2.71) << endl;
    cout << "maximum('a', 'z'): " << maximum('a', 'z') << endl;

    cout << "\nprintPair examples:" << endl;
    printPair(42, "hello");
    printPair(3.14, true);
    printPair("world", 100);
}

void demonstrateClassTemplates() {
    cout << "\n=== Class Templates ===\n" << endl;

    Container<int> intContainer(42);
    intContainer.display();

    Container<double> doubleContainer(3.14159);
    doubleContainer.display();

    Container<string> stringContainer("Hello, Templates!");
    stringContainer.display();
    cout << "String length: " << stringContainer.length() << endl;
}

void demonstrateVariadicTemplates() {
    cout << "\n=== Variadic Templates ===\n" << endl;

    printAll(1, 2, 3);
    printAll("apple", "banana", "cherry");
    printAll(1, "mixed", 3.14, true);
}

void demonstrateTemplateArrays() {
    cout << "\n=== Template Arrays ===\n" << endl;

    Array<int, 5> intArray;
    for (size_t i = 0; i < intArray.size(); ++i) {
        intArray[i] = static_cast<int>(i * 10);
    }
    intArray.display();

    Array<string, 3> stringArray;
    stringArray[0] = "Hello";
    stringArray[1] = "Template";
    stringArray[2] = "World";
    stringArray.display();
}

// Compile-time factorial using templates
template <unsigned int N>
struct factorial {
    static const unsigned int value = N * factorial<N - 1>::value;
};

template <>
struct factorial<0> {
    static const unsigned int value = 1;
};

void demonstrateTemplateMetaprogramming() {
    cout << "\n=== Template Metaprogramming ===\n" << endl;

    // Factorial at compile time
    cout << "Factorial examples (compile-time):" << endl;
    cout << "5! = " << factorial<5>::value << endl;
    cout << "3! = " << factorial<3>::value << endl;
    cout << "0! = " << factorial<0>::value << endl;
}

int main() {
    cout << "=== C++ Templates Demo ===\n" << endl;

    demonstrateFunctionTemplates();
    demonstrateClassTemplates();
    demonstrateVariadicTemplates();
    demonstrateTemplateArrays();
    demonstrateTemplateMetaprogramming();

    cout << "\n=== Summary ===" << endl;
    cout << "• Templates enable generic programming" << endl;
    cout << "• Function templates work with any type" << endl;
    cout << "• Class templates create generic classes" << endl;
    cout << "• Template specialization handles special cases" << endl;
    cout << "• Variadic templates accept variable arguments" << endl;
    cout << "• Non-type parameters allow compile-time constants" << endl;
    cout << "• Template metaprogramming enables compile-time computation" << endl;

    return 0;
}