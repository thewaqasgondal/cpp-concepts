#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
#include <optional>
#include <variant>
#include <any>
using namespace std;

// Constexpr function (must be defined at global scope)
constexpr int square(int x) {
    return x * x;
}

void demonstrateAutoAndDecltype() {
    cout << "=== Auto and Decltype ===\n" << endl;

    // Auto keyword (C++11)
    auto x = 42;        // int
    auto y = 3.14;      // double
    auto z = "hello";   // const char*
    auto v = vector<int>{1, 2, 3}; // vector<int>

    cout << "x: " << x << " (type: int)" << endl;
    cout << "y: " << y << " (type: double)" << endl;
    cout << "z: " << z << " (type: const char*)" << endl;
    cout << "v: ";
    for (auto& elem : v) cout << elem << " ";
    cout << "(type: vector<int>)" << endl;

    // Decltype (C++11)
    decltype(x) a = 100;        // int
    decltype(y) b = 2.71;       // double
    decltype(v) w = {4, 5, 6};  // vector<int>

    cout << "\ndecltype examples:" << endl;
    cout << "a: " << a << " (same type as x)" << endl;
    cout << "b: " << b << " (same type as y)" << endl;
    cout << "w: ";
    for (auto& elem : w) cout << elem << " ";
    cout << "(same type as v)" << endl;
}

void demonstrateRangeBasedFor() {
    cout << "\n=== Range-based For Loop ===\n" << endl;

    vector<string> fruits = {"apple", "banana", "cherry"};

    cout << "Fruits: ";
    for (const auto& fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl;

    // With structured bindings (C++17)
    vector<pair<string, int>> inventory = {
        {"apples", 5},
        {"bananas", 3},
        {"cherries", 7}
    };

    cout << "Inventory:" << endl;
    for (const auto& [item, count] : inventory) {
        cout << "  " << item << ": " << count << endl;
    }
}

void demonstrateLambdas() {
    cout << "\n=== Lambdas ===\n" << endl;

    // Basic lambda
    auto basic_lambda = []() {
        cout << "Hello from basic lambda!" << endl;
    };
    basic_lambda();

    // Lambda with parameters
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << "5 + 3 = " << add(5, 3) << endl;

    // Lambda with capture
    int multiplier = 2;
    auto multiply = [multiplier](int x) {
        return x * multiplier;
    };
    cout << "5 * 2 = " << multiply(5) << endl;

    // Capture by reference
    int counter = 0;
    auto increment = [&counter]() {
        counter++;
        cout << "Counter: " << counter << endl;
    };
    increment();
    increment();

    // Generic lambda (C++14)
    auto generic_add = [](auto a, auto b) {
        return a + b;
    };
    cout << "Generic add: " << generic_add(3, 4) << endl;
    cout << "Generic add: " << generic_add(3.5, 2.1) << endl;
    cout << "Generic add: " << generic_add(string("Hello"), string(" World")) << endl;
}

void demonstrateSmartPointers() {
    cout << "\n=== Smart Pointers ===\n" << endl;

    // unique_ptr
    auto unique = make_unique<string>("Hello, unique_ptr!");
    cout << "unique_ptr: " << *unique << endl;

    // shared_ptr
    auto shared1 = make_shared<string>("Hello, shared_ptr!");
    auto shared2 = shared1; // Reference count increases
    cout << "shared_ptr: " << *shared1 << endl;
    cout << "Use count: " << shared1.use_count() << endl;

    // weak_ptr
    auto weak = weak_ptr<string>(shared1);
    if (auto locked = weak.lock()) {
        cout << "weak_ptr locked: " << *locked << endl;
    }
}

void demonstrateOptional() {
    cout << "\n=== Optional ===\n" << endl;

    // Function that may or may not return a value
    auto find_value = [](int target) -> optional<int> {
        vector<int> data = {1, 2, 3, 4, 5};
        auto it = find(data.begin(), data.end(), target);
        if (it != data.end()) {
            return *it;
        }
        return nullopt;
    };

    auto result1 = find_value(3);
    if (result1) {
        cout << "Found: " << *result1 << endl;
    } else {
        cout << "Not found" << endl;
    }

    auto result2 = find_value(10);
    if (result2) {
        cout << "Found: " << *result2 << endl;
    } else {
        cout << "Not found" << endl;
    }

    // Using value_or
    cout << "Value or default: " << result2.value_or(-1) << endl;
}

void demonstrateVariant() {
    cout << "\n=== Variant ===\n" << endl;

    // Variant can hold different types
    variant<int, double, string> v;

    v = 42;
    cout << "Variant holds int: " << get<int>(v) << endl;

    v = 3.14;
    cout << "Variant holds double: " << get<double>(v) << endl;

    v = "hello";
    cout << "Variant holds string: " << get<string>(v) << endl;

    // Using visit (C++17)
    auto visitor = [](auto&& arg) {
        cout << "Visited: " << arg << endl;
    };

    v = 100;
    visit(visitor, v);

    v = 2.71;
    visit(visitor, v);

    v = "world";
    visit(visitor, v);
}

void demonstrateAny() {
    cout << "\n=== Any ===\n" << endl;

    // Any can hold any type
    any a;

    a = 42;
    cout << "Any holds int: " << any_cast<int>(a) << endl;

    a = 3.14;
    cout << "Any holds double: " << any_cast<double>(a) << endl;

    a = string("hello");
    cout << "Any holds string: " << any_cast<string>(a) << endl;

    // Check type
    if (a.type() == typeid(string)) {
        cout << "Type is string" << endl;
    }
}

void demonstrateConstexpr() {
    cout << "\n=== Constexpr ===\n" << endl;

    // Constexpr function is defined at global scope
    constexpr int result = square(5);
    cout << "5 squared (compile-time): " << result << endl;

    // Constexpr if (C++17) - using compile-time condition
    if constexpr (sizeof(int) == 4) {
        cout << "int is 32-bit" << endl;
    } else {
        cout << "int is not 32-bit" << endl;
    }

    // Runtime condition
    auto check_value = [](int x) {
        if (x > 0) {
            cout << x << " is positive" << endl;
        } else {
            cout << x << " is not positive" << endl;
        }
    };

    check_value(5);
    check_value(-3);
}

int main() {
    cout << "=== Modern C++ Features Demo ===\n" << endl;

    demonstrateAutoAndDecltype();
    demonstrateRangeBasedFor();
    demonstrateLambdas();
    demonstrateSmartPointers();
    demonstrateOptional();
    demonstrateVariant();
    demonstrateAny();
    demonstrateConstexpr();

    cout << "\n=== Summary ===" << endl;
    cout << "• auto and decltype: Automatic type deduction" << endl;
    cout << "• Range-based for: Simplified iteration" << endl;
    cout << "• Lambdas: Anonymous functions with capture" << endl;
    cout << "• Smart pointers: Automatic memory management" << endl;
    cout << "• Optional: Values that may or may not exist" << endl;
    cout << "• Variant: Type-safe unions" << endl;
    cout << "• Any: Type-erased containers" << endl;
    cout << "• Constexpr: Compile-time computation" << endl;

    return 0;
}