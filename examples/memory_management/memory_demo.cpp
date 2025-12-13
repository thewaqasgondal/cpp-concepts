#include <iostream>
#include <memory>
using namespace std;

// Class to demonstrate memory management
class Resource {
private:
    string name;

public:
    Resource(string n) : name(n) {
        cout << "Resource '" << name << "' created" << endl;
    }

    ~Resource() {
        cout << "Resource '" << name << "' destroyed" << endl;
    }

    void use() {
        cout << "Using resource '" << name << "'" << endl;
    }
};

// Function that returns a raw pointer (dangerous!)
Resource* createResourceRaw(string name) {
    return new Resource(name);
}

// Function that returns a unique_ptr (safe)
unique_ptr<Resource> createResourceUnique(string name) {
    return make_unique<Resource>(name);
}

// Function that returns a shared_ptr (safe)
shared_ptr<Resource> createResourceShared(string name) {
    return make_shared<Resource>(name);
}

void demonstrateRawPointers() {
    cout << "\n=== Raw Pointers (Manual Memory Management) ===" << endl;

    // Single object
    cout << "1. Single object allocation:" << endl;
    int* ptr = new int;
    *ptr = 42;
    cout << "Value: " << *ptr << endl;
    delete ptr;
    ptr = nullptr;

    // Array allocation
    cout << "\n2. Array allocation:" << endl;
    int* arr = new int[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    delete[] arr;
    arr = nullptr;

    // Object allocation
    cout << "\n3. Object allocation:" << endl;
    Resource* res = createResourceRaw("Manual");
    res->use();
    delete res;  // Manual cleanup
    res = nullptr;
}

void demonstrateSmartPointers() {
    cout << "\n=== Smart Pointers (Automatic Memory Management) ===" << endl;

    // unique_ptr - exclusive ownership
    cout << "1. unique_ptr (exclusive ownership):" << endl;
    {
        unique_ptr<Resource> res1 = make_unique<Resource>("Unique1");
        res1->use();

        // Transfer ownership
        unique_ptr<Resource> res2 = move(res1);
        if (!res1) {
            cout << "res1 is now null" << endl;
        }
        res2->use();
        // res2 goes out of scope here, automatically deletes the resource
    }
    cout << "unique_ptr scope ended" << endl;

    // shared_ptr - shared ownership
    cout << "\n2. shared_ptr (shared ownership):" << endl;
    {
        shared_ptr<Resource> res1 = make_shared<Resource>("Shared1");
        cout << "Reference count: " << res1.use_count() << endl;

        {
            shared_ptr<Resource> res2 = res1;  // Share ownership
            cout << "Reference count after sharing: " << res1.use_count() << endl;
            res2->use();
            // res2 goes out of scope, but resource still exists
        }

        cout << "Reference count after inner scope: " << res1.use_count() << endl;
        res1->use();
        // res1 goes out of scope here, resource is deleted
    }
    cout << "shared_ptr scope ended" << endl;

    // weak_ptr - non-owning reference
    cout << "\n3. weak_ptr (non-owning reference):" << endl;
    {
        shared_ptr<Resource> shared = make_shared<Resource>("WeakDemo");
        weak_ptr<Resource> weak = shared;

        cout << "Shared pointer use count: " << shared.use_count() << endl;
        cout << "Weak pointer expired: " << weak.expired() << endl;

        if (auto locked = weak.lock()) {
            locked->use();
        }

        shared.reset();  // Release shared ownership
        cout << "After shared.reset(), weak expired: " << weak.expired() << endl;
    }
}

void demonstrateMemoryIssues() {
    cout << "\n=== Common Memory Issues ===" << endl;

    // Memory leak
    cout << "1. Memory Leak (commented out to avoid actual leak):" << endl;
    cout << "Resource* leak = new Resource(\"Leak\");" << endl;
    cout << "// Forgot to delete leak;" << endl;

    // Double deletion
    cout << "\n2. Double Deletion (commented out to avoid crash):" << endl;
    cout << "Resource* res = new Resource(\"DoubleDelete\");" << endl;
    cout << "// delete res;" << endl;
    cout << "// delete res; // CRASH!" << endl;

    // Dangling pointer
    cout << "\n3. Dangling Pointer (commented out to avoid undefined behavior):" << endl;
    cout << "int* dangling;" << endl;
    cout << "{ int x = 42; dangling = &x; }" << endl;
    cout << "// *dangling = 100; // UNDEFINED BEHAVIOR!" << endl;
}

void demonstrateRAII() {
    cout << "\n=== RAII (Resource Acquisition Is Initialization) ===" << endl;

    class FileHandler {
    private:
        FILE* file;

    public:
        FileHandler(const char* filename) {
            file = fopen(filename, "w");
            if (file) {
                cout << "File opened successfully" << endl;
            }
        }

        ~FileHandler() {
            if (file) {
                fclose(file);
                cout << "File closed automatically" << endl;
            }
        }

        void write(const char* text) {
            if (file) {
                fprintf(file, "%s\n", text);
            }
        }
    };

    {
        FileHandler handler("example.txt");
        handler.write("Hello from RAII!");
        // File automatically closed when handler goes out of scope
    }
    cout << "FileHandler scope ended" << endl;
}

int main() {
    cout << "=== Memory Management Demo ===\n" << endl;

    demonstrateRawPointers();
    demonstrateSmartPointers();
    demonstrateMemoryIssues();
    demonstrateRAII();

    cout << "\n=== Summary ===" << endl;
    cout << "Raw pointers require manual memory management (error-prone)" << endl;
    cout << "Smart pointers provide automatic memory management (safe)" << endl;
    cout << "RAII ensures resources are properly cleaned up" << endl;

    return 0;
}