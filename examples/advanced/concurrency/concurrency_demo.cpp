#include <atomic>
#include <condition_variable>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// Simple thread-safe queue for producer-consumer demonstration
template <typename T>
class TSQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lk(m_);
        q_.push(std::move(value));
        cv_.notify_one();
    }

    bool pop(T &out) {
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [this] { return !q_.empty() || finished_; });
        if (q_.empty()) return false;
        out = std::move(q_.front());
        q_.pop();
        return true;
    }

    void finish() {
        {
            std::lock_guard<std::mutex> lk(m_);
            finished_ = true;
        }
        cv_.notify_all();
    }

private:
    std::mutex m_;
    std::condition_variable cv_;
    std::queue<T> q_;
    bool finished_ = false;
};

int main() {
    TSQueue<int> q;
    std::atomic<int> produced{0};
    std::atomic<int> consumed{0};

    const int PRODUCERS = 2;
    const int CONSUMERS = 3;
    const int ITEMS_PER_PRODUCER = 50;

    // Producers
    std::vector<std::thread> producers;
    for (int p = 0; p < PRODUCERS; ++p) {
        producers.emplace_back([&q, &produced, p]() {
            for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
                q.push(p * ITEMS_PER_PRODUCER + i);
                ++produced;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    }

    // Consumers
    std::vector<std::thread> consumers;
    for (int c = 0; c < CONSUMERS; ++c) {
        consumers.emplace_back([&q, &consumed, c]() {
            int value;
            while (q.pop(value)) {
                ++consumed;
                if (consumed % 25 == 0) {
                    std::cout << "Consumer " << c << " consumed " << value << " (total=" << consumed << ")\n";
                }
            }
            // queue finished and empty
        });
    }

    // Wait for producers and signal finish
    for (auto &t : producers) t.join();
    q.finish();

    for (auto &t : consumers) t.join();

    std::cout << "Produced: " << produced << ", Consumed: " << consumed << "\n";
    return 0;
}
