cmake_minimum_required(VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(catch2)

add_executable(thread_pool_tests thread_pool_tests.cpp)
target_link_libraries(thread_pool_tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(thread_pool_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_compile_features(thread_pool_tests PRIVATE cxx_std_23)

include(CTest)
include(Catch)
catch_discover_tests(thread_pool_tests)
