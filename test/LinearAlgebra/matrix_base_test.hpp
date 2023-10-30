#include <gtest/gtest.h>
#include "../../include/LinearAlgebra/matrix_base.hpp"
namespace {
    using namespace linear_algebra;
}
TEST(LinearAlgebraTest, MatrixBaseInitializeTest) {
    // コンパイルが通るかのテスト
    // initializer_listによる初期化
    MatrixBase<int, 3, 3> m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    MatrixBase<int, 2, 2> m2 = {1, 2, 3, 4};
}