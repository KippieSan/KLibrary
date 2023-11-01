#include <gtest/gtest.h>
#include "../../include/LinearAlgebra/matrix_base.hpp"
namespace {
    using namespace linear_algebra;
}
TEST(LinearAlgebraTest, MatrixBaseConstructorTest) {
    // コンパイルが通るかのテスト
    // デフォルトコンストラクタ
    MatrixBase<int, 3, 3> m;
    // initializer_listによる初期化
    MatrixBase<int, 3, 3> m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    MatrixBase<int, 2, 2> m2 = {1, 2, 3, 4};
    // コピーコンストラクタ 左辺値参照
    MatrixBase<int, 3, 3> m3 = m1;
    // コピーコンストラクタ 右辺値参照
    MatrixBase<double, 2, 2> m4 = MatrixBase<double, 2, 2>{1.1, 2.2, 3.3, 4.4};
}
TEST(LinearAlgebraTest, MatrixBaseAssignmentOperatorTest) {
    MatrixBase<int, 3, 3>       m1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MatrixBase<int, 3, 3>       m2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    MatrixBase<double, 3, 3>    m3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    MatrixBase<int, 3, 3>       m4 = {30, 24, 18, 84, 69, 54, 138, 114, 90};

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