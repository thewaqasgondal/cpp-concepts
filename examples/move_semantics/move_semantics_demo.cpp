#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Resource {
private:
    string name;
    int* data;
    size_t size;

public:
    // Constructor
    Resource(const string& n, size_t s) : name(n), size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
        cout << "Resource '" << name << "' created with " << size << " elements" << endl;
    }

    // Copy constructor
    Resource(const Resource& other) : name(other.name + "_copy"), size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        cout << "Resource '" << name << "' copy-constructed" << endl;
    }

    // Move constructor
    Resource(Resource&& other) noexcept : name(move(other.name)), data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Resource '" << name << "' move-constructed" << endl;
    }

    // Copy assignment
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            name = other.name + "_assigned";
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            cout << "Resource '" << name << "' copy-assigned" << endl;
        }
        return *this;
    }

    // Move assignment
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            name = move(other.name);
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "Resource '" << name << "' move-assigned" << endl;
        }
        return *this;
    }

    // Destructor
    ~Resource() {
        delete[] data;
        cout << "Resource '" << name << "' destroyed" << endl;
    }

    void display() const {
        cout << "Resource '" << name << "': ";
        if (data) {
            for (size_t i = 0; i < min(size, size_t(5)); ++i) {
                cout << data[i] << " ";
            }
            if (size > 5) cout << "...";
        } else {
            cout << "(empty)";
        }
        cout << endl;
    }
};

void demonstrateLvaluesRvalues() {
    cout << "=== Lvalues and Rvalues ===\n" << endl;

    int x = 5;        // x is an lvalue
    int& ref = x;     // ref is an lvalue reference
    // int&& rref = x; // Error: can't bind rvalue reference to lvalue

    cout << "x = " << x << " (lvalue)" << endl;
    cout << "ref = " << ref << " (lvalue reference)" << endl;

    int&& rref = 10;  // rref is an rvalue reference
    cout << "rref = " << rref << " (rvalue reference)" << endl;

    // Rvalues from expressions
    int y = x + 1;    // x + 1 is an rvalue
    cout << "y = x + 1 = " << y << endl;
}

void demonstrateCopyVsMove() {
    cout << "\n=== Copy vs Move Semantics ===\n" << endl;

    cout << "Creating original resource..." << endl;
    Resource original("Original", 10);
    original.display();

    cout << "\nCopying resource..." << endl;
    Resource copy = original;
    copy.display();

    cout << "\nMoving resource..." << endl;
    Resource moved = move(original);
    moved.display();
    original.display(); // Should be empty after move
}

void demonstrateMoveInFunctions() {
    cout << "\n=== Move in Functions ===\n" << endl;

    auto process_resource = [](Resource res) {
        cout << "Processing resource inside function:" << endl;
        res.display();
    };

    auto process_resource_ref = [](Resource& res) {
        cout << "Processing resource by reference:" << endl;
        res.display();
    };

    auto process_resource_move = [](Resource&& res) {
        cout << "Processing resource by rvalue reference:" << endl;
        res.display();
    };

    Resource res("FunctionTest", 5);

    cout << "Calling with copy:" << endl;
    process_resource(res);

    cout << "\nCalling with reference:" << endl;
    process_resource_ref(res);

    cout << "\nCalling with move:" << endl;
    process_resource_move(move(res));
}

void demonstrateStdMove() {
    cout << "\n=== std::move ===\n" << endl;

    Resource res1("MoveTest1", 3);
    Resource res2("MoveTest2", 4);

    cout << "Before assignment:" << endl;
    res1.display();
    res2.display();

    cout << "\nAfter res1 = move(res2):" << endl;
    res1 = move(res2);
    res1.display();
    res2.display();
}

void demonstratePerfectForwarding() {
    cout << "\n=== Perfect Forwarding ===\n" << endl;

    auto factory = [](auto&&... args) {
        return Resource(forward<decltype(args)>(args)...);
    };

    cout << "Creating resource with perfect forwarding:" << endl;
    Resource res = factory("PerfectForward", 8);
    res.display();
}

void demonstrateVectorMove() {
    cout << "\n=== Move with Containers ===\n" << endl;

    vector<Resource> resources;

    cout << "Creating resources..." << endl;
    resources.emplace_back("VecRes1", 2);
    resources.emplace_back("VecRes2", 2);
    resources.emplace_back("VecRes3", 2);

    cout << "\nMoving vector..." << endl;
    vector<Resource> moved_resources = move(resources);

    cout << "\nOriginal vector after move:" << endl;
    for (const auto& res : resources) {
        res.display();
    }

    cout << "\nMoved vector:" << endl;
    for (const auto& res : moved_resources) {
        res.display();
    }
}

void demonstrateMoveWithStrings() {
    cout << "\n=== Move with Strings ===\n" << endl;

    string s1 = "Hello";
    string s2 = "World";

    cout << "s1: '" << s1 << "' (capacity: " << s1.capacity() << ")" << endl;
    cout << "s2: '" << s2 << "' (capacity: " << s2.capacity() << ")" << endl;

    cout << "\nAfter s1 = move(s2):" << endl;
    s1 = move(s2);
    cout << "s1: '" << s1 << "' (capacity: " << s1.capacity() << ")" << endl;
    cout << "s2: '" << s2 << "' (capacity: " << s2.capacity() << ")" << endl;
}

int main() {
    cout << "=== C++ Move Semantics Demo ===\n" << endl;

    demonstrateLvaluesRvalues();
    demonstrateCopyVsMove();
    demonstrateMoveInFunctions();
    demonstrateStdMove();
    demonstratePerfectForwarding();
    demonstrateVectorMove();
    demonstrateMoveWithStrings();

    cout << "\n=== Summary ===" << endl;
    cout << "• Lvalues: Have names and persist beyond expressions" << endl;
    cout << "• Rvalues: Temporary values, can be moved from" << endl;
    cout << "• Move constructor: Transfers ownership efficiently" << endl;
    cout << "• Move assignment: Transfers ownership in assignments" << endl;
    cout << "• std::move: Casts to rvalue reference" << endl;
    cout << "• Perfect forwarding: Preserves value category" << endl;
    cout << "• Containers support move semantics for efficiency" << endl;

    return 0;
}