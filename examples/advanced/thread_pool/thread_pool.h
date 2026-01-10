#pragma once
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// Minimal thread-pool using std::jthread and stop_token (C++20+)
class ThreadPool {
public:
    explicit ThreadPool(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            workers.emplace_back([this](std::stop_token st){ worker_loop(st); });
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lk(m);
            stopping = true;
        }
        cv.notify_all();
        // jthreads will stop via stop_token
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) {
        using R = std::invoke_result_t<F, Args...>;
        auto task = std::make_shared<std::packaged_task<R()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<R> res = task->get_future();
        {
            std::lock_guard<std::mutex> lk(m);
            tasks.push([task]() { (*task)(); });
        }
        cv.notify_one();
        return res;
    }

private:
    std::vector<std::jthread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex m;
    std::condition_variable_any cv;
    bool stopping = false;

    void worker_loop(std::stop_token st) {
        while (!st.stop_requested()) {
            std::function<void()> job;
            {
                std::unique_lock<std::mutex> lk(m);
                cv.wait(lk, [&]{ return stopping || !tasks.empty() || st.stop_requested(); });
                if (tasks.empty()) continue;
                job = std::move(tasks.front()); tasks.pop();
            }
            if (job) job();
        }
    }
};
