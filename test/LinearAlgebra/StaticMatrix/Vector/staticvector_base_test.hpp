#include <gtest/gtest.h>
#include <array>
#include <iostream>
#include "./../../../../include/LinearAlgebra/StaticMatrix/Vector/Base/staticvector_base.hpp"

namespace {
    using namespace klibrary::linear_algebra;
}
TEST(LinearAlgebraStaticVectorBaseTest, ConstructorTest) {
    StaticVectorBase<int, 5, 1> dv1;
    StaticVectorBase<int, 5, 1> cv1(3);
    StaticVectorBase<int, 5, 1> ini_v1 = {1, 2, 3, 4, 5};
    std::array<int, 5> arr1 = {9, 8, 7, 6, 5};
    StaticVectorBase<int, 5, 1> arr_v1 = arr1;
    StaticVectorBase<int, 5, 1> copy_v1 = arr_v1;
    StaticVectorBase<int, 5, 1> copy_v2 = StaticVectorBase<int, 5, 1>{3, 4, 5, 6, 7};

    std::array<int, 5> ini_v1_test = {1, 2, 3, 4, 5};
    std::array<int, 5> arr_v1_test = {9, 8, 7, 6, 5};
    std::array<int, 5> copy_v2_test = {3, 4, 5, 6, 7};

    for(std::size_t i = 0; i < 5; ++i) {
        assert(dv1.at(i) == 0);
        assert(cv1.at(i) == 3);
        assert(ini_v1.at(i) == ini_v1_test.at(i));
        assert(arr_v1.at(i) == arr_v1_test.at(i));
        assert(copy_v1.at(i) == arr_v1_test.at(i));
        assert(copy_v2.at(i) == copy_v2_test.at(i));
    }
}
TEST(LinearAlgebraStaticVectorBaseTest, AssignmentOperatorTest) {
    StaticVectorBase<int, 5, 1> v1 = {1, 2, 3, 4, 5};
    StaticVectorBase<int, 5, 1> v2 = {2, 3, 4, 5, 6};

    std::array<int, 5> addition_test = {3, 5, 7, 9, 11};
    std::array<int, 5> subtraction_test = {1, 2, 3, 4, 5};
    std::array<int, 5> multiplication_test = {2, 6, 12, 20, 30};
    std::array<int, 5> division_test = {1, 3, 6, 10, 15};
    std::array<int, 5> scalar_multiplication_test = {3, 9, 18, 30, 45};

    v1 += v2;
    for(std::size_t i = 0; i < 5; ++i) {
        assert(v1.at(i) == addition_test.at(i));
    }
    v1 -= v2;
    for(std::size_t i = 0; i < 5; ++i) {
        assert(v1.at(i) == subtraction_test.at(i));
    }
    v1 *= v2;
    for(std::size_t i = 0; i < 5; ++i) {
        assert(v1.at(i) == multiplication_test.at(i));
    }
    v1 /= 2;
    for(std::size_t i = 0; i < 5; ++i) {
        assert(v1.at(i) == division_test.at(i));
    }
    v1 *= 3;
    for(std::size_t i = 0; i < 5; ++i) {
        assert(v1.at(i) == scalar_multiplication_test.at(i));
    }
}
TEST(LinearAlgebraStaticVectorBaseTest, OperatorTest) {
    StaticVectorBase<int, 5, 1> v1 = {6, 4, 5, 9, 2};
    StaticVectorBase<int, 5, 1> v2 = {2, 3, 4, 5, 6};

    std::array<int, 5> addition_test = {8, 7, 9, 14, 8};
    std::array<int, 5> subtraction_test = {4, 1, 1, 4, -4};
    std::array<int, 5> multiplication_test = {12, 12, 20, 45, 12};
    std::array<int, 5> scalar_multiplication_test1 = {4, 6, 8, 10, 12};
    std::array<int, 5> scalar_multiplication_test2 = {18, 12, 15, 27, 6};
    std::array<int, 5> scalar_division_test = {3, 2, 2, 4, 1};

    const auto r1 = v1 + v2;
    const auto r2 = v1 - v2;
    const auto r3 = v1 * v2;
    const auto r4 = v2 * 2;
    const auto r5 = 3 * v1;
    const auto r6 = v1 / 2;

    for(std::size_t i = 0; i < 5; ++i) {
        assert(r1.at(i) == addition_test.at(i));
        assert(r2.at(i) == subtraction_test.at(i));
        assert(r3.at(i) == multiplication_test.at(i));
        assert(r4.at(i) == scalar_multiplication_test1.at(i));
        assert(r5.at(i) == scalar_multiplication_test2.at(i));
        assert(r6.at(i) == scalar_division_test.at(i));
    }
}
TEST(LinearAlgebraStaticVectorBaseTest, MemberFunctionTest) {
    StaticVectorBase<int, 1, 5> v1 = {1, 2, 3, 4, 5};
    assert(v1[3] == 4);
    assert(v1.at(3) == 4);
    assert(v1.size() == 5);
}