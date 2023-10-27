add_executable(numerical_analysis_test numerical_analysis_test.cpp)
target_link_libraries(numerical_analysis_test GTest::gtest GTest::gtest_main)

include(GoogleTest)
# gtest_discover_tests(test)