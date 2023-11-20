#include <gtest/gtest.h>
#include <array>
#include <iostream>
#include "./../../../include/LinearAlgebra/StaticMatrix/BasicMatrices/staticmatrix_basic_matrices.hpp"
namespace {
    using namespace klibrary::linear_algebra;
}
TEST(LinearAlgebraStaticMatrixBasicMatricesTest, ConstructorTest) {
    StaticMatrixBasicMatrices<int, 3, 3> dm1;
    StaticMatrixBasicMatrices<int, 4, 5> cm1(5);
    StaticMatrixBasicMatrices<int, 3, 3> ini_m1 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    StaticMatrixBasicMatrices<int, 2, 2> ini_m2 = {1, 2, 3, 4};
    std::array<std::array<int, 2>, 3> arr1 = {{{1, 2}, {2, 3}, {1, 2}}};
    StaticMatrixBasicMatrices<int, 3, 2> arr_m1 = arr1;
    std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
    StaticMatrixBasicMatrices<int, 6, 1> arr_m2 = arr2;
    StaticMatrixBasicMatrices<int, 1, 6> arr_m3 = arr2;
    StaticMatrixBasicMatrices<int, 3, 3> copy_m1 = ini_m1;
    StaticMatrixBasicMatrices<double, 2, 2> copy_m2 = StaticMatrixBasicMatrices<double, 2, 2>{1.1, 2.2, 3.3, 4.4};


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
TEST(LinearAlgebraStaticMatrixBasicMatricesTest, Test) {
    const auto zero = StaticMatrixBasicMatrices<int, 5, 3>::Zero();
    const auto one = StaticMatrixBasicMatrices<int, 3, 2>::One();
    const auto eye = StaticMatrixBasicMatrices<int, 4, 4>::I();
    std::array<int, 3> diag = {2, 3, 4};
    const auto diag1 = StaticMatrixBasicMatrices<int, 3, 3>::Diag({2, 3, 4});
    const auto diag2 = StaticMatrixBasicMatrices<int, 3, 3>::Diag(diag);


    for(std::size_t i = 0; i < 15; ++i) {
        assert(zero.at(i) == 0);
    }
    for(std::size_t i = 0; i < 6; ++i) {
        assert(one.at(i) == 1);
    }
    for(std::size_t r = 0; r < 4; ++r) {
        for(std::size_t c = 0; c < 4; ++c) {
            assert(r == c ? eye(r, c) == 1 : eye(r, c) == 0);
        }
    }
    for(std::size_t r = 0; r < 3; ++r) {
        for(std::size_t c = 0; c < 3; ++c) {
            assert(r == c ? diag1(r, c) == diag.at(r) : diag1(r, c) == 0);
            assert(r == c ? diag2(r, c) == diag.at(r) : diag2(r, c) == 0);
        }
    }
}