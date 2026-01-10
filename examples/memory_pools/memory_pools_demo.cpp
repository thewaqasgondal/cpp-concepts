#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <new>
#include <cstring>
using namespace std;

// ===== MEMORY POOL IMPLEMENTATION =====
class MemoryPool {
private:
    struct Block {
        Block* next;
    };

    size_t blockSize;
    size_t blockCount;
    char* pool;
    Block* freeList;

public:
    MemoryPool(size_t blockSize, size_t blockCount)
        : blockSize(blockSize), blockCount(blockCount), freeList(nullptr) {

        // Allocate the entire pool
        pool = new char[blockSize * blockCount];

        // Initialize free list
        for (size_t i = 0; i < blockCount; ++i) {
            Block* block = reinterpret_cast<Block*>(&pool[i * blockSize]);
            block->next = freeList;
            freeList = block;
        }
    }

    ~MemoryPool() {
        delete[] pool;
    }

    void* allocate() {
        if (!freeList) {
            throw bad_alloc();
        }

        Block* block = freeList;
        freeList = freeList->next;
        return block;
    }

    void deallocate(void* ptr) {
        if (!ptr) return;

        // Check if pointer is within our pool
        char* charPtr = static_cast<char*>(ptr);
        if (charPtr < pool || charPtr >= pool + (blockSize * blockCount)) {
            return; // Not our memory
        }

        // Return to free list
        Block* block = static_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }

    size_t getBlockSize() const { return blockSize; }
    size_t getBlockCount() const { return blockCount; }
};

// ===== OBJECT POOL FOR SPECIFIC TYPES =====
template<typename T>
class ObjectPool {
private:
    MemoryPool pool;
    size_t objectSize;

public:
    ObjectPool(size_t count)
        : pool(sizeof(T), count), objectSize(sizeof(T)) {}

    template<typename... Args>
    T* allocate(Args&&... args) {
        void* memory = pool.allocate();
        return new(memory) T(forward<Args>(args)...);
    }

    void deallocate(T* obj) {
        if (!obj) return;
        obj->~T(); // Call destructor
        pool.deallocate(obj);
    }

    size_t capacity() const { return pool.getBlockCount(); }
};

// ===== ARENA ALLOCATOR =====
class ArenaAllocator {
private:
    vector<char*> blocks;
    size_t blockSize;
    size_t currentOffset;
    char* currentBlock;

    void allocateNewBlock() {
        currentBlock = new char[blockSize];
        blocks.push_back(currentBlock);
        currentOffset = 0;
    }

public:
    ArenaAllocator(size_t blockSize = 4096)
        : blockSize(blockSize), currentOffset(0), currentBlock(nullptr) {
        allocateNewBlock();
    }

    ~ArenaAllocator() {
        for (char* block : blocks) {
            delete[] block;
        }
    }

    void* allocate(size_t size, size_t alignment = alignof(max_align_t)) {
        // Align the offset
        size_t alignedOffset = (currentOffset + alignment - 1) & ~(alignment - 1);

        if (alignedOffset + size > blockSize) {
            allocateNewBlock();
            alignedOffset = 0;
        }

        void* ptr = currentBlock + alignedOffset;
        currentOffset = alignedOffset + size;
        return ptr;
    }

    void reset() {
        currentOffset = 0;
        // Keep the first block, reset offset
        if (!blocks.empty()) {
            currentBlock = blocks[0];
        }
    }

    size_t totalAllocated() const {
        return blocks.size() * blockSize;
    }
};

// ===== DEMONSTRATION =====

// Simple test class
class TestObject {
private:
    int id;
    string name;
    vector<int> data;

public:
    TestObject(int id, const string& name, const vector<int>& data)
        : id(id), name(name), data(data) {}

    ~TestObject() {
        cout << "TestObject " << id << " destroyed" << endl;
    }

    void display() const {
        cout << "Object " << id << ": " << name << " (data size: " << data.size() << ")" << endl;
    }
};

void demonstrateMemoryPool() {
    cout << "=== Memory Pool Demo ===\n" << endl;

    // Create a memory pool for 10 blocks of 64 bytes each
    MemoryPool pool(64, 10);

    cout << "Memory pool created with " << pool.getBlockCount()
         << " blocks of " << pool.getBlockSize() << " bytes each" << endl;

    // Allocate some memory
    vector<void*> allocations;
    try {
        for (int i = 0; i < 5; ++i) {
            void* ptr = pool.allocate();
            allocations.push_back(ptr);
            cout << "Allocated block " << i << " at " << ptr << endl;
        }
    } catch (const bad_alloc&) {
        cout << "Memory pool exhausted!" << endl;
    }

    // Deallocate some memory
    for (size_t i = 0; i < allocations.size(); i += 2) {
        pool.deallocate(allocations[i]);
        cout << "Deallocated block " << i << endl;
    }

    // Allocate again (should reuse freed blocks)
    try {
        void* ptr = pool.allocate();
        cout << "Reallocated block at " << ptr << endl;
        pool.deallocate(ptr);
    } catch (const bad_alloc&) {
        cout << "Failed to reallocate" << endl;
    }
}

void demonstrateObjectPool() {
    cout << "\n=== Object Pool Demo ===\n" << endl;

    ObjectPool<TestObject> objPool(5);

    cout << "Object pool created with capacity: " << objPool.capacity() << endl;

    // Allocate objects
    vector<TestObject*> objects;
    for (int i = 0; i < 3; ++i) {
        vector<int> data = {i * 10, i * 20, i * 30};
        TestObject* obj = objPool.allocate(i, "Object" + to_string(i), data);
        objects.push_back(obj);
        cout << "Created ";
        obj->display();
    }

    // Use objects
    for (auto obj : objects) {
        obj->display();
    }

    // Deallocate objects
    for (auto obj : objects) {
        objPool.deallocate(obj);
        cout << "Object deallocated" << endl;
    }
}

void demonstrateArenaAllocator() {
    cout << "\n=== Arena Allocator Demo ===\n" << endl;

    ArenaAllocator arena(1024); // 1KB blocks

    cout << "Arena allocator created with 1KB blocks" << endl;

    // Allocate various sizes
    vector<void*> allocations;
    for (int i = 0; i < 10; ++i) {
        size_t size = 50 + (i * 10); // 50, 60, 70, ... bytes
        void* ptr = arena.allocate(size);
        allocations.push_back(ptr);
        cout << "Allocated " << size << " bytes at " << ptr << endl;
    }

    cout << "Total arena size: " << arena.totalAllocated() << " bytes" << endl;

    // Reset arena (all allocations become invalid)
    arena.reset();
    cout << "Arena reset - all previous allocations are now invalid" << endl;

    // Allocate again
    void* newPtr = arena.allocate(100);
    cout << "New allocation after reset at " << newPtr << endl;
}

void performanceComparison() {
    cout << "\n=== Performance Comparison ===\n" << endl;

    const int NUM_ALLOCATIONS = 10000;
    const size_t OBJECT_SIZE = sizeof(TestObject);

    // Time standard new/delete
    auto start = chrono::high_resolution_clock::now();

    vector<TestObject*> standardObjects;
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        vector<int> data = {i};
        standardObjects.push_back(new TestObject(i, "Standard", data));
    }

    for (auto obj : standardObjects) {
        delete obj;
    }

    auto end = chrono::high_resolution_clock::now();
    auto standardTime = chrono::duration_cast<chrono::microseconds>(end - start);

    // Time object pool
    start = chrono::high_resolution_clock::now();

    ObjectPool<TestObject> pool(NUM_ALLOCATIONS);
    vector<TestObject*> poolObjects;

    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        vector<int> data = {i};
        poolObjects.push_back(pool.allocate(i, "Pool", data));
    }

    for (auto obj : poolObjects) {
        pool.deallocate(obj);
    }

    end = chrono::high_resolution_clock::now();
    auto poolTime = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Performance comparison (" << NUM_ALLOCATIONS << " allocations):\n";
    cout << "Standard new/delete: " << standardTime.count() << " microseconds\n";
    cout << "Object pool:         " << poolTime.count() << " microseconds\n";
    cout << "Speedup: " << (double)standardTime.count() / poolTime.count() << "x" << endl;
}

int main() {
    cout << "=== C++ Memory Management Demo ===\n" << endl;

    demonstrateMemoryPool();
    demonstrateObjectPool();
    demonstrateArenaAllocator();
    performanceComparison();

    cout << "\n=== Summary ===" << endl;
    cout << "• Memory Pool: Efficient allocation/deallocation of fixed-size blocks" << endl;
    cout << "• Object Pool: Type-safe object reuse with constructor/destructor calls" << endl;
    cout << "• Arena Allocator: Fast allocation with bulk deallocation" << endl;
    cout << "• Choose based on your memory usage patterns and performance needs" << endl;

    return 0;
}