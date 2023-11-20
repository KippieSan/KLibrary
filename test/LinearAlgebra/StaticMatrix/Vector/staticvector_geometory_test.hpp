#include <gtest/gtest.h>
#include <array>
#include <iostream>
#include "./../../../../include/LinearAlgebra/StaticMatrix/Vector/Geometory/staticvector_geometory.hpp"
namespace {
    using namespace klibrary::linear_algebra;
}
TEST(LinearAlgebraStaticVectorGeometoryTest, FunctionTest) {
    StaticVectorGeometory<int, 1, 3> v1{3, 4, 5};
    StaticVectorGeometory<int, 1, 3> v2{7, 2, 4};

    int dot_test = 21 + 8 + 20;
    double norm1_test = 3.0 + 4.0 + 5.0;
    double norm2_test = std::sqrt(9.0 + 16.0 + 25.0);
    double norminf_test = 5.0;
    std::array<int, 3> cross_test = {6, 23, -22};


    assert(v1.dot(v2) == dot_test);
    assert(v1.norm(1) == norm1_test);
    assert(v1.norm() == norm2_test);
    assert(v1.norm(Infinity) == norminf_test);

    const auto r1 = v1.cross(v2);
    for(std::size_t i = 0; i < 3; ++i) {
        assert(r1.at(i) == cross_test.at(i));
    }
}
