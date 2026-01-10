#include "thread_pool.h"
#include <chrono>
#include <iostream>

int main() {
    ThreadPool pool(std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 2);

    auto f1 = pool.submit([]{ return 1 + 2; });
    auto f2 = pool.submit([](int a){ return a * 2; }, 21);

    std::cout << "f1=" << f1.get() << " f2=" << f2.get() << std::endl;

    // submit several tasks
    std::vector<std::future<int>> results;
    for (int i = 0; i < 8; ++i) {
        results.push_back(pool.submit([i]{ std::this_thread::sleep_for(std::chrono::milliseconds(10)); return i * i; }));
    }

    for (auto &r : results) std::cout << r.get() << " ";
    std::cout << "\nDone" << std::endl;
    return 0;
}
