add_executable(test numerical_analysis_test.cpp)
target_link_libraries(test GTest::gtest GTest::gtest_main)

include(GoogleTest)
# gtest_discover_tests(test)