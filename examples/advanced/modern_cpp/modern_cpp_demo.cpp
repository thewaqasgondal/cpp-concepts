#include <iostream>
#include <memory>
#include <utility>

struct Widget {
    Widget(int id) : id(id) { std::cout << "Widget(" << id << ") constructed\n"; }
    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;
    Widget(Widget&& other) noexcept : id(other.id) { std::cout << "Widget moved\n"; other.id = -1; }
    Widget& operator=(Widget&&) = delete;
    ~Widget() { std::cout << "Widget(" << id << ") destroyed\n"; }
    int id;
};

// Factory that returns unique_ptr (move semantics)
std::unique_ptr<Widget> make_widget(int id) {
    return std::make_unique<Widget>(id);
}

// Demonstrate RVO and move elision
Widget make_widget_by_value(int id) {
    return Widget{id};
}

int main() {
    std::cout << "-- Unique/Shared pointer demo --\n";
    auto u = make_widget(1);
    std::shared_ptr<Widget> s = std::move(u);
    if (!u) std::cout << "unique_ptr moved to shared_ptr\n";

    std::cout << "-- Move semantics demo --\n";
    Widget w = make_widget_by_value(2); // RVO/elision
    Widget w2(std::move(w)); // explicit move (w is left in valid but unspecified state)

    std::cout << "-- End demo --\n";
    return 0;
}
