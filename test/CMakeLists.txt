add_executable(test_all test_all.cpp)
target_link_libraries(test_all GTest::gtest GTest::gtest_main)
include(GoogleTest)
