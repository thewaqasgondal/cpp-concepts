#include <cassert>
#include <vector>
#include "../thread_pool.h"

int main() {
    {
        ThreadPool pool(4);
        auto f1 = pool.submit([]{ return 42; });
        auto f2 = pool.submit([](int a){ return a + 1; }, 7);
        assert(f1.get() == 42);
        assert(f2.get() == 8);
    }
    {
        ThreadPool pool(2);
        std::vector<std::future<int>> results;
        for (int i = 0; i < 20; ++i) results.push_back(pool.submit([i]{ return i; }));
        for (int i = 0; i < 20; ++i) assert(results[i].get() == i);
    }
    return 0;
}
