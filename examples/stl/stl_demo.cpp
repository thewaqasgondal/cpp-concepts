#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

void demonstrateContainers() {
    cout << "=== STL Containers ===\n" << endl;

    // Vector
    cout << "1. Vector:" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    cout << "Vector: ";
    for (int num : vec) cout << num << " ";
    cout << endl;

    // Array (fixed size)
    cout << "\n2. Array:" << endl;
    array<int, 5> arr = {10, 20, 30, 40, 50};
    cout << "Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    // Deque
    cout << "\n3. Deque:" << endl;
    deque<int> deq = {1, 2, 3};
    deq.push_front(0);
    deq.push_back(4);
    cout << "Deque: ";
    for (int num : deq) cout << num << " ";
    cout << endl;

    // List
    cout << "\n4. List:" << endl;
    list<int> lst = {1, 2, 3, 4, 5};
    lst.push_front(0);
    lst.push_back(6);
    cout << "List: ";
    for (int num : lst) cout << num << " ";
    cout << endl;

    // Set (unique, sorted)
    cout << "\n5. Set:" << endl;
    set<int> s = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Set: ";
    for (int num : s) cout << num << " ";
    cout << endl;

    // Unordered Set
    cout << "\n6. Unordered Set:" << endl;
    unordered_set<int> us = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Unordered Set: ";
    for (int num : us) cout << num << " ";
    cout << endl;

    // Map
    cout << "\n7. Map:" << endl;
    map<string, int> m;
    m["apple"] = 5;
    m["banana"] = 3;
    m["cherry"] = 7;
    cout << "Map contents:" << endl;
    for (const auto& pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Unordered Map
    cout << "\n8. Unordered Map:" << endl;
    unordered_map<string, int> um = {{"one", 1}, {"two", 2}, {"three", 3}};
    cout << "Unordered Map:" << endl;
    for (const auto& pair : um) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void demonstrateAdapters() {
    cout << "\n=== Container Adapters ===\n" << endl;

    // Stack (LIFO)
    cout << "1. Stack:" << endl;
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout << "Stack top: " << stk.top() << endl;
    stk.pop();
    cout << "After pop, stack top: " << stk.top() << endl;

    // Queue (FIFO)
    cout << "\n2. Queue:" << endl;
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "Queue front: " << q.front() << endl;
    q.pop();
    cout << "After pop, queue front: " << q.front() << endl;

    // Priority Queue (max-heap by default)
    cout << "\n3. Priority Queue:" << endl;
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(2);
    cout << "Priority queue top: " << pq.top() << endl;
    pq.pop();
    cout << "After pop, priority queue top: " << pq.top() << endl;
}

void demonstrateAlgorithms() {
    cout << "\n=== STL Algorithms ===\n" << endl;

    vector<int> nums = {9, 1, 8, 2, 7, 3, 6, 4, 5};

    cout << "Original vector: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    // Sorting
    cout << "\n1. Sorting:" << endl;
    sort(nums.begin(), nums.end());
    cout << "Sorted: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    // Reverse sorting
    sort(nums.begin(), nums.end(), greater<int>());
    cout << "Reverse sorted: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    // Finding
    cout << "\n2. Finding:" << endl;
    auto it = find(nums.begin(), nums.end(), 7);
    if (it != nums.end()) {
        cout << "Found 7 at position: " << (it - nums.begin()) << endl;
    }

    // Count
    cout << "\n3. Count:" << endl;
    int count = count_if(nums.begin(), nums.end(), [](int x) { return x > 5; });
    cout << "Numbers greater than 5: " << count << endl;

    // Transform
    cout << "\n4. Transform:" << endl;
    vector<int> squares(nums.size());
    transform(nums.begin(), nums.end(), squares.begin(), [](int x) { return x * x; });
    cout << "Squares: ";
    for (int num : squares) cout << num << " ";
    cout << endl;

    // Accumulate (sum)
    cout << "\n5. Accumulate:" << endl;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    cout << "Sum: " << sum << endl;

    // Min/Max
    cout << "\n6. Min/Max:" << endl;
    auto [min_it, max_it] = minmax_element(nums.begin(), nums.end());
    cout << "Min: " << *min_it << ", Max: " << *max_it << endl;
}

void demonstrateIterators() {
    cout << "\n=== Iterators ===\n" << endl;

    vector<int> vec = {1, 2, 3, 4, 5};

    cout << "1. Forward iteration:" << endl;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n2. Reverse iteration:" << endl;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n3. Const iterator:" << endl;
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        cout << *it << " ";
        // *it = 10; // Error: const iterator
    }
    cout << endl;
}

void demonstrateLambdas() {
    cout << "\n=== Lambdas and Function Objects ===\n" << endl;

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Lambda function
    cout << "1. Lambda function:" << endl;
    for_each(nums.begin(), nums.end(), [](int x) {
        cout << x << " ";
    });
    cout << endl;

    // Lambda with capture
    cout << "\n2. Lambda with capture:" << endl;
    int multiplier = 2;
    transform(nums.begin(), nums.end(), nums.begin(), [multiplier](int x) {
        return x * multiplier;
    });
    cout << "Multiplied by " << multiplier << ": ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    // Function object
    cout << "\n3. Function object:" << endl;
    struct IsEven {
        bool operator()(int x) const {
            return x % 2 == 0;
        }
    };

    auto it = find_if(nums.begin(), nums.end(), IsEven());
    if (it != nums.end()) {
        cout << "First even number: " << *it << endl;
    }
}

int main() {
    demonstrateContainers();
    demonstrateAdapters();
    demonstrateAlgorithms();
    demonstrateIterators();
    demonstrateLambdas();

    cout << "\n=== STL Summary ===" << endl;
    cout << "• Containers: vector, array, deque, list, set, map, etc." << endl;
    cout << "• Adapters: stack, queue, priority_queue" << endl;
    cout << "• Algorithms: sort, find, transform, accumulate, etc." << endl;
    cout << "• Iterators: begin(), end(), rbegin(), rend()" << endl;
    cout << "• Lambdas: Anonymous functions for algorithms" << endl;

    return 0;
}