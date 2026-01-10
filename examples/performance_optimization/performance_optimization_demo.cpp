#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include <cstring>
using namespace std;

// ===== PROFILING UTILITIES =====
class Profiler {
private:
    chrono::high_resolution_clock::time_point start_time;
    string name;

public:
    Profiler(const string& name) : name(name) {
        start_time = chrono::high_resolution_clock::now();
    }

    ~Profiler() {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout << name << " took " << duration.count() << " microseconds" << endl;
    }
};

#define PROFILE_SCOPE(name) Profiler profiler(name)

// ===== CACHE-FRIENDLY DATA STRUCTURES =====

// Cache-unfriendly: Array of structs
struct ParticleAOS {
    float x, y, z;    // Position
    float vx, vy, vz; // Velocity
    float mass;       // Mass
};

// Cache-friendly: Struct of arrays
struct ParticleSOA {
    vector<float> x, y, z;
    vector<float> vx, vy, vz;
    vector<float> mass;
};

// ===== MATRIX OPERATIONS =====

// Naive matrix multiplication (cache-unfriendly)
void matrixMultiplyNaive(const vector<vector<float>>& A,
                        const vector<vector<float>>& B,
                        vector<vector<float>>& C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Cache-friendly matrix multiplication (blocked)
void matrixMultiplyBlocked(const vector<vector<float>>& A,
                          const vector<vector<float>>& B,
                          vector<vector<float>>& C, int N, int blockSize = 64) {
    for (int ii = 0; ii < N; ii += blockSize) {
        for (int jj = 0; jj < N; jj += blockSize) {
            for (int kk = 0; kk < N; kk += blockSize) {
                // Multiply blocks
                int iEnd = min(ii + blockSize, N);
                int jEnd = min(jj + blockSize, N);
                int kEnd = min(kk + blockSize, N);

                for (int i = ii; i < iEnd; ++i) {
                    for (int j = jj; j < jEnd; ++j) {
                        float sum = C[i][j];
                        for (int k = kk; k < kEnd; ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}

// ===== BRANCH PREDICTION OPTIMIZATION =====

// Branchy version (hard to predict)
int sumWithBranches(const vector<int>& data) {
    int sum = 0;
    for (int x : data) {
        if (x > 0) {        // Branch based on data
            sum += x;
        } else {
            sum -= x;
        }
    }
    return sum;
}

// Branchless version (predictable)
int sumBranchless(const vector<int>& data) {
    int sum = 0;
    for (int x : data) {
        // Use arithmetic instead of branches
        int sign = (x > 0) ? 1 : -1;
        sum += sign * abs(x);
    }
    return sum;
}

// ===== LOOP OPTIMIZATION =====

// Inefficient loop (multiple array accesses per iteration)
void processDataInefficient(vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = data[i] * 2 + data[(i + 1) % data.size()];
    }
}

// Optimized loop (single pass, cache-friendly)
void processDataOptimized(vector<int>& data) {
    if (data.empty()) return;

    int next = data[0]; // Cache first element
    for (size_t i = 0; i < data.size() - 1; ++i) {
        int current = data[i];
        int temp = data[i + 1];
        data[i] = current * 2 + temp;
        next = temp;
    }
    // Handle last element
    data.back() = data.back() * 2 + data[0];
}

// ===== MEMORY ACCESS PATTERNS =====

// Strided access (cache-unfriendly)
long long sumStrided(const vector<int>& data, int stride) {
    long long sum = 0;
    for (size_t i = 0; i < data.size(); i += stride) {
        sum += data[i];
    }
    return sum;
}

// Sequential access (cache-friendly)
long long sumSequential(const vector<int>& data) {
    long long sum = 0;
    for (int x : data) {
        sum += x;
    }
    return sum;
}

// ===== DEMONSTRATION =====

void demonstrateCacheFriendlyDataStructures() {
    cout << "=== Cache-Friendly Data Structures ===\n" << endl;

    const int NUM_PARTICLES = 10000;

    // Initialize AOS (Array of Structs)
    vector<ParticleAOS> particlesAOS(NUM_PARTICLES);
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        particlesAOS[i].x = i * 1.0f;
        particlesAOS[i].y = i * 2.0f;
        particlesAOS[i].z = i * 3.0f;
        particlesAOS[i].vx = i * 0.1f;
        particlesAOS[i].vy = i * 0.2f;
        particlesAOS[i].vz = i * 0.3f;
        particlesAOS[i].mass = 1.0f + i * 0.01f;
    }

    // Initialize SOA (Struct of Arrays)
    ParticleSOA particlesSOA;
    particlesSOA.x.resize(NUM_PARTICLES);
    particlesSOA.y.resize(NUM_PARTICLES);
    particlesSOA.z.resize(NUM_PARTICLES);
    particlesSOA.vx.resize(NUM_PARTICLES);
    particlesSOA.vy.resize(NUM_PARTICLES);
    particlesSOA.vz.resize(NUM_PARTICLES);
    particlesSOA.mass.resize(NUM_PARTICLES);

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        particlesSOA.x[i] = i * 1.0f;
        particlesSOA.y[i] = i * 2.0f;
        particlesSOA.z[i] = i * 3.0f;
        particlesSOA.vx[i] = i * 0.1f;
        particlesSOA.vy[i] = i * 0.2f;
        particlesSOA.vz[i] = i * 0.3f;
        particlesSOA.mass[i] = 1.0f + i * 0.01f;
    }

    // Benchmark AOS access (process only x coordinates)
    {
        PROFILE_SCOPE("AOS - Process X coordinates");
        float sum = 0;
        for (const auto& p : particlesAOS) {
            sum += p.x;
        }
    }

    // Benchmark SOA access (process only x coordinates)
    {
        PROFILE_SCOPE("SOA - Process X coordinates");
        float sum = 0;
        for (float x : particlesSOA.x) {
            sum += x;
        }
    }
}

void demonstrateMatrixMultiplication() {
    cout << "\n=== Matrix Multiplication Optimization ===\n" << endl;

    const int N = 256; // Matrix size

    // Initialize matrices
    vector<vector<float>> A(N, vector<float>(N));
    vector<vector<float>> B(N, vector<float>(N));
    vector<vector<float>> C1(N, vector<float>(N, 0));
    vector<vector<float>> C2(N, vector<float>(N, 0));

    // Fill with random data
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = dist(gen);
            B[i][j] = dist(gen);
        }
    }

    // Benchmark naive multiplication
    {
        PROFILE_SCOPE("Naive Matrix Multiplication");
        matrixMultiplyNaive(A, B, C1, N);
    }

    // Benchmark blocked multiplication
    {
        PROFILE_SCOPE("Blocked Matrix Multiplication");
        matrixMultiplyBlocked(A, B, C2, N);
    }

    // Verify results are similar
    float maxDiff = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            maxDiff = max(maxDiff, abs(C1[i][j] - C2[i][j]));
        }
    }
    cout << "Maximum difference between methods: " << maxDiff << endl;
}

void demonstrateBranchPrediction() {
    cout << "\n=== Branch Prediction Optimization ===\n" << endl;

    const int SIZE = 1000000;
    vector<int> data(SIZE);

    // Create data with pattern (mostly positive, some negative)
    for (int i = 0; i < SIZE; ++i) {
        data[i] = (i % 100 == 0) ? -i : i; // 1% negative values
    }

    // Benchmark branchy version
    int result1;
    {
        PROFILE_SCOPE("Branchy sum");
        result1 = sumWithBranches(data);
    }

    // Benchmark branchless version
    int result2;
    {
        PROFILE_SCOPE("Branchless sum");
        result2 = sumBranchless(data);
    }

    cout << "Branchy result: " << result1 << endl;
    cout << "Branchless result: " << result2 << endl;
    cout << "Results match: " << (result1 == result2 ? "Yes" : "No") << endl;
}

void demonstrateMemoryAccessPatterns() {
    cout << "\n=== Memory Access Patterns ===\n" << endl;

    const int SIZE = 1000000;
    vector<int> data(SIZE);

    // Initialize with sequential values
    iota(data.begin(), data.end(), 0);

    // Benchmark sequential access
    long long result1;
    {
        PROFILE_SCOPE("Sequential access");
        result1 = sumSequential(data);
    }

    // Benchmark strided access (stride = 16)
    long long result2;
    {
        PROFILE_SCOPE("Strided access (stride=16)");
        result2 = sumStrided(data, 16);
    }

    cout << "Sequential sum: " << result1 << endl;
    cout << "Strided sum: " << result2 << endl;
    cout << "Results match: " << (result1 == result2 ? "Yes" : "No") << endl;
}

void demonstrateLoopOptimization() {
    cout << "\n=== Loop Optimization ===\n" << endl;

    const int SIZE = 100000;
    vector<int> data1(SIZE), data2(SIZE);

    // Initialize test data
    iota(data1.begin(), data1.end(), 0);
    iota(data2.begin(), data2.end(), 0);

    // Benchmark inefficient version
    {
        PROFILE_SCOPE("Inefficient loop");
        processDataInefficient(data1);
    }

    // Benchmark optimized version
    {
        PROFILE_SCOPE("Optimized loop");
        processDataOptimized(data2);
    }

    // Verify results are the same
    bool resultsMatch = equal(data1.begin(), data1.end(), data2.begin());
    cout << "Results match: " << (resultsMatch ? "Yes" : "No") << endl;
}

int main() {
    cout << "=== C++ Performance Optimization Demo ===\n" << endl;

    demonstrateCacheFriendlyDataStructures();
    demonstrateMatrixMultiplication();
    demonstrateBranchPrediction();
    demonstrateMemoryAccessPatterns();
    demonstrateLoopOptimization();

    cout << "\n=== Performance Optimization Summary ===" << endl;
    cout << "• Cache-Friendly Data: SOA often faster than AOS for specific operations" << endl;
    cout << "• Matrix Multiplication: Blocking improves cache utilization" << endl;
    cout << "• Branch Prediction: Avoid branches when possible, use arithmetic" << endl;
    cout << "• Memory Access: Sequential access is much faster than strided access" << endl;
    cout << "• Loop Optimization: Minimize array accesses, cache values in registers" << endl;
    cout << "• Always profile your code to identify actual bottlenecks!" << endl;

    return 0;
}