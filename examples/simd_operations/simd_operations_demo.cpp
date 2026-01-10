#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <functional>
using namespace std;
using namespace chrono;

// ===== BASIC SIMD CONCEPTS =====

// Demonstrate SIMD concepts without intrinsics
void demonstrate_simd_concepts() {
    cout << "=== SIMD Concepts ===\n" << endl;

    cout << "SIMD (Single Instruction, Multiple Data) allows processing multiple data elements simultaneously." << endl;
    cout << "Benefits:" << endl;
    cout << "• Parallel processing of data elements" << endl;
    cout << "• Better CPU utilization" << endl;
    cout << "• Performance gains for data-parallel operations" << endl;
    cout << "• Automatic vectorization by compiler" << endl;
    cout << "• Manual control with intrinsics" << endl << endl;

    // Simple vectorizable loop
    const int SIZE = 1000000;
    vector<float> a(SIZE), b(SIZE), c(SIZE);

    // Initialize data
    for (int i = 0; i < SIZE; ++i) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(i * 2);
    }

    cout << "Performing vector addition: c[i] = a[i] + b[i]" << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        c[i] = a[i] + b[i];
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << "Sample results: c[0] = " << c[0] << ", c[1] = " << c[1] << ", c[999999] = " << c[999999] << endl;
    cout << "Note: Modern compilers may auto-vectorize this loop." << endl << endl;
}

// ===== COMPILER VECTORIZATION =====

// Demonstrate compiler vectorization hints
void demonstrate_compiler_vectorization() {
    cout << "=== Compiler Vectorization ===\n" << endl;

    const int SIZE = 1000000;
    vector<float> data(SIZE);

    // Initialize with some pattern
    for (int i = 0; i < SIZE; ++i) {
        data[i] = sin(static_cast<float>(i) * 0.01f);
    }

    vector<float> result(SIZE);

    cout << "Computing element-wise operations that can be vectorized..." << endl;

    // This loop is likely to be vectorized by the compiler
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        result[i] = data[i] * data[i] + 2.0f * data[i] + 1.0f;  // (x^2 + 2x + 1)
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Vectorizable computation time: " << duration.count() << " microseconds" << endl;

    // Non-vectorizable version (with dependencies)
    vector<float> result2(SIZE);
    start = high_resolution_clock::now();
    float accumulator = 0.0f;
    for (int i = 0; i < SIZE; ++i) {
        accumulator += data[i];  // Loop-carried dependency
        result2[i] = accumulator;
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);

    cout << "Non-vectorizable computation time: " << duration.count() << " microseconds" << endl;
    cout << "Note: The second loop has dependencies that prevent vectorization." << endl << endl;
}

// ===== SIMD WITH ARRAYS =====

// Using arrays for better SIMD optimization
void demonstrate_simd_arrays() {
    cout << "=== SIMD with Arrays ===\n" << endl;

    const int SIZE = 1000000;
    array<float, 1000000> a{}, b{}, c{};

    // Initialize
    for (int i = 0; i < SIZE; ++i) {
        a[i] = static_cast<float>(i + 1);
        b[i] = 1.0f / a[i];
    }

    cout << "Array-based computation (better for SIMD)..." << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        c[i] = a[i] * b[i] - 1.0f;  // Should be approximately 0
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << "Sample: a[0] * b[0] - 1 = " << c[0] << " (should be ~0)" << endl;
    cout << "Sample: a[999] * b[999] - 1 = " << c[999] << " (should be ~0)" << endl << endl;
}

// ===== STRUCTURE OF ARRAYS =====

// Structure of Arrays (SoA) vs Array of Structures (AoS)
void demonstrate_soa_aos() {
    cout << "=== Structure of Arrays (SoA) vs Array of Structures (AoS) ===\n" << endl;

    const int SIZE = 500000;

    // Array of Structures (AoS)
    struct Particle_AoS {
        float x, y, z, mass;
    };
    vector<Particle_AoS> particles_aos(SIZE);

    // Structure of Arrays (SoA)
    struct Particles_SoA {
        vector<float> x, y, z, mass;
    };
    Particles_SoA particles_soa;
    particles_soa.x.resize(SIZE);
    particles_soa.y.resize(SIZE);
    particles_soa.z.resize(SIZE);
    particles_soa.mass.resize(SIZE);

    // Initialize data
    for (int i = 0; i < SIZE; ++i) {
        float val = static_cast<float>(i);
        particles_aos[i] = {val, val * 2, val * 3, val * 0.1f};
        particles_soa.x[i] = val;
        particles_soa.y[i] = val * 2;
        particles_soa.z[i] = val * 3;
        particles_soa.mass[i] = val * 0.1f;
    }

    // AoS computation
    cout << "Array of Structures (AoS) computation..." << endl;
    auto start = high_resolution_clock::now();
    for (auto& p : particles_aos) {
        p.x += p.mass;
        p.y += p.mass;
        p.z += p.mass;
    }
    auto end = high_resolution_clock::now();
    auto aos_duration = duration_cast<microseconds>(end - start);

    cout << "AoS time: " << aos_duration.count() << " microseconds" << endl;

    // SoA computation
    cout << "Structure of Arrays (SoA) computation..." << endl;
    start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        particles_soa.x[i] += particles_soa.mass[i];
        particles_soa.y[i] += particles_soa.mass[i];
        particles_soa.z[i] += particles_soa.mass[i];
    }
    end = high_resolution_clock::now();
    auto soa_duration = duration_cast<microseconds>(end - start);

    cout << "SoA time: " << soa_duration.count() << " microseconds" << endl;

    double speedup = static_cast<double>(aos_duration.count()) / soa_duration.count();
    cout << "SoA speedup: " << speedup << "x" << endl;
    cout << "SoA is often faster due to better memory access patterns for SIMD." << endl << endl;
}

// ===== SIMD-FRIENDLY ALGORITHMS =====

// Algorithms designed for SIMD processing
void demonstrate_simd_friendly_algorithms() {
    cout << "=== SIMD-Friendly Algorithms ===\n" << endl;

    const int SIZE = 1000000;
    vector<float> data(SIZE);

    // Initialize with alternating positive/negative values
    for (int i = 0; i < SIZE; ++i) {
        data[i] = (i % 2 == 0) ? static_cast<float>(i) : -static_cast<float>(i);
    }

    // Branchless absolute value (SIMD-friendly)
    cout << "Computing absolute values (branchless vs branching)..." << endl;

    vector<float> abs_branchless(SIZE);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        // Branchless: using sign bit manipulation
        uint32_t bits = *reinterpret_cast<uint32_t*>(&data[i]);
        bits &= 0x7FFFFFFF;  // Clear sign bit
        abs_branchless[i] = *reinterpret_cast<float*>(&bits);
    }
    auto end = high_resolution_clock::now();
    auto branchless_duration = duration_cast<microseconds>(end - start);

    cout << "Branchless absolute value: " << branchless_duration.count() << " microseconds" << endl;

    vector<float> abs_branching(SIZE);
    start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        // Branching version
        abs_branching[i] = (data[i] >= 0) ? data[i] : -data[i];
    }
    end = high_resolution_clock::now();
    auto branching_duration = duration_cast<microseconds>(end - start);

    cout << "Branching absolute value: " << branching_duration.count() << " microseconds" << endl;

    // Verify results match
    bool results_match = true;
    for (int i = 0; i < SIZE; ++i) {
        if (abs(abs_branchless[i] - abs_branching[i]) > 1e-6f) {
            results_match = false;
            break;
        }
    }
    cout << "Results match: " << (results_match ? "Yes" : "No") << endl;

    // Horizontal operations (sum of array)
    cout << "\nComputing sum of array..." << endl;
    start = high_resolution_clock::now();
    float sum = 0.0f;
    for (float val : data) {
        sum += abs(val);  // Using absolute values
    }
    end = high_resolution_clock::now();
    auto sum_duration = duration_cast<microseconds>(end - start);

    cout << "Sum computation: " << sum_duration.count() << " microseconds" << endl;
    cout << "Sum result: " << sum << endl << endl;
}

// ===== MEMORY ALIGNMENT =====

// Demonstrate memory alignment for SIMD
void demonstrate_memory_alignment() {
    cout << "=== Memory Alignment for SIMD ===\n" << endl;

    cout << "SIMD operations often require aligned memory for optimal performance." << endl;

    const int SIZE = 1000000;
    const int ALIGNMENT = 32;  // AVX alignment requirement

    // Aligned allocation
    float* aligned_data = static_cast<float*>(aligned_alloc(ALIGNMENT, SIZE * sizeof(float)));
    float* unaligned_data = new float[SIZE];

    // Initialize
    for (int i = 0; i < SIZE; ++i) {
        aligned_data[i] = unaligned_data[i] = static_cast<float>(i % 100);
    }

    // Test alignment
    cout << "Aligned data pointer: " << aligned_data << endl;
    cout << "Unaligned data pointer: " << unaligned_data << endl;
    cout << "Alignment requirement: " << ALIGNMENT << " bytes" << endl;
    cout << "Aligned data is " << ((reinterpret_cast<uintptr_t>(aligned_data) % ALIGNMENT == 0) ? "" : "not ") << "aligned" << endl;
    cout << "Unaligned data is " << ((reinterpret_cast<uintptr_t>(unaligned_data) % ALIGNMENT == 0) ? "" : "not ") << "aligned" << endl;

    // Computation on aligned data
    vector<float> result_aligned(SIZE);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        result_aligned[i] = sqrt(aligned_data[i] * aligned_data[i] + 1.0f);
    }
    auto end = high_resolution_clock::now();
    auto aligned_duration = duration_cast<microseconds>(end - start);

    cout << "Aligned computation: " << aligned_duration.count() << " microseconds" << endl;

    // Computation on unaligned data
    vector<float> result_unaligned(SIZE);
    start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        result_unaligned[i] = sqrt(unaligned_data[i] * unaligned_data[i] + 1.0f);
    }
    end = high_resolution_clock::now();
    auto unaligned_duration = duration_cast<microseconds>(end - start);

    cout << "Unaligned computation: " << unaligned_duration.count() << " microseconds" << endl;

    // Cleanup
    free(aligned_data);
    delete[] unaligned_data;

    cout << "Note: Alignment benefits vary by CPU and compiler." << endl << endl;
}

// ===== SIMD WIDTH DETECTION =====

// Detect SIMD capabilities
void demonstrate_simd_detection() {
    cout << "=== SIMD Capability Detection ===\n" << endl;

    cout << "Common SIMD instruction sets:" << endl;
    cout << "• SSE: 128-bit (4 floats, 2 doubles)" << endl;
    cout << "• AVX: 256-bit (8 floats, 4 doubles)" << endl;
    cout << "• AVX-512: 512-bit (16 floats, 8 doubles)" << endl;
    cout << "• NEON: ARM SIMD (varies by architecture)" << endl << endl;

    // In a real implementation, you would use CPUID or similar
    // to detect available instruction sets at runtime
    cout << "Runtime SIMD detection would check CPU capabilities." << endl;
    cout << "This allows choosing optimal code paths for different hardware." << endl << endl;
}

// ===== PERFORMANCE COMPARISON =====

// Comprehensive performance comparison
void demonstrate_performance_comparison() {
    cout << "=== SIMD Performance Comparison ===\n" << endl;

    const int SIZE = 2000000;

    // Test different data types and operations
    struct TestCase {
        string name;
        function<void()> func;
    };

    vector<TestCase> tests;

    // Float addition
    {
        vector<float> a(SIZE), b(SIZE), c(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            a[i] = b[i] = static_cast<float>(i % 1000);
        }

        TestCase tc{"Float Addition", [&]() {
            for (int i = 0; i < SIZE; ++i) {
                c[i] = a[i] + b[i];
            }
        }};
        tests.push_back(tc);
    }

    // Float multiplication
    {
        vector<float> a(SIZE), b(SIZE), c(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            a[i] = static_cast<float>(i) * 0.001f;
            b[i] = static_cast<float>(i) * 0.002f;
        }

        TestCase tc{"Float Multiplication", [&]() {
            for (int i = 0; i < SIZE; ++i) {
                c[i] = a[i] * b[i];
            }
        }};
        tests.push_back(tc);
    }

    // Trigonometric functions
    {
        vector<float> a(SIZE), b(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            a[i] = static_cast<float>(i) * 0.01f;
        }

        TestCase tc{"Sine Computation", [&]() {
            for (int i = 0; i < SIZE; ++i) {
                b[i] = sin(a[i]);
            }
        }};
        tests.push_back(tc);
    }

    // Run tests
    for (auto& test : tests) {
        cout << "Running " << test.name << " on " << SIZE << " elements..." << endl;

        auto start = high_resolution_clock::now();
        test.func();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        cout << "  Time: " << duration.count() << " microseconds" << endl;
        cout << "  Throughput: " << (SIZE * 1000000.0 / duration.count()) << " operations/second" << endl;
    }

    cout << "\nNote: Actual SIMD performance depends on:" << endl;
    cout << "• Compiler optimization level (-O3, -march=native)" << endl;
    cout << "• CPU microarchitecture" << endl;
    cout << "• Memory bandwidth" << endl;
    cout << "• Cache hierarchy" << endl;
    cout << "• Data alignment" << endl << endl;
}

int main() {
    cout << "=== SIMD Operations Demo ===\n" << endl;

    demonstrate_simd_concepts();
    demonstrate_compiler_vectorization();
    demonstrate_simd_arrays();
    demonstrate_soa_aos();
    demonstrate_simd_friendly_algorithms();
    demonstrate_memory_alignment();
    demonstrate_simd_detection();
    demonstrate_performance_comparison();

    cout << "=== SIMD Summary ===" << endl;
    cout << "• SIMD enables parallel processing of multiple data elements" << endl;
    cout << "• Compiler auto-vectorization can provide significant speedups" << endl;
    cout << "• Structure of Arrays (SoA) is often better than Array of Structures (AoS)" << endl;
    cout << "• Memory alignment is crucial for optimal SIMD performance" << endl;
    cout << "• Avoid branches and loop-carried dependencies" << endl;
    cout << "• Use -march=native and -O3 for best SIMD utilization" << endl;
    cout << "• Profile and measure to ensure SIMD is actually being used" << endl;

    return 0;
}