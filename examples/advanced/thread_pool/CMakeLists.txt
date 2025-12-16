cmake_minimum_required(VERSION 3.10)

add_library(thread_pool INTERFACE)
target_include_directories(thread_pool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(thread_pool_demo thread_pool_demo.cpp)
target_link_libraries(thread_pool_demo PRIVATE thread_pool)
target_compile_features(thread_pool_demo PRIVATE cxx_std_23)

add_subdirectory(test)
