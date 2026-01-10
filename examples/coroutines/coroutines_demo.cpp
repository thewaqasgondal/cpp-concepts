#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include <future>
#include <vector>
using namespace std;
using namespace chrono_literals;

// ===== COROUTINE BASICS =====

// Simple coroutine return type
struct CoroutineTask {
    struct promise_type {
        CoroutineTask get_return_object() { return {}; }
        suspend_never initial_suspend() { return {}; }
        suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

// Generator coroutine for yielding values
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        Generator get_return_object() { return Generator{handle_type::from_promise(*this)}; }
        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() {}
    };

    using handle_type = coroutine_handle<promise_type>;

    handle_type handle;

    Generator(handle_type h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    bool next() {
        if (!handle.done()) {
            handle.resume();
            return !handle.done();
        }
        return false;
    }

    T value() const { return handle.promise().current_value; }
};

// ===== ASYNC TASK COROUTINE =====

// Async task that can be awaited
struct AsyncTask {
    struct promise_type {
        AsyncTask get_return_object() { return {}; }
        suspend_never initial_suspend() { return {}; }
        suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

// ===== COROUTINE EXAMPLES =====

// Simple coroutine that prints messages
CoroutineTask simple_coroutine() {
    cout << "Coroutine started" << endl;
    co_await suspend_always{};
    cout << "Coroutine resumed" << endl;
    co_await suspend_always{};
    cout << "Coroutine finished" << endl;
}

// Generator that yields Fibonacci numbers
Generator<int> fibonacci_generator(int count) {
    int a = 0, b = 1;
    for (int i = 0; i < count; ++i) {
        co_yield a;
        int temp = a;
        a = b;
        b = temp + b;
    }
}

// Generator that yields even numbers
Generator<int> even_numbers(int max) {
    for (int i = 0; i <= max; i += 2) {
        co_yield i;
    }
}

// ===== ASYNC OPERATIONS =====

// Simulate async file I/O
AsyncTask async_file_operation() {
    cout << "Starting async file operation..." << endl;
    this_thread::sleep_for(100ms);
    cout << "File operation completed" << endl;
}

// Simulate async network request
AsyncTask async_network_request() {
    cout << "Starting network request..." << endl;
    this_thread::sleep_for(200ms);
    cout << "Network request completed" << endl;
}

// ===== COROUTINE WITH THREADING =====

// Coroutine that runs on a separate thread
CoroutineTask threaded_coroutine() {
    cout << "Coroutine running on thread: " << this_thread::get_id() << endl;

    // Simulate some work
    this_thread::sleep_for(50ms);

    cout << "Switching to main thread for I/O" << endl;
    co_await suspend_always{};

    cout << "Back on main thread: " << this_thread::get_id() << endl;
}

// ===== LAZY EVALUATION =====

// Lazy evaluation with coroutines
Generator<int> lazy_factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
        co_yield result;
    }
}

// ===== COROUTINE PIPELINE =====

// Pipeline stage 1: Generate numbers
Generator<int> generate_numbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i;
    }
}

// Pipeline stage 2: Filter even numbers
Generator<int> filter_even(Generator<int>& input) {
    while (input.next()) {
        int value = input.value();
        if (value % 2 == 0) {
            co_yield value;
        }
    }
}

// Pipeline stage 3: Square the numbers
Generator<int> square_numbers(Generator<int>& input) {
    while (input.next()) {
        int value = input.value();
        co_yield value * value;
    }
}

// ===== DEMONSTRATION =====

void demonstrate_basic_coroutines() {
    cout << "=== Basic Coroutines ===\n" << endl;

    cout << "Running simple coroutine:" << endl;
    simple_coroutine();
    cout << endl;
}

void demonstrate_generators() {
    cout << "=== Generators ===\n" << endl;

    cout << "Fibonacci numbers: ";
    auto fib = fibonacci_generator(10);
    while (fib.next()) {
        cout << fib.value() << " ";
    }
    cout << endl;

    cout << "Even numbers: ";
    auto evens = even_numbers(20);
    while (evens.next()) {
        cout << evens.value() << " ";
    }
    cout << endl;

    cout << "Factorials: ";
    auto facts = lazy_factorial(5);
    while (facts.next()) {
        cout << facts.value() << " ";
    }
    cout << endl << endl;
}

void demonstrate_async_operations() {
    cout << "=== Async Operations ===\n" << endl;

    cout << "Running async operations concurrently:" << endl;

    // Run async operations (simulated)
    async_file_operation();
    async_network_request();

    cout << endl;
}

void demonstrate_threading() {
    cout << "=== Threading with Coroutines ===\n" << endl;

    cout << "Main thread: " << this_thread::get_id() << endl;

    // Run coroutine on current thread
    threaded_coroutine();

    cout << endl;
}

void demonstrate_pipeline() {
    cout << "=== Coroutine Pipeline ===\n" << endl;

    cout << "Processing pipeline: generate -> filter even -> square" << endl;

    // Create pipeline
    auto numbers = generate_numbers(1, 10);
    auto evens = filter_even(numbers);
    auto squares = square_numbers(evens);

    cout << "Results: ";
    while (squares.next()) {
        cout << squares.value() << " ";
    }
    cout << endl << endl;
}

void demonstrate_performance_comparison() {
    cout << "=== Performance Comparison ===\n" << endl;

    const int COUNT = 100000;

    // Traditional approach
    cout << "Traditional approach:" << endl;
    auto start = chrono::high_resolution_clock::now();

    vector<int> results;
    for (int i = 1; i <= COUNT; ++i) {
        if (i % 2 == 0) {
            results.push_back(i * i);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration_traditional = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration_traditional.count() << " microseconds" << endl;
    cout << "Results count: " << results.size() << endl;

    // Coroutine pipeline approach
    cout << "\nCoroutine pipeline approach:" << endl;
    start = chrono::high_resolution_clock::now();

    auto gen = generate_numbers(1, COUNT);
    auto filtered = filter_even(gen);
    auto squared = square_numbers(filtered);

    int count = 0;
    while (squared.next()) {
        count++;
    }

    end = chrono::high_resolution_clock::now();
    auto duration_coroutine = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration_coroutine.count() << " microseconds" << endl;
    cout << "Results count: " << count << endl;

    cout << "\nNote: Coroutines may be slower for simple operations due to overhead," << endl;
    cout << "but they excel at complex async workflows and lazy evaluation." << endl << endl;
}

int main() {
    cout << "=== C++20 Coroutines Demo ===\n" << endl;

    demonstrate_basic_coroutines();
    demonstrate_generators();
    demonstrate_async_operations();
    demonstrate_threading();
    demonstrate_pipeline();
    demonstrate_performance_comparison();

    cout << "=== Coroutines Summary ===" << endl;
    cout << "• Coroutines enable cooperative multitasking" << endl;
    cout << "• Generators provide lazy evaluation of sequences" << endl;
    cout << "• Async operations can be written synchronously" << endl;
    cout << "• Pipelines enable functional-style data processing" << endl;
    cout << "• Best for I/O-bound operations and complex workflows" << endl;

    return 0;
}