#include <coroutine>
#include <iostream>
#include <optional>

// Simple generator coroutine (C++20)
template<typename T>
struct Generator {
    struct promise_type {
        std::optional<T> current;

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        std::suspend_always yield_value(T value) {
            current = std::move(value);
            return {};
        }

        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> coro;

    explicit Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
    Generator(const Generator&) = delete;
    Generator(Generator&& other) : coro(other.coro) { other.coro = {}; }
    ~Generator() { if (coro) coro.destroy(); }

    struct Iterator {
        std::coroutine_handle<promise_type> coro;
        bool operator!=(std::default_sentinel_t) const { return !coro.done(); }
        void operator++() { coro.resume(); }
        T operator*() const { return *coro.promise().current; }
    };

    Iterator begin() {
        coro.resume();
        return Iterator{coro};
    }

    std::default_sentinel_t end() { return {}; }
};

Generator<int> count_up(int n) {
    for (int i = 0; i < n; ++i) co_yield i;
}

int main() {
    std::cout << "Coroutine generator demo:" << std::endl;
    for (int v : count_up(10)) {
        std::cout << v << " ";
    }
    std::cout << "\nDone" << std::endl;
    return 0;
}
