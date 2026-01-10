cmake_minimum_required(VERSION 3.10)
project(coroutines_demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(modern_coroutines_demo coroutines_demo.cpp)