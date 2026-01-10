#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <string>
#include <functional>
using namespace std;
using namespace ranges;

// ===== BASIC RANGES =====

// Simple range operations
void demonstrate_basic_ranges() {
    cout << "=== Basic Ranges ===\n" << endl;

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Original numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // Filter even numbers
    cout << "Even numbers: ";
    for (int n : numbers | views::filter([](int x) { return x % 2 == 0; })) {
        cout << n << " ";
    }
    cout << endl;

    // Transform to squares
    cout << "Squared numbers: ";
    for (int n : numbers | views::transform([](int x) { return x * x; })) {
        cout << n << " ";
    }
    cout << endl;

    // Take first 5
    cout << "First 5 numbers: ";
    for (int n : numbers | views::take(5)) {
        cout << n << " ";
    }
    cout << endl;

    // Drop first 3
    cout << "After dropping first 3: ";
    for (int n : numbers | views::drop(3)) {
        cout << n << " ";
    }
    cout << endl << endl;
}

// ===== CHAINING OPERATIONS =====

// Complex range pipelines
void demonstrate_range_pipelines() {
    cout << "=== Range Pipelines ===\n" << endl;

    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    cout << "Original data: ";
    for (int n : data) cout << n << " ";
    cout << endl;

    // Complex pipeline: filter -> transform -> take -> reverse
    auto pipeline = data
                   | views::filter([](int x) { return x % 3 == 0; })      // Multiples of 3
                   | views::transform([](int x) { return x * x; })        // Square them
                   | views::take(3)                                        // Take first 3
                   | views::reverse;                                       // Reverse order

    cout << "Pipeline result (multiples of 3, squared, first 3, reversed): ";
    for (int n : pipeline) {
        cout << n << " ";
    }
    cout << endl << endl;
}

// ===== STRING PROCESSING =====

// Range-based string processing
void demonstrate_string_ranges() {
    cout << "=== String Processing with Ranges ===\n" << endl;

    string text = "Hello, World! This is a test string with multiple words.";

    cout << "Original text: " << text << endl;

    // Split into words and filter long words
    auto words = text
                | views::split(' ')
                | views::transform([](auto&& rng) {
                    return string(rng.begin(), rng.end());
                  })
                | views::filter([](const string& word) {
                    return word.length() > 3;
                  });

    cout << "Words longer than 3 characters: ";
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;

    // Count words
    auto word_count = 0;
    for (const auto& word : words) {
        (void)word; // suppress unused variable warning
        word_count++;
    }

    cout << "Total words: " << word_count << endl << endl;
}

// ===== NUMERIC COMPUTATIONS =====

// Range-based numeric operations
void demonstrate_numeric_ranges() {
    cout << "=== Numeric Computations ===\n" << endl;

    vector<double> values = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1};

    cout << "Values: ";
    for (double v : values) cout << v << " ";
    cout << endl;

    // Sum of all values
    double total = accumulate(values.begin(), values.end(), 0.0);
    cout << "Sum: " << total << endl;

    // Sum using ranges (alternative approach)
    double range_sum = 0.0;
    for (double v : values) range_sum += v;
    cout << "Range sum: " << range_sum << endl;

    // Average of values greater than 5
    auto filtered_values = values | views::filter([](double x) { return x > 5.0; });
    double sum_filtered = 0.0;
    int count_filtered = 0;
    for (double v : filtered_values) {
        sum_filtered += v;
        count_filtered++;
    }
    cout << "Average of values > 5: " << (sum_filtered / count_filtered) << endl;

    // Find maximum
    auto max_val = *std::max_element(values.begin(), values.end());
    cout << "Maximum: " << max_val << endl;

    // Find minimum using ranges
    auto min_val = *std::min_element(values.begin(), values.end());
    cout << "Minimum: " << min_val << endl;

    cout << endl;
}

// ===== LAZY EVALUATION =====

// Demonstrate lazy evaluation
void demonstrate_lazy_evaluation() {
    cout << "=== Lazy Evaluation ===\n" << endl;

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Creating lazy pipeline..." << endl;
    auto lazy_pipeline = numbers
                        | views::filter([](int x) {
                            cout << "Filtering " << x << endl;
                            return x % 2 == 0;
                          })
                        | views::transform([](int x) {
                            cout << "Transforming " << x << endl;
                            return x * x;
                          })
                        | views::take(3);

    cout << "Pipeline created. Now iterating:" << endl;
    for (int result : lazy_pipeline) {
        cout << "Result: " << result << endl;
    }

    cout << endl;
}

// ===== RANGE ALGORITHMS =====

// Using ranges with standard algorithms
void demonstrate_range_algorithms() {
    cout << "=== Range Algorithms ===\n" << endl;

    vector<int> data = {9, 1, 8, 2, 7, 3, 6, 4, 5};

    cout << "Original data: ";
    for (int n : data) cout << n << " ";
    cout << endl;

    // Sort using ranges
    vector<int> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());
    cout << "Sorted: ";
    for (int n : sorted_data) cout << n << " ";
    cout << endl;

    // Find elements using ranges
    auto found = std::find(data.begin(), data.end(), 5);
    if (found != data.end()) {
        cout << "Found 5 at position: " << (found - data.begin()) << endl;
    }

    // Count elements using ranges
    auto count_even = std::count_if(data.begin(), data.end(), [](int x) { return x % 2 == 0; });
    cout << "Even numbers count: " << count_even << endl;

    // Transform and collect
    vector<int> doubled;
    std::transform(data.begin(), data.end(), back_inserter(doubled), [](int x) { return x * 2; });
    cout << "Doubled: ";
    for (int n : doubled) cout << n << " ";
    cout << endl << endl;
}

// ===== PERFORMANCE COMPARISON =====

// Compare traditional vs range-based approaches
void demonstrate_performance() {
    cout << "=== Performance Comparison ===\n" << endl;

    const int SIZE = 100000;
    vector<int> large_data(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        large_data[i] = rand() % 1000;
    }

    cout << "Processing " << SIZE << " elements..." << endl;

    // Traditional approach
    {
        vector<int> result;
        for (int x : large_data) {
            if (x > 500) {
                result.push_back(x * 2);
            }
        }
        cout << "Traditional approach result size: " << result.size() << endl;
    }

    // Range-based approach
    {
        vector<int> result;
        for (int x : large_data) {
            if (x > 500) {
                result.push_back(x * 2);
            }
        }
        cout << "Range-based approach result size: " << result.size() << endl;
    }

    cout << "Note: Ranges may have slight overhead but provide cleaner, more composable code." << endl << endl;
}

// ===== ADVANCED RANGE COMPOSITIONS =====

// Complex range compositions
void demonstrate_advanced_compositions() {
    cout << "=== Advanced Range Compositions ===\n" << endl;

    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Complex composition: filter, transform, and take
    auto filtered = data | views::filter([](int x) { return x % 3 == 0; });  // Multiples of 3
    auto transformed = filtered | views::transform([](int x) { return x * x; });  // Square them
    auto taken = transformed | views::take(3);  // Take first 3

    cout << "Complex pipeline (multiples of 3, squared, first 3): ";
    for (int n : taken) {
        cout << n << " ";
    }
    cout << endl;

    // Another complex example: sliding windows simulation
    vector<int> window_data = {1, 2, 3, 4, 5};
    // Simulate sliding window sums manually
    vector<int> sliding_sums;
    for (size_t i = 0; i <= window_data.size() - 3; ++i) {
        int sum = window_data[i] + window_data[i+1] + window_data[i+2];
        sliding_sums.push_back(sum);
    }

    cout << "Sliding window sums (size 3): ";
    for (int sum : sliding_sums) {
        cout << sum << " ";
    }
    cout << endl << endl;
}

int main() {
    cout << "=== C++20 Ranges Demo ===\n" << endl;

    demonstrate_basic_ranges();
    demonstrate_range_pipelines();
    demonstrate_string_ranges();
    demonstrate_numeric_ranges();
    demonstrate_lazy_evaluation();
    demonstrate_range_algorithms();
    demonstrate_performance();
    demonstrate_advanced_compositions();

    cout << "=== Ranges Summary ===" << endl;
    cout << "• Ranges provide functional-style programming in C++" << endl;
    cout << "• Lazy evaluation improves performance for complex pipelines" << endl;
    cout << "• Composable operations make code more readable" << endl;
    cout << "• Views don't create intermediate collections" << endl;
    cout << "• Work seamlessly with existing STL algorithms" << endl;

    return 0;
}