# C++ Concepts Examples - Makefile

CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2

# Source directories
BASICS_DIR = examples/basics
DATA_TYPES_DIR = examples/data_types
CONTROL_FLOW_DIR = examples/control_flow
FUNCTIONS_DIR = examples/functions
ARRAYS_VECTORS_DIR = examples/arrays_vectors
POINTERS_REFS_DIR = examples/pointers_references
OOP_DIR = examples/oop
MEMORY_DIR = examples/memory_management
STL_DIR = examples/stl
ADVANCED_DIR = examples/advanced

# Executable names
EXECUTABLES = \
	$(BASICS_DIR)/hello_world \
	$(DATA_TYPES_DIR)/data_types_demo \
	$(CONTROL_FLOW_DIR)/control_flow_demo \
	$(FUNCTIONS_DIR)/functions_demo \
	$(ARRAYS_VECTORS_DIR)/arrays_vectors_demo \
	$(POINTERS_REFS_DIR)/pointers_references_demo \
	$(OOP_DIR)/oop_demo \
	$(MEMORY_DIR)/memory_demo \
	$(STL_DIR)/stl_demo \
	$(ADVANCED_DIR)/concurrency/concurrency_demo \
	$(ADVANCED_DIR)/modern_cpp/modern_cpp_demo \
	$(ADVANCED_DIR)/templates/templates_demo	$(ADVANCED_DIR)/coroutines/coroutines_demo \
	$(ADVANCED_DIR)/thread_pool/thread_pool_demo \
	$(ADVANCED_DIR)/thread_pool/thread_pool_tests \
# Default target
all: $(EXECUTABLES)

# Compile individual programs
$(BASICS_DIR)/hello_world: $(BASICS_DIR)/hello_world.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(DATA_TYPES_DIR)/data_types_demo: $(DATA_TYPES_DIR)/data_types_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(CONTROL_FLOW_DIR)/control_flow_demo: $(CONTROL_FLOW_DIR)/control_flow_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(FUNCTIONS_DIR)/functions_demo: $(FUNCTIONS_DIR)/functions_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(ARRAYS_VECTORS_DIR)/arrays_vectors_demo: $(ARRAYS_VECTORS_DIR)/arrays_vectors_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(POINTERS_REFS_DIR)/pointers_references_demo: $(POINTERS_REFS_DIR)/pointers_references_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OOP_DIR)/oop_demo: $(OOP_DIR)/oop_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(MEMORY_DIR)/memory_demo: $(MEMORY_DIR)/memory_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
$(ADVANCED_DIR)/concurrency/concurrency_demo: $(ADVANCED_DIR)/concurrency/concurrency_demo.cpp
	$(CXX) $(CXXFLAGS) -pthread -o $@ $<

$(ADVANCED_DIR)/modern_cpp/modern_cpp_demo: $(ADVANCED_DIR)/modern_cpp/modern_cpp_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(ADVANCED_DIR)/templates/templates_demo: $(ADVANCED_DIR)/templates/templates_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(ADVANCED_DIR)/coroutines/coroutines_demo: $(ADVANCED_DIR)/coroutines/coroutines_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(ADVANCED_DIR)/thread_pool/thread_pool_demo: $(ADVANCED_DIR)/thread_pool/thread_pool_demo.cpp $(ADVANCED_DIR)/thread_pool/thread_pool.h
	$(CXX) $(CXXFLAGS) -pthread -o $@ $<

$(ADVANCED_DIR)/thread_pool/thread_pool_tests: $(ADVANCED_DIR)/thread_pool/test/thread_pool_tests.cpp $(ADVANCED_DIR)/thread_pool/thread_pool.h
	$(CXX) $(CXXFLAGS) -pthread -o $@ $< -I$(ADVANCED_DIR)/thread_pool -lstdc++ -lpthread


$(STL_DIR)/stl_demo: $(STL_DIR)/stl_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean build artifacts
clean:
	rm -f $(EXECUTABLES)

# Run all examples
run-all: all
	@echo "Running all examples..."
	@for exe in $(EXECUTABLES); do \
		echo "========================================"; \
		echo "Running $$exe"; \
		echo "========================================"; \
		./$$exe; \
		echo ""; \
	done

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build all examples"
	@echo "  clean      - Remove all built executables"
	@echo "  concurrency_demo"
	@echo "  modern_cpp_demo"
	@echo "  templates_demo"
	@echo "  coroutines_demo"
	@echo "  thread_pool_demo"
	@echo "  run-all    - Build and run all examples"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Individual examples:"
	@echo "  hello_world"
	@echo "  data_types_demo"
	@echo "  control_flow_demo"
	@echo "  functions_demo"
	@echo "  arrays_vectors_demo"
	@echo "  pointers_references_demo"
	@echo "  oop_demo"
	@echo "  memory_demo"
	@echo "  stl_demo"

.PHONY: all clean run-all help