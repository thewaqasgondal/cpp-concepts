cmake_minimum_required(VERSION 3.10)
project(CppConceptsTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add test executable
add_executable(run_tests test_main.cpp)
add_test(NAME BasicTest COMMAND run_tests)

# Link with examples for testing
target_link_libraries(run_tests)