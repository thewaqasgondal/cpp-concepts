add_executable(dsa_demo dsa_demo.cpp)
target_compile_features(dsa_demo PRIVATE cxx_std_23)

add_executable(dsa_tests dsa_tests.cpp)
target_compile_features(dsa_tests PRIVATE cxx_std_23)
