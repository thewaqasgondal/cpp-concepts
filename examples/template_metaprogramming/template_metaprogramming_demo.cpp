#include <iostream>
#include <type_traits>
#include <utility>
#include <string>
#include <vector>
#include <array>
using namespace std;

// ===== TYPE TRAITS AND SFINAE =====

// Custom type traits (using different names to avoid conflicts)
template<typename T>
struct my_is_pointer : false_type {};

template<typename T>
struct my_is_pointer<T*> : true_type {};

template<typename T>
struct my_is_pointer<T* const> : true_type {};

template<typename T>
struct my_is_pointer<T* volatile> : true_type {};

template<typename T>
struct my_is_pointer<T* const volatile> : true_type {};

// Check if a type is an array
template<typename T>
struct my_is_array : false_type {};

template<typename T, size_t N>
struct my_is_array<T[N]> : true_type {};

template<typename T>
struct my_is_array<T[]> : true_type {};

// ===== CONSTEXPR FUNCTIONS =====

// Factorial at compile time
constexpr unsigned long long factorial(unsigned int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

// Fibonacci at compile time
constexpr unsigned long long fibonacci(unsigned int n) {
    return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// Check if number is prime at compile time
constexpr bool is_prime(unsigned int n, unsigned int divisor = 2) {
    if (n < 2) return false;
    if (divisor * divisor > n) return true;
    if (n % divisor == 0) return false;
    return is_prime(n, divisor + 1);
}

// ===== SFINAE (Substitution Failure is Not An Error) =====

// Function that only accepts integral types
template<typename T>
enable_if_t<is_integral_v<T>, void>
print_integral(const T& value) {
    cout << "Integral: " << value << endl;
}

// Function that only accepts floating point types
template<typename T>
enable_if_t<is_floating_point_v<T>, void>
print_floating_point(const T& value) {
    cout << "Floating point: " << value << endl;
}

// Function that only accepts pointers
template<typename T>
enable_if_t<is_pointer_v<T>, void>
print_pointer(T ptr) {
    cout << "Pointer: " << ptr << " -> " << *ptr << endl;
}

// Generic fallback
template<typename T>
void print_value(const T& value) {
    cout << "Generic: " << value << endl;
}

// ===== TEMPLATE SPECIALIZATION =====

// Primary template
template<typename T>
struct TypeInfo {
    static string name() { return "Unknown"; }
    static size_t size() { return sizeof(T); }
};

// Specializations
template<>
struct TypeInfo<int> {
    static string name() { return "int"; }
    static size_t size() { return sizeof(int); }
};

template<>
struct TypeInfo<double> {
    static string name() { return "double"; }
    static size_t size() { return sizeof(double); }
};

template<>
struct TypeInfo<string> {
    static string name() { return "string"; }
    static size_t size() { return sizeof(string); }
};

template<typename T>
struct TypeInfo<T*> {
    static string name() { return TypeInfo<T>::name() + " pointer"; }
    static size_t size() { return sizeof(T*); }
};

template<typename T, size_t N>
struct TypeInfo<T[N]> {
    static string name() { return TypeInfo<T>::name() + " array[" + to_string(N) + "]"; }
    static size_t size() { return sizeof(T[N]); }
};

// ===== COMPILE-TIME COMPUTATIONS =====

// Sum of array elements at compile time
template<typename T, size_t N>
constexpr T array_sum(const array<T, N>& arr, size_t index = 0) {
    return index >= N ? T{} : arr[index] + array_sum(arr, index + 1);
}

// Check if all elements satisfy a condition
template<typename T, size_t N, typename Predicate>
constexpr bool all_of(const array<T, N>& arr, Predicate pred, size_t index = 0) {
    return index >= N ? true : (pred(arr[index]) && all_of(arr, pred, index + 1));
}

// ===== TYPE MANIPULATION =====

// Remove const qualifier
template<typename T>
struct my_remove_const {
    using type = T;
};

template<typename T>
struct my_remove_const<const T> {
    using type = T;
};

template<typename T>
using my_remove_const_t = typename my_remove_const<T>::type;

// Add const qualifier
template<typename T>
struct my_add_const {
    using type = const T;
};

template<typename T>
using my_add_const_t = typename my_add_const<T>::type;

// Remove reference
template<typename T>
struct my_remove_reference {
    using type = T;
};

template<typename T>
struct my_remove_reference<T&> {
    using type = T;
};

template<typename T>
struct my_remove_reference<T&&> {
    using type = T;
};

template<typename T>
using my_remove_reference_t = typename my_remove_reference<T>::type;

// ===== FUNCTION TRAITS =====
template<typename T>
struct function_traits;

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    using return_type = R;
    using args_tuple = tuple<Args...>;
    static constexpr size_t arity = sizeof...(Args);

    template<size_t N>
    using arg_type = tuple_element_t<N, args_tuple>;
};

template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> : function_traits<R(Args...)> {};

template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...)> : function_traits<R(Args...)> {
    using class_type = C;
};

// Test class for function traits
class TestObject {
public:
    void method(int x) {
        cout << "TestObject::method called with " << x << endl;
    }
};

// ===== DEMONSTRATION =====

void demonstrateConstexpr() {
    cout << "=== Constexpr Computations ===\n" << endl;

    cout << "Factorial(5) = " << factorial(5) << endl;
    cout << "Fibonacci(10) = " << fibonacci(10) << endl;
    cout << "Is 17 prime? " << (is_prime(17) ? "Yes" : "No") << endl;
    cout << "Is 15 prime? " << (is_prime(15) ? "Yes" : "No") << endl;

    // Constexpr array operations
    constexpr array<int, 5> arr = {1, 2, 3, 4, 5};
    cout << "Array sum: " << array_sum(arr) << endl;
    cout << "All even? " << (all_of(arr, [](int x) { return x % 2 == 0; }) ? "Yes" : "No") << endl;
    cout << "All positive? " << (all_of(arr, [](int x) { return x > 0; }) ? "Yes" : "No") << endl;
}

void demonstrateSFINAE() {
    cout << "\n=== SFINAE (Substitution Failure is Not An Error) ===\n" << endl;

    int i = 42;
    double d = 3.14;
    int* ptr = &i;
    string s = "hello";

    print_value(i);        // Uses print_integral
    print_value(d);        // Uses print_floating_point
    print_value(ptr);      // Uses print_pointer
    print_value(s);        // Uses generic fallback
}

void demonstrateTypeTraits() {
    cout << "\n=== Custom Type Traits ===\n" << endl;

    cout << "my_is_pointer<int>::value = " << my_is_pointer<int>::value << endl;
    cout << "my_is_pointer<int*>::value = " << my_is_pointer<int*>::value << endl;
    cout << "my_is_pointer<const int*>::value = " << my_is_pointer<const int*>::value << endl;

    cout << "my_is_array<int>::value = " << my_is_array<int>::value << endl;
    cout << "my_is_array<int[5]>::value = " << my_is_array<int[5]>::value << endl;
    cout << "my_is_array<int[]>::value = " << my_is_array<int[]>::value << endl;
}

void demonstrateTypeInfo() {
    cout << "\n=== Type Information System ===\n" << endl;

    cout << "int: " << TypeInfo<int>::name() << " (" << TypeInfo<int>::size() << " bytes)" << endl;
    cout << "double: " << TypeInfo<double>::name() << " (" << TypeInfo<double>::size() << " bytes)" << endl;
    cout << "string: " << TypeInfo<string>::name() << " (" << TypeInfo<string>::size() << " bytes)" << endl;
    cout << "int*: " << TypeInfo<int*>::name() << " (" << TypeInfo<int*>::size() << " bytes)" << endl;
    cout << "int[10]: " << TypeInfo<int[10]>::name() << " (" << TypeInfo<int[10]>::size() << " bytes)" << endl;
}

void demonstrateTypeManipulation() {
    cout << "\n=== Type Manipulation ===\n" << endl;

    using T1 = int;
    using T2 = const int;
    using T3 = int&;
    using T4 = int&&;

    cout << "my_remove_const<const int>::type is " << TypeInfo<my_remove_const_t<T2>>::name() << endl;
    cout << "my_add_const<int>::type is " << TypeInfo<my_add_const_t<T1>>::name() << endl;
    cout << "my_remove_reference<int&>::type is " << TypeInfo<my_remove_reference_t<T3>>::name() << endl;
    cout << "my_remove_reference<int&&>::type is " << TypeInfo<my_remove_reference_t<T4>>::name() << endl;
}

void demonstrateFunctionTraits() {
    cout << "\n=== Function Traits ===\n" << endl;

    using Func1 = int(*)(double, string);
    using Func2 = void (TestObject::*)(int);

    cout << "Function: int(*)(double, string)" << endl;
    cout << "  Return type: " << TypeInfo<function_traits<Func1>::return_type>::name() << endl;
    cout << "  Arity: " << function_traits<Func1>::arity << endl;
    cout << "  Arg 0: " << TypeInfo<function_traits<Func1>::template arg_type<0>>::name() << endl;
    cout << "  Arg 1: " << TypeInfo<function_traits<Func1>::template arg_type<1>>::name() << endl;

    cout << "\nMethod: void(TestObject::*)(int)" << endl;
    cout << "  Return type: " << TypeInfo<function_traits<Func2>::return_type>::name() << endl;
    cout << "  Class type: " << TypeInfo<function_traits<Func2>::class_type>::name() << endl;
    cout << "  Arity: " << function_traits<Func2>::arity << endl;
}

int main() {
    cout << "=== C++ Template Metaprogramming Demo ===\n" << endl;

    demonstrateConstexpr();
    demonstrateSFINAE();
    demonstrateTypeTraits();
    demonstrateTypeInfo();
    demonstrateTypeManipulation();
    demonstrateFunctionTraits();

    cout << "\n=== Summary ===" << endl;
    cout << "• Constexpr: Compile-time computations and checks" << endl;
    cout << "• SFINAE: Selective function template instantiation" << endl;
    cout << "• Type Traits: Compile-time type introspection" << endl;
    cout << "• Template Specialization: Customizing templates for specific types" << endl;
    cout << "• Type Manipulation: Modifying type properties at compile time" << endl;
    cout << "• Function Traits: Analyzing function signatures at compile time" << endl;

    return 0;
}