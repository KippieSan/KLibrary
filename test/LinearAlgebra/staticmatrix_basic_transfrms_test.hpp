#include <gtest/gtest.h>
#include <array>
#include <iostream>
#include "../../include/LinearAlgebra/StaticMatrixBasicTransforms/staticmatrix_basic_transforms.hpp"
namespace {
    using namespace linear_algebra;
}
TEST(LinearAlgebraTest, StaticMatrixBasicTransformsConstructorTest) {
    // デフォルトコンストラクタ
    StaticMatrixBasicTransforms<int, 3, 3> dm1;
    for(std::size_t i = 0; i < 9; ++i) {
        assert(dm1.at(i) == 0);
    }
    // 全ての要素を5で初期化
    StaticMatrixBasicTransforms<int, 4, 5> cm1(5);
    for(std::size_t i = 0; i < 20; ++i) {
        assert(cm1.at(i) == 5);
    }
    // initializer_listによる初期化
    StaticMatrixBasicTransforms<int, 3, 3> ini_m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    int ini_m1_test[9] = {1, 2, 3, 2, 3, 4, 3, 4, 5};
    for(std::size_t i = 0; i < 9; ++i) {
        assert(ini_m1.at(i) == ini_m1_test[i]);
    }
    StaticMatrixBasicTransforms<int, 2, 2> ini_m2 = {1, 2, 3, 4};
    int ini_m2_test[4] = {1, 2, 3, 4};
    for(std::size_t i = 0; i < 4; ++i) {
        assert(ini_m2.at(i) == ini_m2_test[i]);
    }
    // std::arrayによる初期化
    std::array<std::array<int, 2>, 3> arr1 = {{{1, 2}, {2, 3}, {1, 2}}};
    std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBasicTransforms<int, 3, 2> arr_m1 = arr1;
    for(std::size_t r = 0; r < 3; ++r) {
        for(std::size_t c = 0; c < 2; ++c) {
            assert(arr_m1(r, c) == arr1.at(r).at(c));
        }
    }
    StaticMatrixBasicTransforms<int, 6, 1> arr_m2 = arr2;
    StaticMatrixBasicTransforms<int, 1, 6> arr_m3 = arr2;
    for(std::size_t i = 0; i < 6; ++i) {
        assert(arr_m2.at(i) == arr2.at(i));
        assert(arr_m3.at(i) == arr2.at(i));
    }
    // コピーコンストラクタ 左辺値参照
    StaticMatrixBasicTransforms<int, 3, 3> copy_m1 = ini_m1;
    for(std::size_t i = 0; i < 9; ++i) {
        assert(copy_m1.at(i) == ini_m1_test[i]);
    }
    // コピーコンストラクタ 右辺値参照
    StaticMatrixBasicTransforms<double, 2, 2> copy_m2 = StaticMatrixBasicTransforms<double, 2, 2>{1.1, 2.2, 3.3, 4.4};
    double copy_m2_test[4] = {1.1, 2.2, 3.3, 4.4};
    for(std::size_t i = 0; i < 4; ++i) {
        assert(copy_m2.at(i) == copy_m2_test[i]);
    }
}
TEST(LinearAlgebraTest, StaticMatrixBasicTransformsTranposeTest) {
    StaticMatrixBasicTransforms<int, 4, 3> m1 = {{1, 2, 3}, {6, 7, 8}, {4, 5, 6}, {9, 8, 7}};
    std::array<int, 12> m1_test = {1, 6, 4, 9, 2, 7, 5, 8, 3, 8, 6, 7};
    StaticMatrixBasicTransforms<int, 3, 3> m2 = {{4, 5, 6}, {1, 2, 3}, {9, 8, 7}};
    std::array<int, 9> m2_test = {4, 1, 9, 5, 2, 8, 6, 3, 7};
    // static
    const auto m1_transposed1 = StaticMatrixBasicTransforms<int, 4, 3>::Transpose(m1);
    const auto m1_transposed2 = decltype(m1)::Transpose(m1);
    for(std::size_t r = 0; r < 3; ++r) {
        for(std::size_t c = 0; c < 4; ++c) {
            assert(m1_transposed1.at(4 * r + c) == m1_test.at(4 * r + c));
            assert(m1_transposed2.at(4 * r + c) == m1_test.at(4 * r + c));
        }
    }
    m2.transpose();
    for(std::size_t i = 0; i < 9; ++i) {
        assert(m2.at(i) == m2_test.at(i));
    }
}