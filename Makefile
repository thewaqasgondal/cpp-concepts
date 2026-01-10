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
STRINGS_DIR = examples/strings
TEMPLATES_DIR = examples/templates
EXCEPTIONS_DIR = examples/exceptions
OOP_DIR = examples/oop
MEMORY_DIR = examples/memory_management
STL_DIR = examples/stl
ADVANCED_DIR = examples/advanced
MODERN_CPP_DIR = examples/modern_cpp
FILE_IO_DIR = examples/file_io
CONCURRENCY_DIR = examples/concurrency
MOVE_SEMANTICS_DIR = examples/move_semantics
ALGORITHMS_DIR = examples/algorithms
DESIGN_PATTERNS_DIR = examples/design_patterns
SERIALIZATION_DIR = examples/serialization
MEMORY_POOLS_DIR = examples/memory_pools
TEMPLATE_METAPROGRAMMING_DIR = examples/template_metaprogramming
PERFORMANCE_OPTIMIZATION_DIR = examples/performance_optimization
PLUGIN_SYSTEM_DIR = examples/plugin_system
COROUTINES_DIR = examples/coroutines
CONCEPTS_DIR = examples/concepts
RANGES_DIR = examples/ranges
PARALLEL_ALGORITHMS_DIR = examples/parallel_algorithms
SIMD_OPERATIONS_DIR = examples/simd_operations

# Executable names
EXECUTABLES = \
	$(BASICS_DIR)/hello_world \
	$(DATA_TYPES_DIR)/data_types_demo \
	$(CONTROL_FLOW_DIR)/control_flow_demo \
	$(FUNCTIONS_DIR)/functions_demo \
	$(ARRAYS_VECTORS_DIR)/arrays_vectors_demo \
	$(POINTERS_REFS_DIR)/pointers_references_demo \
	$(STRINGS_DIR)/strings_demo \
	$(TEMPLATES_DIR)/templates_demo \
	$(EXCEPTIONS_DIR)/exceptions_demo \
	$(OOP_DIR)/oop_demo \
	$(MEMORY_DIR)/memory_demo \
	$(STL_DIR)/stl_demo \
	$(ADVANCED_DIR)/concurrency/concurrency_demo \
	$(ADVANCED_DIR)/modern_cpp/modern_cpp_demo \
	$(ADVANCED_DIR)/templates/templates_demo \
	$(ADVANCED_DIR)/coroutines/coroutines_demo \
	$(ADVANCED_DIR)/thread_pool/thread_pool_demo \
	$(ADVANCED_DIR)/thread_pool/thread_pool_tests \
	$(ADVANCED_DIR)/dsa/dsa_demo \
	$(ADVANCED_DIR)/dsa/dsa_tests \
	$(MODERN_CPP_DIR)/modern_cpp_demo \
	$(FILE_IO_DIR)/file_io_demo \
	$(CONCURRENCY_DIR)/concurrency_demo \
	$(MOVE_SEMANTICS_DIR)/move_semantics_demo \
	$(ALGORITHMS_DIR)/algorithms_demo \
	$(DESIGN_PATTERNS_DIR)/design_patterns_demo \
	$(SERIALIZATION_DIR)/serialization_demo \
	$(MEMORY_POOLS_DIR)/memory_pools_demo \
	$(TEMPLATE_METAPROGRAMMING_DIR)/template_metaprogramming_demo \
	$(PERFORMANCE_OPTIMIZATION_DIR)/performance_optimization_demo \
	$(PLUGIN_SYSTEM_DIR)/plugin_system_demo \
	$(COROUTINES_DIR)/modern_coroutines_demo \
	$(CONCEPTS_DIR)/concepts_demo \
	$(RANGES_DIR)/ranges_demo \
	$(PARALLEL_ALGORITHMS_DIR)/parallel_algorithms_demo \
	$(SIMD_OPERATIONS_DIR)/simd_operations_demo
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

$(STRINGS_DIR)/strings_demo: $(STRINGS_DIR)/strings_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TEMPLATES_DIR)/templates_demo: $(TEMPLATES_DIR)/templates_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(EXCEPTIONS_DIR)/exceptions_demo: $(EXCEPTIONS_DIR)/exceptions_demo.cpp
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

$(ADVANCED_DIR)/dsa/dsa_demo: $(ADVANCED_DIR)/dsa/dsa_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(ADVANCED_DIR)/dsa/dsa_tests: $(ADVANCED_DIR)/dsa/dsa_tests.cpp $(ADVANCED_DIR)/dsa/dsa_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


$(STL_DIR)/stl_demo: $(STL_DIR)/stl_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(MODERN_CPP_DIR)/modern_cpp_demo: $(MODERN_CPP_DIR)/modern_cpp_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(FILE_IO_DIR)/file_io_demo: $(FILE_IO_DIR)/file_io_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(CONCURRENCY_DIR)/concurrency_demo: $(CONCURRENCY_DIR)/concurrency_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(MOVE_SEMANTICS_DIR)/move_semantics_demo: $(MOVE_SEMANTICS_DIR)/move_semantics_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(ALGORITHMS_DIR)/algorithms_demo: $(ALGORITHMS_DIR)/algorithms_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(DESIGN_PATTERNS_DIR)/design_patterns_demo: $(DESIGN_PATTERNS_DIR)/design_patterns_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(SERIALIZATION_DIR)/serialization_demo: $(SERIALIZATION_DIR)/serialization_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(MEMORY_POOLS_DIR)/memory_pools_demo: $(MEMORY_POOLS_DIR)/memory_pools_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TEMPLATE_METAPROGRAMMING_DIR)/template_metaprogramming_demo: $(TEMPLATE_METAPROGRAMMING_DIR)/template_metaprogramming_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(PERFORMANCE_OPTIMIZATION_DIR)/performance_optimization_demo: $(PERFORMANCE_OPTIMIZATION_DIR)/performance_optimization_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(PLUGIN_SYSTEM_DIR)/plugin_system_demo: $(PLUGIN_SYSTEM_DIR)/plugin_system_demo.cpp
	$(CXX) $(CXXFLAGS) -ldl -o $@ $<

$(COROUTINES_DIR)/modern_coroutines_demo: $(COROUTINES_DIR)/coroutines_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(CONCEPTS_DIR)/concepts_demo: $(CONCEPTS_DIR)/concepts_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(RANGES_DIR)/ranges_demo: $(RANGES_DIR)/ranges_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(PARALLEL_ALGORITHMS_DIR)/parallel_algorithms_demo: $(PARALLEL_ALGORITHMS_DIR)/parallel_algorithms_demo.cpp
	$(CXX) $(CXXFLAGS) -pthread -o $@ $<

$(SIMD_OPERATIONS_DIR)/simd_operations_demo: $(SIMD_OPERATIONS_DIR)/simd_operations_demo.cpp
	$(CXX) $(CXXFLAGS) -march=native -o $@ $<

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
	@echo "  strings_demo"
	@echo "  templates_demo"
	@echo "  exceptions_demo"
	@echo "  oop_demo"
	@echo "  memory_demo"
	@echo "  stl_demo"
	@echo "  modern_cpp_demo"
	@echo "  file_io_demo"
	@echo "  concurrency_demo"
	@echo "  move_semantics_demo"
	@echo "  algorithms_demo"
	@echo "  design_patterns_demo"
	@echo "  serialization_demo"
	@echo "  memory_pools_demo"
	@echo "  template_metaprogramming_demo"
	@echo "  performance_optimization_demo"
	@echo "  plugin_system_demo"
	@echo "  modern_coroutines_demo"
	@echo "  concepts_demo"
	@echo "  ranges_demo"
	@echo "  parallel_algorithms_demo"
	@echo "  simd_operations_demo"

.PHONY: all clean run-all help