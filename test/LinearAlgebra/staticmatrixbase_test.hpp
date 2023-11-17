#include <gtest/gtest.h>
#include <array>
#include <iostream>
#include "./../../include/LinearAlgebra/StaticMatrix/Base/staticmatrixbase.hpp"
namespace {
    using namespace klibrary::linear_algebra;
}
TEST(LinearAlgebraTest, StaticMatrixBaseConstructorTest) {
    // デフォルトコンストラクタ
    StaticMatrixBase<int, 3, 3> dm1;
    StaticMatrixBase<int, 4, 5> cm1(5);
    StaticMatrixBase<int, 3, 3> ini_m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    StaticMatrixBase<int, 2, 2> ini_m2 = {1, 2, 3, 4};
    std::array<std::array<int, 2>, 3> arr1 = {{{1, 2}, {2, 3}, {1, 2}}};
    StaticMatrixBase<int, 3, 2> arr_m1 = arr1;
    std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBase<int, 6, 1> arr_m2 = arr2;
    StaticMatrixBase<int, 1, 6> arr_m3 = arr2;
    StaticMatrixBase<int, 3, 3> copy_m1 = ini_m1;
    StaticMatrixBase<double, 2, 2> copy_m2 = StaticMatrixBase<double, 2, 2>{1.1, 2.2, 3.3, 4.4};


    for(std::size_t i = 0; i < 9; ++i) {
        assert(dm1.at(i) == 0);
    }
    for(std::size_t i = 0; i < 20; ++i) {
        assert(cm1.at(i) == 5);
    }
    int ini_m1_test[9] = {1, 2, 3, 2, 3, 4, 3, 4, 5};
    for(std::size_t i = 0; i < 9; ++i) {
        assert(ini_m1.at(i) == ini_m1_test[i]);
    }
    int ini_m2_test[4] = {1, 2, 3, 4};
    for(std::size_t i = 0; i < 4; ++i) {
        assert(ini_m2.at(i) == ini_m2_test[i]);
    }
    for(std::size_t r = 0; r < 3; ++r) {
        for(std::size_t c = 0; c < 2; ++c) {
            assert(arr_m1(r, c) == arr1.at(r).at(c));
        }
    }
    for(std::size_t i = 0; i < 6; ++i) {
        assert(arr_m2.at(i) == arr2.at(i));
        assert(arr_m3.at(i) == arr2.at(i));
    }
    for(std::size_t i = 0; i < 9; ++i) {
        assert(copy_m1.at(i) == ini_m1_test[i]);
    }
    double copy_m2_test[4] = {1.1, 2.2, 3.3, 4.4};
    for(std::size_t i = 0; i < 4; ++i) {
        assert(copy_m2.at(i) == copy_m2_test[i]);
    }
}
TEST(LinearAlgebraTest, StaticMatrixBaseAssignmentOperatorTest) {
    // 代入演算子のテスト
    StaticMatrixBase<int, 3, 3>       m1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    StaticMatrixBase<int, 3, 3>       m2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    StaticMatrixBase<double, 3, 3>    m3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    StaticMatrixBase<int, 3, 3>       m4 = {30, 24, 18, 84, 69, 54, 138, 114, 90};

    m1 += m2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(m1.at(i) == 10);
    }
    m1 -= m2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(m1.at(i) == i + 1);
    }
    m1 *= m3;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(m1.at(i) == m4.at(i));
    }
    m1 *= 2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(m1.at(i) == m4.at(i) * 2);
    }
    m1 /= 2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(m1.at(i) == m4.at(i));
    }
}
TEST(LinearAlgebraTest, StaticMatrixBaseOperatorTest) {
    // 二項演算子のテスト
    StaticMatrixBase<int, 2, 3>     m1 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBase<double, 2, 3>  m2 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBase<double, 2, 3>  m3 = {2, 4, 6, 8, 10, 12};
    StaticMatrixBase<double, 2, 3>  m4;
    StaticMatrixBase<double, 3, 4>  m5 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    StaticMatrixBase<double, 2, 4>  m6 = {38, 44, 50, 56, 83, 98, 113, 128};

    const auto plus = m1 + m2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(plus.at(i) == m3.at(i));
    }
    const auto minus = m3 - plus;
    for(std::size_t i = 0; i < m3.shape().row() * m3.shape().col(); ++i) {
        assert(minus.at(i) == m4.at(i));
    }
    const auto mul = m1 * m5;
    for(std::size_t i = 0; i < mul.shape().row() * mul.shape().col(); ++i) {
        assert(mul.at(i) == m6.at(i));
    }
    const auto mul2 = m2 * 2;
    for(std::size_t i = 0; i < mul2.shape().row() * mul2.shape().col(); ++i) {
        assert(mul2.at(i) == m3.at(i));
    }
    const auto mul3 = 2 * m2;
    for(std::size_t i = 0; i < mul3.shape().row() * mul3.shape().col(); ++i) {
        assert(mul3.at(i) == m3.at(i));
    }
    const auto mul4 = m3 / 2;
    for(std::size_t i = 0; i < mul4.shape().row() * mul4.shape().col(); ++i) {
        assert(mul4.at(i) == m2.at(i));
    }
}
