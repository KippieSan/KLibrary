#include <gtest/gtest.h>
#include "../../include/NumericalAnalysis/numerical_differentiation.hpp"
#include "../../include/NumericalAnalysis/approximation_algorithm.hpp"

#include <limits>
#include <functional>
#include <cmath>
#include <numbers>

TEST(NumericalAnalysisTest, DerivativeTest) {
    using namespace numerical_analysis;
    // Error threshold
    const double epsilon = 10e-5;
    // Functions
    const auto f0 = [](const double x) { return 0.2 * std::pow(x, 4) + 0.5 * std::pow(x, 3) - std::pow(x, 2) + 3.1 * x - 2.0; };
    const auto f1 = [](const double x) { return std::cos(x); };
    const auto f2 = [](const double x) { return std::exp(3 * x) + std::pow(std::sin(x), 2); };
    const auto f3 = [](const double x) { return std::atan(x) * std::sin(x) * std::exp(0.5 * x); };
    // Derivatives
    EXPECT_LT(std::abs(Derivative(f0).with_respect_to(0.73) - (2.75056))        , epsilon);
    EXPECT_LT(std::abs(Derivative(f1).with_respect_to(2.7) - (-0.42738))        , epsilon);
    EXPECT_LT(std::abs(Derivative(f2, 0.0001).with_respect_to(0.21) - (6.04059)), epsilon);
    EXPECT_LT(std::abs(Derivative(f3).with_respect_to(3.0) - (-5.08359))        , epsilon);
}

TEST(NumericalAnalysisTest, NewtonRaphsonTest) {
    using namespace numerical_analysis;
    // Error threshold
    const double epsilon = 10e-5;
    // Functions
    const auto f0 = [](const double x) {
        return 0.1 * std::pow(x - 1.2, 5) - 0.5 * std::pow(x + 3.1, 3) - 1.1 * std::pow(x - 0.3, 2) + 3.1 * (x + 2.0);
    };
    const auto f1 = [](const double x) { return 4.2 * std::cos(x) - 1.7 * x; };
    const auto f2 = [](const double x) { return 1 / log(x) + std::pow(x + 2.3, 2); };
    const auto f3 = [](const double x) { return std::log10(std::pow(std::numbers::pi, std::exp(x))) - std::numbers::pi; };
    // NewtonRaphson-Method
    EXPECT_LT(std::abs(newton_raphson(6  , f0) - (6.65052)) , epsilon);
    EXPECT_LT(std::abs(newton_raphson(0  , f1) - (1.10644)) , epsilon);
    EXPECT_LT(std::abs(newton_raphson(0.9, f2) - (0.90737)) , epsilon);
    EXPECT_LT(std::abs(newton_raphson(2  , f3) - (1.84359)) , epsilon);
}