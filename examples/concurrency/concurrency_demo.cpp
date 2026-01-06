#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <future>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;
using namespace chrono;

void demonstrateThreads() {
    cout << "=== Basic Threads ===\n" << endl;

    // Function to run in a thread
    auto worker = [](int id) {
        cout << "Worker " << id << " started" << endl;
        this_thread::sleep_for(seconds(1));
        cout << "Worker " << id << " finished" << endl;
    };

    // Create and start threads
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    // Wait for threads to complete
    t1.join();
    t2.join();
    t3.join();

    cout << "All threads completed" << endl;
}

void demonstrateMutex() {
    cout << "\n=== Mutex (Mutual Exclusion) ===\n" << endl;

    mutex mtx;
    vector<int> shared_data;
    atomic<int> counter{0};

    auto producer = [&]() {
        for (int i = 0; i < 5; ++i) {
            lock_guard<mutex> lock(mtx);
            shared_data.push_back(counter++);
            cout << "Produced: " << shared_data.back() << endl;
            this_thread::sleep_for(milliseconds(100));
        }
    };

    auto consumer = [&]() {
        for (int i = 0; i < 5; ++i) {
            lock_guard<mutex> lock(mtx);
            if (!shared_data.empty()) {
                int value = shared_data.back();
                shared_data.pop_back();
                cout << "Consumed: " << value << endl;
            }
            this_thread::sleep_for(milliseconds(150));
        }
    };

    thread prod1(producer);
    thread prod2(producer);
    thread cons1(consumer);
    thread cons2(consumer);

    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();
}

void demonstrateConditionVariable() {
    cout << "\n=== Condition Variable ===\n" << endl;

    mutex mtx;
    condition_variable cv;
    queue<int> data_queue;
    bool done = false;

    auto producer = [&]() {
        for (int i = 0; i < 5; ++i) {
            this_thread::sleep_for(milliseconds(200));
            {
                lock_guard<mutex> lock(mtx);
                data_queue.push(i);
                cout << "Produced: " << i << endl;
            }
            cv.notify_one();
        }
        {
            lock_guard<mutex> lock(mtx);
            done = true;
        }
        cv.notify_all();
    };

    auto consumer = [&]() {
        while (true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]() { return !data_queue.empty() || done; });

            if (data_queue.empty() && done) {
                break;
            }

            int value = data_queue.front();
            data_queue.pop();
            cout << "Consumed: " << value << endl;
            lock.unlock();
        }
    };

    thread prod(producer);
    thread cons1(consumer);
    thread cons2(consumer);

    prod.join();
    cons1.join();
    cons2.join();
}

void demonstrateAtomic() {
    cout << "\n=== Atomic Operations ===\n" << endl;

    atomic<int> counter{0};
    atomic<bool> ready{false};

    auto incrementor = [&]() {
        for (int i = 0; i < 1000; ++i) {
            counter++;
        }
    };

    auto checker = [&]() {
        while (!ready) {
            this_thread::sleep_for(milliseconds(1));
        }
        cout << "Final counter value: " << counter.load() << endl;
    };

    thread t1(incrementor);
    thread t2(incrementor);
    thread t3(checker);

    t1.join();
    t2.join();

    ready = true;
    t3.join();

    cout << "Atomic operations ensure thread safety without locks" << endl;
}

void demonstrateFutures() {
    cout << "\n=== Futures and Promises ===\n" << endl;

    // packaged_task
    auto task = [](int x) -> int {
        this_thread::sleep_for(milliseconds(500));
        return x * x;
    };

    packaged_task<int(int)> pt(task);
    future<int> result = pt.get_future();

    thread t(move(pt), 5);
    cout << "Waiting for result..." << endl;
    cout << "Result: " << result.get() << endl;
    t.join();

    // async
    auto async_task = [](int x, int y) {
        this_thread::sleep_for(milliseconds(300));
        return x + y;
    };

    future<int> async_result = async(async_task, 10, 20);
    cout << "Async result: " << async_result.get() << endl;
}

void demonstrateThreadLocal() {
    cout << "\n=== Thread-Local Storage ===\n" << endl;

    thread_local int thread_id = 0;

    auto worker = [](int id) {
        thread_id = id;
        cout << "Thread " << id << " has thread_local value: " << thread_id << endl;
        this_thread::sleep_for(milliseconds(100));
        cout << "Thread " << id << " still has thread_local value: " << thread_id << endl;
    };

    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    cout << "Main thread thread_local: " << thread_id << endl;
}

void demonstrateThreadPool() {
    cout << "\n=== Simple Thread Pool ===\n" << endl;

    const int num_threads = 4;
    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex queue_mutex;
    condition_variable cv;
    bool stop = false;

    // Worker function
    auto worker = [&]() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(queue_mutex);
                cv.wait(lock, [&]() { return !tasks.empty() || stop; });

                if (stop && tasks.empty()) {
                    return;
                }

                task = move(tasks.front());
                tasks.pop();
            }
            task();
        }
    };

    // Start worker threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker);
    }

    // Add tasks to the pool
    auto add_task = [&](function<void()> task) {
        {
            lock_guard<mutex> lock(queue_mutex);
            tasks.push(move(task));
        }
        cv.notify_one();
    };

    // Submit some tasks
    for (int i = 0; i < 8; ++i) {
        add_task([i]() {
            cout << "Task " << i << " executed by thread "
                 << this_thread::get_id() << endl;
            this_thread::sleep_for(milliseconds(200));
        });
    }

    // Wait for all tasks to complete
    this_thread::sleep_for(seconds(2));

    // Stop the thread pool
    {
        lock_guard<mutex> lock(queue_mutex);
        stop = true;
    }
    cv.notify_all();

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    cout << "Thread pool completed" << endl;
}

int main() {
    cout << "=== C++ Concurrency Demo ===\n" << endl;

    demonstrateThreads();
    demonstrateMutex();
    demonstrateConditionVariable();
    demonstrateAtomic();
    demonstrateFutures();
    demonstrateThreadLocal();
    demonstrateThreadPool();

    cout << "\n=== Summary ===" << endl;
    cout << "• thread: Basic threading support" << endl;
    cout << "• mutex: Mutual exclusion for thread safety" << endl;
    cout << "• condition_variable: Thread synchronization" << endl;
    cout << "• atomic: Lock-free operations" << endl;
    cout << "• future/promise: Asynchronous operations" << endl;
    cout << "• thread_local: Thread-specific storage" << endl;
    cout << "• Thread pools: Managing multiple threads efficiently" << endl;

    return 0;
}