cmake_minimum_required(VERSION 3.10)
project(plugin_system_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(plugin_system_demo plugin_system_demo.cpp)
target_link_libraries(plugin_system_demo dl)