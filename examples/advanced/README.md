# Advanced Examples

This folder contains more advanced, self-contained examples demonstrating modern C++ concepts and utilities.

Included examples:

- **concurrency/concurrency_demo.cpp** — Producer/consumer example using threads, condition_variable and atomic counters.
- **modern_cpp/modern_cpp_demo.cpp** — Move semantics, `unique_ptr`/`shared_ptr`, and RVO demonstration.
- **templates/templates_demo.cpp** — C++20 concepts, type traits, and `constexpr` compile-time computation.
- **coroutines/coroutines_demo.cpp** — C++20 coroutine generator demo
- **thread_pool/thread_pool_demo.cpp** — Thread pool using `std::jthread` and futures (includes tests)

Build using CMake (top-level):

```bash
mkdir -p build && cd build
cmake -DCMAKE_CXX_STANDARD=23 ..
make
./examples/advanced/concurrency/concurrency_demo
./examples/advanced/modern_cpp/modern_cpp_demo
./examples/advanced/templates/templates_demo
./examples/advanced/coroutines/coroutines_demo
./examples/advanced/thread_pool/thread_pool_demo

# To run tests (requires network to fetch Catch2 via CMake FetchContent):
ctest --output-on-failure
```
