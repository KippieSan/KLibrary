#include <gtest/gtest.h>
#include <array>
#include "../../include/LinearAlgebra/StaticMatrixBase/staticmatrixbase.hpp"
namespace {
    using namespace linear_algebra;
}
TEST(LinearAlgebraTest, MatrixBaseConstructorTest) {
    // コンパイルが通るかのテスト
    // 全ての値を0で初期化
    StaticMatrixBase<int, 3, 3> dm1(0);
    // initializer_listによる初期化
    StaticMatrixBase<int, 3, 3> ini_m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    StaticMatrixBase<int, 2, 2> ini_m2 = {1, 2, 3, 4};
    // std::arrayによる初期化
    std::array<std::array<int, 2>, 3> arr1 = {{{1, 2}, {2, 3}, {1, 2}}};
    std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBase<int, 3, 2> arr_m1 = arr1;
    StaticMatrixBase<int, 2, 3> arr_m2 = arr2;
    // コピーコンストラクタ 左辺値参照
    StaticMatrixBase<int, 3, 3> copy_m1 = ini_m1;
    // コピーコンストラクタ 右辺値参照
    StaticMatrixBase<double, 2, 2> copy_m2 = StaticMatrixBase<double, 2, 2>{1.1, 2.2, 3.3, 4.4};
}
TEST(LinearAlgebraTest, MatrixBaseAssignmentOperatorTest) {
    StaticMatrixBase<int, 3, 3>       m1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    StaticMatrixBase<int, 3, 3>       m2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    StaticMatrixBase<double, 3, 3>    m3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    StaticMatrixBase<int, 3, 3>       m4 = {30, 24, 18, 84, 69, 54, 138, 114, 90};

    m1 += m2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().column(); ++i) {
        assert(m1.at(i) == 10);
    }
    m1 -= m2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().column(); ++i) {
        assert(m1.at(i) == i + 1);
    }
    m1 *= m3;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().column(); ++i) {
        assert(m1.at(i) == m4.at(i));
    }
    m1 *= 2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().column(); ++i) {
        assert(m1.at(i) == m4.at(i) * 2);
    }
    m1 /= 2;
    for(std::size_t i = 0; i < m1.shape().row() * m1.shape().column(); ++i) {
        assert(m1.at(i) == m4.at(i));
    }
}