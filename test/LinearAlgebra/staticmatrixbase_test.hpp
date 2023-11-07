#include <gtest/gtest.h>
#include <array>
#include <iostream>
#include "../../include/LinearAlgebra/StaticMatrixBase/staticmatrixbase.hpp"
namespace {
    using namespace linear_algebra;
}
TEST(LinearAlgebraTest, StaticMatrixBaseConstructorTest) {
    // 全ての値を0で初期化
    StaticMatrixBase<int, 3, 3> dm1(0);
    for(std::size_t i = 0; i < 9; ++i) {
        assert(dm1.at(i) == 0);
    }
    // initializer_listによる初期化
    StaticMatrixBase<int, 3, 3> ini_m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    int ini_m1_test[9] = {1, 2, 3, 2, 3, 4, 3, 4, 5};
    for(std::size_t i = 0; i < 9; ++i) {
        assert(ini_m1.at(i) == ini_m1_test[i]);
    }
    StaticMatrixBase<int, 2, 2> ini_m2 = {1, 2, 3, 4};
    int ini_m2_test[4] = {1, 2, 3, 4};
    for(std::size_t i = 0; i < 4; ++i) {
        assert(ini_m2.at(i) == ini_m2_test[i]);
    }
    // std::arrayによる初期化
    std::array<std::array<int, 2>, 3> arr1 = {{{1, 2}, {2, 3}, {1, 2}}};
    std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBase<int, 3, 2> arr_m1 = arr1;
    // std::cout << arr_m1 << std::endl;
    for(std::size_t r = 0; r < 3; ++r) {
        for(std::size_t c = 0; c < 2; ++c) {
            assert(arr_m1(r, c) == arr1.at(r).at(c));
        }
    }
    StaticMatrixBase<int, 6, 1> arr_m2 = arr2;
    StaticMatrixBase<int, 1, 6> arr_m3 = arr2;
    for(std::size_t i = 0; i < 6; ++i) {
        assert(arr_m2.at(i) == arr2.at(i));
        assert(arr_m3.at(i) == arr2.at(i));
    }
    // コピーコンストラクタ 左辺値参照
    StaticMatrixBase<int, 3, 3> copy_m1 = ini_m1;
    for(std::size_t i = 0; i < 9; ++i) {
        assert(copy_m1.at(i) == ini_m1_test[i]);
    }
    // コピーコンストラクタ 右辺値参照
    StaticMatrixBase<double, 2, 2> copy_m2 = StaticMatrixBase<double, 2, 2>{1.1, 2.2, 3.3, 4.4};
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

    //std::cout << m1 << m2 << std::endl;
    const auto m1pm2 = m1 + m2;
    //std::cout << m1pm2 << std::endl;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().col(); ++i) {
        assert(m1pm2.at(i) == m3.at(i));
    }
    const auto m3mm1pm2 = m3 - m1pm2;
    //std::cout << m3mm1pm2 << std::endl;
    for(std::size_t i = 0; i < m3.shape().row() * m3.shape().col(); ++i) {
        assert(m3mm1pm2.at(i) == m4.at(i));
    }
}