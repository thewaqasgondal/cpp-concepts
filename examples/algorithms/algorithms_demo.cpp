#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
using namespace std;

void demonstrateNonModifyingAlgorithms() {
    cout << "=== Non-Modifying Algorithms ===\n" << endl;

    vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // all_of, any_of, none_of
    cout << "Numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    bool all_positive = all_of(numbers.begin(), numbers.end(), [](int x) { return x > 0; });
    bool any_even = any_of(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; });
    bool none_negative = none_of(numbers.begin(), numbers.end(), [](int x) { return x < 0; });

    cout << "All positive: " << (all_positive ? "Yes" : "No") << endl;
    cout << "Any even: " << (any_even ? "Yes" : "No") << endl;
    cout << "None negative: " << (none_negative ? "Yes" : "No") << endl;

    // count, count_if
    int count_5 = count(numbers.begin(), numbers.end(), 5);
    int count_even = count_if(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; });

    cout << "Count of 5s: " << count_5 << endl;
    cout << "Count of evens: " << count_even << endl;

    // find, find_if, find_if_not
    auto it = find(numbers.begin(), numbers.end(), 9);
    if (it != numbers.end()) {
        cout << "Found 9 at position: " << distance(numbers.begin(), it) << endl;
    }

    auto it_even = find_if(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; });
    if (it_even != numbers.end()) {
        cout << "First even number: " << *it_even << endl;
    }
}

void demonstrateModifyingAlgorithms() {
    cout << "\n=== Modifying Algorithms ===\n" << endl;

    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> dest(5);

    // copy
    copy(source.begin(), source.end(), dest.begin());
    cout << "Copied: ";
    for (int n : dest) cout << n << " ";
    cout << endl;

    // copy_if
    vector<int> evens;
    copy_if(source.begin(), source.end(), back_inserter(evens), [](int x) { return x % 2 == 0; });
    cout << "Evens only: ";
    for (int n : evens) cout << n << " ";
    cout << endl;

    // transform
    vector<int> doubled(source.size());
    transform(source.begin(), source.end(), doubled.begin(), [](int x) { return x * 2; });
    cout << "Doubled: ";
    for (int n : doubled) cout << n << " ";
    cout << endl;

    // fill, generate
    vector<int> filled(5);
    fill(filled.begin(), filled.end(), 42);
    cout << "Filled with 42: ";
    for (int n : filled) cout << n << " ";
    cout << endl;

    // iota (C++11)
    vector<int> sequence(5);
    iota(sequence.begin(), sequence.end(), 10);
    cout << "Sequence from 10: ";
    for (int n : sequence) cout << n << " ";
    cout << endl;
}

void demonstrateSortingAlgorithms() {
    cout << "\n=== Sorting and Related Algorithms ===\n" << endl;

    vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // sort
    vector<int> sorted = numbers;
    sort(sorted.begin(), sorted.end());
    cout << "Sorted: ";
    for (int n : sorted) cout << n << " ";
    cout << endl;

    // stable_sort
    vector<pair<int, string>> pairs = {{3, "three"}, {1, "one"}, {2, "two"}, {1, "uno"}};
    stable_sort(pairs.begin(), pairs.end());
    cout << "Stable sorted pairs: ";
    for (auto& p : pairs) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // partial_sort
    vector<int> partial_sorted = numbers;
    partial_sort(partial_sorted.begin(), partial_sorted.begin() + 3, partial_sorted.end());
    cout << "Partial sort (first 3): ";
    for (int n : partial_sorted) cout << n << " ";
    cout << endl;

    // nth_element
    vector<int> nth_element_vec = numbers;
    nth_element(nth_element_vec.begin(), nth_element_vec.begin() + 2, nth_element_vec.end());
    cout << "nth_element (3rd smallest): " << nth_element_vec[2] << endl;
}

void demonstratePartitioningAlgorithms() {
    cout << "\n=== Partitioning Algorithms ===\n" << endl;

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // partition
    vector<int> partitioned = numbers;
    auto partition_point = partition(partitioned.begin(), partitioned.end(),
                                   [](int x) { return x % 2 == 0; });
    cout << "Partitioned by even/odd: ";
    for (int n : partitioned) cout << n << " ";
    cout << endl;
    cout << "Partition point at: " << distance(partitioned.begin(), partition_point) << endl;

    // stable_partition
    vector<int> stable_partitioned = numbers;
    auto stable_partition_point = stable_partition(stable_partitioned.begin(), stable_partitioned.end(),
                                                 [](int x) { return x <= 5; });
    cout << "Stable partitioned by <=5: ";
    for (int n : stable_partitioned) cout << n << " ";
    cout << endl;
}

void demonstrateHeapAlgorithms() {
    cout << "\n=== Heap Algorithms ===\n" << endl;

    vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // make_heap
    vector<int> heap = numbers;
    make_heap(heap.begin(), heap.end());
    cout << "Heap: ";
    for (int n : heap) cout << n << " ";
    cout << endl;

    // push_heap, pop_heap
    heap.push_back(7);
    push_heap(heap.begin(), heap.end());
    cout << "After push_heap(7): ";
    for (int n : heap) cout << n << " ";
    cout << endl;

    cout << "Heap top: " << heap.front() << endl;
    pop_heap(heap.begin(), heap.end());
    heap.pop_back();
    cout << "After pop_heap: ";
    for (int n : heap) cout << n << " ";
    cout << endl;
}

void demonstrateSetAlgorithms() {
    cout << "\n=== Set Algorithms ===\n" << endl;

    vector<int> set1 = {1, 2, 3, 4, 5};
    vector<int> set2 = {3, 4, 5, 6, 7};
    vector<int> result;

    // set_union
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
    cout << "Union: ";
    for (int n : result) cout << n << " ";
    cout << endl;

    // set_intersection
    result.clear();
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
    cout << "Intersection: ";
    for (int n : result) cout << n << " ";
    cout << endl;

    // set_difference
    result.clear();
    set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
    cout << "Difference (set1 - set2): ";
    for (int n : result) cout << n << " ";
    cout << endl;
}

void demonstrateNumericAlgorithms() {
    cout << "\n=== Numeric Algorithms ===\n" << endl;

    vector<int> numbers = {1, 2, 3, 4, 5};

    // accumulate
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    cout << "Sum: " << sum << endl;

    // inner_product
    vector<int> weights = {1, 2, 3, 4, 5};
    int dot_product = inner_product(numbers.begin(), numbers.end(), weights.begin(), 0);
    cout << "Dot product: " << dot_product << endl;

    // partial_sum
    vector<int> partial_sums(numbers.size());
    partial_sum(numbers.begin(), numbers.end(), partial_sums.begin());
    cout << "Partial sums: ";
    for (int n : partial_sums) cout << n << " ";
    cout << endl;

    // adjacent_difference
    vector<int> differences(numbers.size());
    adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
    cout << "Adjacent differences: ";
    for (int n : differences) cout << n << " ";
    cout << endl;
}

void demonstrateCustomComparators() {
    cout << "\n=== Custom Comparators ===\n" << endl;

    vector<string> words = {"apple", "Banana", "cherry", "Date"};

    // sort with custom comparator (case-insensitive)
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        string lower_a = a, lower_b = b;
        transform(lower_a.begin(), lower_a.end(), lower_a.begin(), ::tolower);
        transform(lower_b.begin(), lower_b.end(), lower_b.begin(), ::tolower);
        return lower_a < lower_b;
    });

    cout << "Case-insensitive sort: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;

    // sort by length
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });

    cout << "Sort by length: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
}

void demonstrateAlgorithmComposition() {
    cout << "\n=== Algorithm Composition ===\n" << endl;

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Combine multiple algorithms
    vector<int> result;

    // Copy even numbers, double them, and collect
    copy_if(numbers.begin(), numbers.end(), back_inserter(result),
            [](int x) { return x % 2 == 0; });
    transform(result.begin(), result.end(), result.begin(),
              [](int x) { return x * 2; });

    cout << "Even numbers doubled: ";
    for (int n : result) cout << n << " ";
    cout << endl;

    // Find minimum and maximum simultaneously
    auto [min_it, max_it] = minmax_element(numbers.begin(), numbers.end());
    cout << "Min: " << *min_it << ", Max: " << *max_it << endl;

    // Clamp values
    vector<int> clamped;
    transform(numbers.begin(), numbers.end(), back_inserter(clamped),
              [](int x) { return clamp(x, 3, 7); });
    cout << "Clamped to [3,7]: ";
    for (int n : clamped) cout << n << " ";
    cout << endl;
}

int main() {
    cout << "=== Advanced STL Algorithms Demo ===\n" << endl;

    demonstrateNonModifyingAlgorithms();
    demonstrateModifyingAlgorithms();
    demonstrateSortingAlgorithms();
    demonstratePartitioningAlgorithms();
    demonstrateHeapAlgorithms();
    demonstrateSetAlgorithms();
    demonstrateNumericAlgorithms();
    demonstrateCustomComparators();
    demonstrateAlgorithmComposition();

    cout << "\n=== Summary ===" << endl;
    cout << "• Non-modifying: all_of, any_of, none_of, count, find" << endl;
    cout << "• Modifying: copy, transform, fill, generate, iota" << endl;
    cout << "• Sorting: sort, stable_sort, partial_sort, nth_element" << endl;
    cout << "• Partitioning: partition, stable_partition" << endl;
    cout << "• Heap: make_heap, push_heap, pop_heap" << endl;
    cout << "• Set: set_union, set_intersection, set_difference" << endl;
    cout << "• Numeric: accumulate, inner_product, partial_sum" << endl;
    cout << "• Custom comparators enable flexible sorting" << endl;
    cout << "• Algorithms can be composed for complex operations" << endl;

    return 0;
}