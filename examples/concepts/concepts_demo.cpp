#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <type_traits>
#include <concepts>
using namespace std;

// ===== BASIC CONCEPTS =====

// Concept for integral types
template<typename T>
concept Integral = is_integral_v<T>;

// Concept for floating point types
template<typename T>
concept FloatingPoint = is_floating_point_v<T>;

// Concept for arithmetic types (integral or floating point)
template<typename T>
concept Arithmetic = Integral<T> || FloatingPoint<T>;

// ===== CONTAINER CONCEPTS =====

// Concept for container types
template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::iterator;
    t.begin();
    t.end();
    t.size();
};

// Concept for sequence containers
template<typename T>
concept SequenceContainer = Container<T> && requires(T t) {
    t.push_back(typename T::value_type{});
    t.insert(t.begin(), typename T::value_type{});
};

// Concept for random access containers
template<typename T>
concept RandomAccessContainer = SequenceContainer<T> && requires(T t, size_t i) {
    t[i];
    t.at(i);
};

// ===== FUNCTION CONCEPTS =====

// Concept for callable objects
template<typename F, typename... Args>
concept Callable = requires(F f, Args... args) {
    f(args...);
};

// Concept for predicates (functions returning bool)
template<typename F, typename T>
concept Predicate = Callable<F, T> && requires(F f, T t) {
    { f(t) } -> same_as<bool>;
};

// Concept for comparators
template<typename F, typename T>
concept Comparator = Callable<F, T, T> && requires(F f, T a, T b) {
    { f(a, b) } -> same_as<bool>;
};

// ===== NUMERIC CONCEPTS =====

// Concept for numbers that can be added
template<typename T>
concept Addable = requires(T a, T b) {
    a + b;
    { a + b } -> same_as<T>;
};

// Concept for numbers that can be multiplied
template<typename T>
concept Multipliable = requires(T a, T b) {
    a * b;
    { a * b } -> same_as<T>;
};

// Concept for numbers supporting basic arithmetic
template<typename T>
concept Numeric = Addable<T> && Multipliable<T> && requires(T a) {
    -a;
    a = a;
};

// ===== STRING-LIKE CONCEPTS =====

// Concept for string-like types
template<typename T>
concept StringLike = requires(T s) {
    s.length();
    s.size();
    s.empty();
    s.substr(0, 1);
    s.find('c');
};

// ===== DEMONSTRATION FUNCTIONS =====

// Function constrained by Integral concept
template<Integral T>
void print_integral(T value) {
    cout << "Integral value: " << value << endl;
}

// Function constrained by FloatingPoint concept
template<FloatingPoint T>
void print_floating_point(T value) {
    cout << "Floating point value: " << value << endl;
}

// Function constrained by Arithmetic concept
template<Arithmetic T>
T square(T value) {
    return value * value;
}

// Function constrained by Container concept
template<Container C>
void print_container(const C& container) {
    cout << "Container contents: ";
    for (const auto& item : container) {
        cout << item << " ";
    }
    cout << endl;
    cout << "Size: " << container.size() << endl;
}

// Function constrained by SequenceContainer concept
template<SequenceContainer C>
void add_elements(C& container, typename C::value_type value, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        container.push_back(value);
    }
}

// Function constrained by RandomAccessContainer concept
template<RandomAccessContainer C>
typename C::value_type get_middle_element(const C& container) {
    if (container.empty()) {
        throw runtime_error("Container is empty");
    }
    return container[container.size() / 2];
}

// Function constrained by Predicate concept
template<Container C, Predicate<typename C::value_type> Pred>
size_t count_if(const C& container, Pred predicate) {
    size_t count = 0;
    for (const auto& item : container) {
        if (predicate(item)) {
            count++;
        }
    }
    return count;
}

// Function constrained by Comparator concept
template<Container C, Comparator<typename C::value_type> Comp>
typename C::value_type find_max(const C& container, Comp comparator) {
    if (container.empty()) {
        throw runtime_error("Container is empty");
    }

    auto it = container.begin();
    auto max_it = it;
    ++it;

    for (; it != container.end(); ++it) {
        if (comparator(*it, *max_it)) {
            max_it = it;
        }
    }

    return *max_it;
}

// Function constrained by Numeric concept
template<Numeric T>
T calculate_average(const vector<T>& values) {
    if (values.empty()) {
        return T{};
    }

    T sum = T{};
    for (const T& value : values) {
        sum = sum + value;
    }
    return sum / static_cast<T>(values.size());
}

// Function constrained by StringLike concept
template<StringLike S>
void analyze_string(const S& str) {
    cout << "String analysis:" << endl;
    cout << "  Length: " << str.length() << endl;
    cout << "  Size: " << str.size() << endl;
    cout << "  Empty: " << (str.empty() ? "yes" : "no") << endl;
    if (!str.empty()) {
        cout << "  First character: " << str[0] << endl;
        cout << "  Contains 'e': " << (str.find('e') != string::npos ? "yes" : "no") << endl;
    }
}

// ===== CONCEPT-BASED CLASS TEMPLATES =====

// Generic calculator class constrained by Numeric concept
template<Numeric T>
class Calculator {
private:
    T value;

public:
    Calculator(T initial = T{}) : value(initial) {}

    void add(T other) { value = value + other; }
    void multiply(T other) { value = value * other; }
    void square() { value = value * value; }

    T get_value() const { return value; }
    void reset() { value = T{}; }
};

// Generic buffer class constrained by SequenceContainer concept
template<SequenceContainer C>
class Buffer {
private:
    C data;
    size_t max_size;

public:
    Buffer(size_t max_size) : max_size(max_size) {}

    bool add(typename C::value_type item) {
        if (data.size() >= max_size) {
            return false;
        }
        data.push_back(item);
        return true;
    }

    void clear() { data.clear(); }
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }

    const C& get_data() const { return data; }
};

// ===== DEMONSTRATION =====

void demonstrate_basic_concepts() {
    cout << "=== Basic Concepts ===\n" << endl;

    // Test integral concept
    print_integral(42);
    print_integral(static_cast<short>(10));

    // Test floating point concept
    print_floating_point(3.14);
    print_floating_point(2.71f);

    // Test arithmetic concept
    cout << "Square of 5: " << square(5) << endl;
    cout << "Square of 3.5: " << square(3.5) << endl;

    cout << endl;
}

void demonstrate_container_concepts() {
    cout << "=== Container Concepts ===\n" << endl;

    vector<int> vec = {1, 2, 3, 4, 5};
    list<string> lst = {"hello", "world", "concepts"};

    print_container(vec);
    print_container(lst);

    // Test sequence container operations
    add_elements(vec, 6, 3);
    cout << "After adding elements: ";
    print_container(vec);

    // Test random access container operations
    try {
        cout << "Middle element: " << get_middle_element(vec) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl;
}

void demonstrate_function_concepts() {
    cout << "=== Function Concepts ===\n" << endl;

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Count even numbers using predicate
    size_t even_count = count_if(numbers, [](int x) { return x % 2 == 0; });
    cout << "Even numbers count: " << even_count << endl;

    // Find maximum using comparator
    int max_val = find_max(numbers, [](int a, int b) { return a > b; });
    cout << "Maximum value: " << max_val << endl;

    cout << endl;
}

void demonstrate_numeric_concepts() {
    cout << "=== Numeric Concepts ===\n" << endl;

    vector<int> int_values = {1, 2, 3, 4, 5};
    vector<double> double_values = {1.1, 2.2, 3.3, 4.4, 5.5};

    cout << "Average of integers: " << calculate_average(int_values) << endl;
    cout << "Average of doubles: " << calculate_average(double_values) << endl;

    cout << endl;
}

void demonstrate_string_concepts() {
    cout << "=== String Concepts ===\n" << endl;

    string str = "Hello, Concepts!";
    analyze_string(str);

    cout << endl;
}

void demonstrate_concept_based_classes() {
    cout << "=== Concept-Based Classes ===\n" << endl;

    // Calculator with int
    Calculator<int> int_calc(10);
    int_calc.add(5);
    int_calc.multiply(2);
    cout << "Integer calculator result: " << int_calc.get_value() << endl;

    // Calculator with double
    Calculator<double> double_calc(3.14);
    double_calc.square();
    cout << "Double calculator result: " << double_calc.get_value() << endl;

    // Buffer with vector
    Buffer<vector<int>> vec_buffer(5);
    for (int i = 1; i <= 6; ++i) {
        if (!vec_buffer.add(i)) {
            cout << "Buffer full, couldn't add " << i << endl;
            break;
        }
    }
    cout << "Buffer size: " << vec_buffer.size() << endl;

    // Buffer with list
    Buffer<list<string>> list_buffer(3);
    list_buffer.add("hello");
    list_buffer.add("world");
    list_buffer.add("concepts");
    cout << "List buffer size: " << list_buffer.size() << endl;

    cout << endl;
}

void demonstrate_concept_errors() {
    cout << "=== Concept Error Examples ===\n" << endl;

    cout << "The following lines would cause compilation errors if uncommented:" << endl;
    cout << "// print_integral(3.14);  // Error: double is not Integral" << endl;
    cout << "// print_floating_point(42);  // Error: int is not FloatingPoint" << endl;
    cout << "// add_elements(set<int>{}, 1, 5);  // Error: set is not SequenceContainer" << endl;
    cout << "// get_middle_element(list<int>{});  // Error: list is not RandomAccessContainer" << endl;
    cout << "// calculate_average(vector<string>{});  // Error: string is not Numeric" << endl;

    cout << endl;
}

int main() {
    cout << "=== C++20 Concepts Demo ===\n" << endl;

    demonstrate_basic_concepts();
    demonstrate_container_concepts();
    demonstrate_function_concepts();
    demonstrate_numeric_concepts();
    demonstrate_string_concepts();
    demonstrate_concept_based_classes();
    demonstrate_concept_errors();

    cout << "=== Concepts Summary ===" << endl;
    cout << "• Concepts provide compile-time constraints for templates" << endl;
    cout << "• Better error messages than SFINAE" << endl;
    cout << "• Self-documenting code with meaningful requirements" << endl;
    cout << "• Enable function overloading based on type properties" << endl;
    cout << "• Can be combined with auto and generic lambdas" << endl;

    return 0;
}