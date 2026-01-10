#include <iostream>
#include <cstdlib>

int main() {
    // Simple test - just run the hello_world program
    int result = system("./examples/basics/hello_world");
    if (result == 0) {
        std::cout << "Test passed: hello_world executed successfully" << std::endl;
        return 0;
    } else {
        std::cout << "Test failed: hello_world execution failed" << std::endl;
        return 1;
    }
}