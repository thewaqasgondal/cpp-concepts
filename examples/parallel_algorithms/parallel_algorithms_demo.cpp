#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <chrono>
#include <random>
#include <functional>
#include <cmath>
using namespace std;
using namespace chrono;

// ===== BASIC PARALLEL ALGORITHMS =====

// Sequential vs parallel sort comparison
void demonstrate_parallel_sort() {
    cout << "=== Parallel Sort ===\n" << endl;

    const int SIZE = 1000000;
    vector<int> data(SIZE);

    // Fill with random data
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);

    generate(data.begin(), data.end(), [&]() { return dis(gen); });

    cout << "Sorting " << SIZE << " elements..." << endl;

    // Sequential sort
    vector<int> seq_data = data;
    auto start = high_resolution_clock::now();
    sort(seq_data.begin(), seq_data.end());
    auto end = high_resolution_clock::now();
    auto seq_duration = duration_cast<milliseconds>(end - start);

    cout << "Sequential sort: " << seq_duration.count() << "ms" << endl;

    // Parallel sort
    vector<int> par_data = data;
    start = high_resolution_clock::now();
    sort(execution::par, par_data.begin(), par_data.end());
    end = high_resolution_clock::now();
    auto par_duration = duration_cast<milliseconds>(end - start);

    cout << "Parallel sort: " << par_duration.count() << "ms" << endl;

    // Verify results are the same
    bool results_match = equal(seq_data.begin(), seq_data.end(), par_data.begin());
    cout << "Results match: " << (results_match ? "Yes" : "No") << endl;

    double speedup = static_cast<double>(seq_duration.count()) / par_duration.count();
    cout << "Speedup: " << speedup << "x" << endl << endl;
}

// ===== PARALLEL TRANSFORM =====

// Parallel transform operations
void demonstrate_parallel_transform() {
    cout << "=== Parallel Transform ===\n" << endl;

    const int SIZE = 100000;
    vector<double> input(SIZE);

    // Fill with random data
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 100.0);

    generate(input.begin(), input.end(), [&]() { return dis(gen); });

    vector<double> output_seq(SIZE);
    vector<double> output_par(SIZE);

    cout << "Transforming " << SIZE << " elements (computing square roots)..." << endl;

    // Sequential transform
    auto start = high_resolution_clock::now();
    transform(input.begin(), input.end(), output_seq.begin(),
              [](double x) { return sqrt(x * x + 1.0); });
    auto end = high_resolution_clock::now();
    auto seq_duration = duration_cast<microseconds>(end - start);

    cout << "Sequential transform: " << seq_duration.count() << "μs" << endl;

    // Parallel transform
    start = high_resolution_clock::now();
    transform(execution::par, input.begin(), input.end(), output_par.begin(),
              [](double x) { return sqrt(x * x + 1.0); });
    end = high_resolution_clock::now();
    auto par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel transform: " << par_duration.count() << "μs" << endl;

    // Verify results
    bool results_match = true;
    for (size_t i = 0; i < SIZE; ++i) {
        if (abs(output_seq[i] - output_par[i]) > 1e-10) {
            results_match = false;
            break;
        }
    }
    cout << "Results match: " << (results_match ? "Yes" : "No") << endl;

    cout << "Sample results:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "  sqrt(" << input[i] << "^2 + 1) = " << output_par[i] << endl;
    }
    cout << endl;
}

// ===== PARALLEL REDUCE/ACCUMULATE =====

// Parallel reduction operations
void demonstrate_parallel_reduce() {
    cout << "=== Parallel Reduce ===\n" << endl;

    const int SIZE = 1000000;
    vector<int> data(SIZE);

    // Fill with random data
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    generate(data.begin(), data.end(), [&]() { return dis(gen); });

    cout << "Reducing " << SIZE << " elements..." << endl;

    // Sequential reduce (accumulate)
    auto start = high_resolution_clock::now();
    int seq_sum = accumulate(data.begin(), data.end(), 0);
    auto end = high_resolution_clock::now();
    auto seq_duration = duration_cast<microseconds>(end - start);

    cout << "Sequential reduce: " << seq_duration.count() << "μs, sum = " << seq_sum << endl;

    // Parallel reduce
    start = high_resolution_clock::now();
    int par_sum = reduce(execution::par, data.begin(), data.end(), 0);
    end = high_resolution_clock::now();
    auto par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel reduce: " << par_duration.count() << "μs, sum = " << par_sum << endl;

    cout << "Results match: " << (seq_sum == par_sum ? "Yes" : "No") << endl;

    // Custom reduction with multiplication
    start = high_resolution_clock::now();
    long long seq_product = accumulate(data.begin(), data.begin() + 1000, 1LL,
                                       [](long long acc, int x) { return acc * (x % 10 + 1); });
    end = high_resolution_clock::now();
    seq_duration = duration_cast<microseconds>(end - start);

    cout << "Sequential custom reduce (first 1000 elements): " << seq_duration.count() << "μs" << endl;

    start = high_resolution_clock::now();
    long long par_product = reduce(execution::par, data.begin(), data.begin() + 1000, 1LL,
                                    [](long long acc, int x) { return acc * (x % 10 + 1); });
    end = high_resolution_clock::now();
    par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel custom reduce (first 1000 elements): " << par_duration.count() << "μs" << endl;
    cout << "Results match: " << (seq_product == par_product ? "Yes" : "No") << endl << endl;
}

// ===== PARALLEL FOR_EACH =====

// Parallel for_each operations
void demonstrate_parallel_for_each() {
    cout << "=== Parallel For Each ===\n" << endl;

    const int SIZE = 100000;
    vector<int> data(SIZE);

    // Fill with sequential numbers
    iota(data.begin(), data.end(), 0);

    vector<int> seq_results(SIZE);
    vector<int> par_results(SIZE);

    cout << "Processing " << SIZE << " elements with for_each..." << endl;

    // Sequential for_each
    auto start = high_resolution_clock::now();
    for_each(data.begin(), data.end(), [&](int& x) {
        seq_results[x] = x * x + 1;
    });
    auto end = high_resolution_clock::now();
    auto seq_duration = duration_cast<microseconds>(end - start);

    cout << "Sequential for_each: " << seq_duration.count() << "μs" << endl;

    // Parallel for_each
    start = high_resolution_clock::now();
    for_each(execution::par, data.begin(), data.end(), [&](int& x) {
        par_results[x] = x * x + 1;
    });
    end = high_resolution_clock::now();
    auto par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel for_each: " << par_duration.count() << "μs" << endl;

    // Verify results
    bool results_match = equal(seq_results.begin(), seq_results.end(), par_results.begin());
    cout << "Results match: " << (results_match ? "Yes" : "No") << endl;

    cout << "Sample results:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "  " << i << " -> " << par_results[i] << endl;
    }
    cout << endl;
}

// ===== PARALLEL COUNT AND FIND =====

// Parallel count and find operations
void demonstrate_parallel_count_find() {
    cout << "=== Parallel Count and Find ===\n" << endl;

    const int SIZE = 1000000;
    vector<int> data(SIZE);

    // Fill with random data
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    generate(data.begin(), data.end(), [&]() { return dis(gen); });

    cout << "Searching in " << SIZE << " elements..." << endl;

    // Parallel count
    auto start = high_resolution_clock::now();
    auto count_even = count_if(execution::par, data.begin(), data.end(),
                               [](int x) { return x % 2 == 0; });
    auto end = high_resolution_clock::now();
    auto par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel count_if (even numbers): " << par_duration.count() << "μs, count = " << count_even << endl;

    // Parallel find
    start = high_resolution_clock::now();
    auto found = find_if(execution::par, data.begin(), data.end(),
                         [](int x) { return x == 42; });
    end = high_resolution_clock::now();
    par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel find_if (value 42): " << par_duration.count() << "μs, found = "
         << (found != data.end() ? "Yes" : "No") << endl;

    // Parallel any_of
    start = high_resolution_clock::now();
    bool has_large = any_of(execution::par, data.begin(), data.end(),
                            [](int x) { return x > 95; });
    end = high_resolution_clock::now();
    par_duration = duration_cast<microseconds>(end - start);

    cout << "Parallel any_of (values > 95): " << par_duration.count() << "μs, result = "
         << (has_large ? "Yes" : "No") << endl << endl;
}

// ===== COMPLEX PARALLEL PIPELINE =====

// Complex parallel processing pipeline
void demonstrate_parallel_pipeline() {
    cout << "=== Parallel Processing Pipeline ===\n" << endl;

    const int SIZE = 500000;
    vector<double> data(SIZE);

    // Fill with random data
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-10.0, 10.0);

    generate(data.begin(), data.end(), [&]() { return dis(gen); });

    cout << "Processing pipeline on " << SIZE << " elements..." << endl;
    cout << "Pipeline: filter(>0) -> transform(sin) -> transform(abs) -> sort" << endl;

    // Sequential pipeline
    vector<double> seq_result;
    auto start = high_resolution_clock::now();

    for (double x : data) {
        if (x > 0) {
            double val = sin(x);
            seq_result.push_back(abs(val));
        }
    }
    sort(seq_result.begin(), seq_result.end());

    auto end = high_resolution_clock::now();
    auto seq_duration = duration_cast<milliseconds>(end - start);

    cout << "Sequential pipeline: " << seq_duration.count() << "ms, results = " << seq_result.size() << endl;

    // Parallel pipeline
    vector<double> par_result;
    start = high_resolution_clock::now();

    // Filter positive values
    vector<double> filtered;
    copy_if(execution::par, data.begin(), data.end(), back_inserter(filtered),
            [](double x) { return x > 0; });

    // Transform with sin
    vector<double> transformed(filtered.size());
    transform(execution::par, filtered.begin(), filtered.end(), transformed.begin(),
              [](double x) { return sin(x); });

    // Transform with abs
    transform(execution::par, transformed.begin(), transformed.end(), transformed.begin(),
              [](double x) { return abs(x); });

    // Sort
    sort(execution::par, transformed.begin(), transformed.end());
    par_result = move(transformed);

    end = high_resolution_clock::now();
    auto par_duration = duration_cast<milliseconds>(end - start);

    cout << "Parallel pipeline: " << par_duration.count() << "ms, results = " << par_result.size() << endl;

    // Verify results are approximately the same (sorting may differ for equal elements)
    bool sizes_match = seq_result.size() == par_result.size();
    cout << "Result sizes match: " << (sizes_match ? "Yes" : "No") << endl;

    if (!seq_result.empty() && !par_result.empty()) {
        cout << "First few results:" << endl;
        cout << "  Sequential: ";
        for (size_t i = 0; i < min(5UL, seq_result.size()); ++i) {
            cout << seq_result[i] << " ";
        }
        cout << endl;
        cout << "  Parallel:   ";
        for (size_t i = 0; i < min(5UL, par_result.size()); ++i) {
            cout << par_result[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ===== EXECUTION POLICY COMPARISON =====

// Compare different execution policies
void demonstrate_execution_policies() {
    cout << "=== Execution Policy Comparison ===\n" << endl;

    const int SIZE = 100000;
    vector<int> data(SIZE);
    iota(data.begin(), data.end(), 0);

    vector<long long> results_seq(SIZE);
    vector<long long> results_par(SIZE);
    vector<long long> results_par_unseq(SIZE);

    auto computation = [](int x) -> long long {
        long long result = 1;
        for (int i = 1; i <= min(20, x + 1); ++i) {
            result *= i;
        }
        return result;
    };

    cout << "Computing factorial-like function on " << SIZE << " elements..." << endl;

    // Sequential
    auto start = high_resolution_clock::now();
    transform(data.begin(), data.end(), results_seq.begin(), computation);
    auto end = high_resolution_clock::now();
    auto seq_duration = duration_cast<milliseconds>(end - start);

    cout << "Sequential: " << seq_duration.count() << "ms" << endl;

    // Parallel
    start = high_resolution_clock::now();
    transform(execution::par, data.begin(), data.end(), results_par.begin(), computation);
    end = high_resolution_clock::now();
    auto par_duration = duration_cast<milliseconds>(end - start);

    cout << "Parallel: " << par_duration.count() << "ms" << endl;

    // Parallel unsequenced
    start = high_resolution_clock::now();
    transform(execution::par_unseq, data.begin(), data.end(), results_par_unseq.begin(), computation);
    end = high_resolution_clock::now();
    auto par_unseq_duration = duration_cast<milliseconds>(end - start);

    cout << "Parallel unsequenced: " << par_unseq_duration.count() << "ms" << endl;

    // Verify results
    bool par_match = equal(results_seq.begin(), results_seq.end(), results_par.begin());
    bool par_unseq_match = equal(results_seq.begin(), results_seq.end(), results_par_unseq.begin());

    cout << "Parallel results match: " << (par_match ? "Yes" : "No") << endl;
    cout << "Parallel unsequenced results match: " << (par_unseq_match ? "Yes" : "No") << endl;

    cout << "Sample results (x -> f(x)):" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "  " << i << " -> " << results_seq[i] << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== C++17 Parallel Algorithms Demo ===\n" << endl;

    demonstrate_parallel_sort();
    demonstrate_parallel_transform();
    demonstrate_parallel_reduce();
    demonstrate_parallel_for_each();
    demonstrate_parallel_count_find();
    demonstrate_parallel_pipeline();
    demonstrate_execution_policies();

    cout << "=== Parallel Algorithms Summary ===" << endl;
    cout << "• Parallel algorithms use execution::par policy for parallel execution" << endl;
    cout << "• execution::par_unseq allows vectorization and reordering" << endl;
    cout << "• Parallel speedup depends on problem size and hardware" << endl;
    cout << "• Not all algorithms benefit from parallelization" << endl;
    cout << "• Thread safety is guaranteed for parallel algorithms" << endl;
    cout << "• Results are identical to sequential versions" << endl;

    return 0;
}