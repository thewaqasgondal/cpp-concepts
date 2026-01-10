#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// Custom exception class
class DivisionByZeroException : public runtime_error {
public:
    DivisionByZeroException() : runtime_error("Division by zero attempted") {}
    DivisionByZeroException(const string& msg) : runtime_error(msg) {}
};

// Another custom exception
class InvalidInputException : public invalid_argument {
public:
    InvalidInputException(const string& msg) : invalid_argument(msg) {}
};

// Function that may throw exceptions
double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw DivisionByZeroException("Cannot divide by zero");
    }
    return numerator / denominator;
}

// Function demonstrating different exception types
void processData(int value) {
    if (value < 0) {
        throw InvalidInputException("Negative values are not allowed");
    }
    if (value == 0) {
        throw runtime_error("Zero is not a valid input for this operation");
    }
    if (value > 100) {
        throw out_of_range("Value exceeds maximum allowed (100)");
    }

    cout << "Processing value: " << value << endl;
}

// Function with multiple exception handling
void riskyOperation() {
    vector<int> data = {1, 2, 3};

    try {
        // This will throw out_of_range
        cout << "Accessing element at index 10: " << data.at(10) << endl;
    } catch (const out_of_range& e) {
        cout << "Caught out_of_range: " << e.what() << endl;
        throw; // Re-throw the exception
    }
}

void demonstrateBasicExceptionHandling() {
    cout << "=== Basic Exception Handling ===\n" << endl;

    try {
        double result = divide(10.0, 0.0);
        cout << "Result: " << result << endl;
    } catch (const DivisionByZeroException& e) {
        cout << "Caught DivisionByZeroException: " << e.what() << endl;
    }

    try {
        double result = divide(10.0, 2.0);
        cout << "Result: " << result << endl;
    } catch (const DivisionByZeroException& e) {
        cout << "This shouldn't be caught" << endl;
    }
}

void demonstrateMultipleCatchBlocks() {
    cout << "\n=== Multiple Catch Blocks ===\n" << endl;

    vector<int> testValues = {-5, 0, 50, 150};

    for (int value : testValues) {
        try {
            processData(value);
        } catch (const InvalidInputException& e) {
            cout << "InvalidInputException for " << value << ": " << e.what() << endl;
        } catch (const runtime_error& e) {
            cout << "Runtime error for " << value << ": " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Out of range for " << value << ": " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Generic exception for " << value << ": " << e.what() << endl;
        }
    }
}

void demonstrateExceptionPropagation() {
    cout << "\n=== Exception Propagation ===\n" << endl;

    try {
        riskyOperation();
    } catch (const out_of_range& e) {
        cout << "Exception propagated to main: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Generic exception caught: " << e.what() << endl;
    }
}

void demonstrateRAIIWithExceptions() {
    cout << "\n=== RAII with Exceptions ===\n" << endl;

    class ResourceManager {
    private:
        string name;
    public:
        ResourceManager(const string& n) : name(n) {
            cout << "Resource '" << name << "' acquired" << endl;
        }
        ~ResourceManager() {
            cout << "Resource '" << name << "' released" << endl;
        }
        void use() {
            cout << "Using resource '" << name << "'" << endl;
        }
    };

    try {
        ResourceManager res1("Database");
        res1.use();

        ResourceManager res2("File");
        res2.use();

        // Simulate an exception
        throw runtime_error("Something went wrong!");

        // This code won't execute
        cout << "This won't be printed" << endl;

    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
        cout << "Resources will be automatically cleaned up" << endl;
    }
}

void demonstrateNothrowGuarantee() {
    cout << "\n=== Exception Safety ===\n" << endl;

    // Function that provides strong exception safety
    auto safeOperation = [](vector<int>& data, int value) {
        vector<int> backup = data; // Create backup

        try {
            data.push_back(value);
            // Simulate potential failure
            if (value == 999) {
                throw runtime_error("Simulated failure");
            }
            data.push_back(value * 2);
        } catch (const exception& e) {
            // Restore original state on failure
            data = backup;
            throw; // Re-throw
        }
    };

    vector<int> numbers = {1, 2, 3};
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    try {
        safeOperation(numbers, 4);
        cout << "After successful operation: ";
        for (int n : numbers) cout << n << " ";
        cout << endl;

        safeOperation(numbers, 999); // This will fail
    } catch (const exception& e) {
        cout << "Operation failed, data restored: ";
        for (int n : numbers) cout << n << " ";
        cout << endl;
    }
}

int main() {
    cout << "=== C++ Exception Handling Demo ===\n" << endl;

    demonstrateBasicExceptionHandling();
    demonstrateMultipleCatchBlocks();
    demonstrateExceptionPropagation();
    demonstrateRAIIWithExceptions();
    demonstrateNothrowGuarantee();

    cout << "\n=== Summary ===" << endl;
    cout << "• Use exceptions for error handling, not for normal flow control" << endl;
    cout << "• Catch exceptions by const reference to avoid slicing" << endl;
    cout << "• Order catch blocks from most specific to most general" << endl;
    cout << "• RAII ensures resources are cleaned up even when exceptions occur" << endl;
    cout << "• Provide exception safety guarantees in your functions" << endl;
    cout << "• Use standard exception classes when possible" << endl;

    return 0;
}