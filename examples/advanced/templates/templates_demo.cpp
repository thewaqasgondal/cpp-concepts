#include <concepts>
#include <iostream>
#include <type_traits>

// Concepts-based constraints
template <std::integral T>
T add_integral(T a, T b) {
    return a + b;
}

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

template <Addable T>
T add_generic(T a, T b) {
    return a + b;
}

// Compile-time calculation with constexpr and type traits
template <std::size_t N>
constexpr std::size_t factorial() {
    if constexpr (N <= 1) return 1;
    else return N * factorial<N - 1>();
}

int main() {
    std::cout << "add_integral<int>(2,3) = " << add_integral(2,3) << '\n';
    std::cout << "add_generic(2.5, 3.25) = " << add_generic(2.5, 3.25) << '\n';
    static_assert(factorial<5>() == 120);
    std::cout << "factorial<5>() = " << factorial<5>() << '\n';

    // type traits example
    std::cout << "is_integral<int>: " << std::boolalpha << std::is_integral_v<int> << '\n';
    std::cout << "is_integral<double>: " << std::is_integral_v<double> << '\n';
    return 0;
}
