#include <gtest/gtest.h>
#include "../../include/NumericalAnalysis/numerical_differentiation.hpp"
#include "../../include/NumericalAnalysis/approximation_algorithm.hpp"
#include "../../include/NumericalAnalysis/constants.hpp"

#include <limits>
#include <functional>
#include <cmath>
#include <numbers>
namespace {
    using namespace numerical_analysis;
}
void derivative_test(numerical_analysis::Derivative::Type type, double order) {
    /*
     * 誤差の最大許容値
     * 
     * 各微分法の誤差のオーダーはそれぞれ
     * 
     * - 前進差分法、後退差分法 (O(h))
     * - 中心差分法 (O(h^2))
     * - 5点公式 (O(h^4))
     * - 7点公式 (O(h^6))
     * 
     * であるから、hが1 * 10^mであると仮定すれば
     * これより1次次数を下げた値が許容される誤差の最大値となる。
     */
    const double epsilon = order / Constants::h;
    /*
     * 入力関数
     * f0   : 0.2x^4 + 0.5x^3 - x^2 + 3.1x - 2.0
     * f1   : cos(x)
     * f2   : e^(3x) + sin^2(x)
     * f3   : arctan(x) * sin(x) * e^(0.5x)
     */
    const auto f0 = [](const double x) { return 0.2 * std::pow(x, 4) + 0.5 * std::pow(x, 3) - std::pow(x, 2) + 3.1 * x - 2.0; };
    const auto f1 = [](const double x) { return std::cos(x); };
    const auto f2 = [](const double x) { return std::exp(3 * x) + std::pow(std::sin(x), 2); };
    const auto f3 = [](const double x) { return std::atan(x) * std::sin(x) * std::exp(0.5 * x); };
    // 数値微分による値と実際の値は閾値を下回るか
    EXPECT_LT(std::abs(Derivative(f0).with_respect_to(0.73, type)         - (2.75056))        , epsilon);
    EXPECT_LT(std::abs(Derivative(f1).with_respect_to(2.7, type)          - (-0.42738))       , epsilon);
    EXPECT_LT(std::abs(Derivative(f2, 0.0001).with_respect_to(0.21, type) - (6.04059))        , epsilon);
    EXPECT_LT(std::abs(Derivative(f3).with_respect_to(3.0, type)          - (-5.08359))       , epsilon);
    return;
}
TEST(NumericalAnalysisTest, ForwardDerivativeTest) {
    derivative_test(Derivative::Type::Forward, Constants::h);
}
TEST(NumericalAnalysisTest, BackwardDerivativeTest) {
    derivative_test(Derivative::Type::Backward, Constants::h);
}
TEST(NumericalAnalysisTest, CentralDerivativeTest) {
    derivative_test(Derivative::Type::Central, std::pow(Constants::h, 2));
}
TEST(NumericalAnalysisTest, FivePointsDerivativeTest) {
    derivative_test(Derivative::Type::FivePoints, std::pow(Constants::h, 4));
}
TEST(NumericalAnalysisTest, SevenPointsDerivativeTest) {
    derivative_test(Derivative::Type::SevenPoints, std::pow(Constants::h, 6));
}

TEST(NumericalAnalysisTest, NewtonRaphsonTest) {
    // 誤差の閾値
    const double epsilon = 10e-5;
    /*
     * 入力関数とその微分関数
     * df0  : 0.5x^4 - 2.4x^3 + 2.82x^2 - 14.956x - 9.6182
     * df1  : -4.2sin(x) - 1.7
     * df2  : 4.6 + 2x - 1 / x*ln^2(x)
     * df3  : (e^x)*(ln(π)/ln(10))
     */
    const auto f0  = [](const double x) {
        return 0.1 * std::pow(x - 1.2, 5) - 0.5 * std::pow(x + 3.1, 3) - 1.1 * std::pow(x - 0.3, 2) + 3.1 * (x + 2.0);
    };
    const auto f1  = [](const double x) { return 4.2 * std::cos(x) - 1.7 * x; };
    const auto f2  = [](const double x) { return 1 / log(x) + std::pow(x + 2.3, 2); };
    const auto f3  = [](const double x) { return std::log10(std::pow(std::numbers::pi, std::exp(x))) - std::numbers::pi; };
    const auto df0 = [](const double x) {
        return 0.5 * std::pow(x, 4) - 2.4 * std::pow(x, 3) + 2.82 * std::pow(x, 2) - 14.956 * x - 9.6182;
    };
    const auto df1 = [](const double x) { return -4.2 * std::sin(x) - 1.7; };
    const auto df2 = [](const double x) { return 4.6 + 2 * x - 1 / (x * std::pow(std::log(x), 2)); };
    const auto df3 = [](const double x) { return std::exp(x) * (std::log(std::numbers::pi) / std::log(10)); };

    // 微分を使ったNewton-Raphson法による解と実解の差は閾値を下回るか
    EXPECT_LT(std::abs(newton_raphson(6  , f0, df0) - (6.65052)), epsilon);
    EXPECT_LT(std::abs(newton_raphson(0  , f1, df1) - (1.10644)), epsilon);
    EXPECT_LT(std::abs(newton_raphson(0.9, f2, df2) - (0.90737)), epsilon);
    EXPECT_LT(std::abs(newton_raphson(2  , f3, df3) - (1.84359)), epsilon);
}

TEST(NumericalAnalysisTest, NewtonRaphson_NumericDerivativeTest) {
    // 誤差の閾値
    const double epsilon = 10e-5;
    /*
     * 入力関数 (NewtonRaphsonTestの入力関数)
     * f0   : 0.1(x - 1.2)^5 - 0.5(x + 3.1)^3 - 1.1(x - 0.3)^2 + 3.1(x + 2.0)
     * f1   : 4.2cos(x) - 1.7x
     * f2   : 1 / ln(x) + (x + 2.3)^2
     * f3   : log((π^e)^x) - π
     */
    const auto f0 = [](const double x) {
        return 0.1 * std::pow(x - 1.2, 5) - 0.5 * std::pow(x + 3.1, 3) - 1.1 * std::pow(x - 0.3, 2) + 3.1 * (x + 2.0);
    };
    const auto f1 = [](const double x) { return 4.2 * std::cos(x) - 1.7 * x; };
    const auto f2 = [](const double x) { return 1 / log(x) + std::pow(x + 2.3, 2); };
    const auto f3 = [](const double x) { return std::log10(std::pow(std::numbers::pi, std::exp(x))) - std::numbers::pi; };

    // 数値微分を使ったNewton-Raphson法による解と実解の差は閾値を下回るか
    EXPECT_LT(std::abs(newton_raphson(6  , f0) - (6.65052)) , epsilon);
    EXPECT_LT(std::abs(newton_raphson(0  , f1) - (1.10644)) , epsilon);
    EXPECT_LT(std::abs(newton_raphson(0.9, f2) - (0.90737)) , epsilon);
    EXPECT_LT(std::abs(newton_raphson(2  , f3) - (1.84359)) , epsilon);
}

TEST(NumericalAnalysisTest, BisectionMethodTest) {
    // 誤差の閾値
    const double epsilon = 10e-5;
    /*
     * 入力関数 (NewtonRaphsonTestの入力関数)
     * f0   : 0.1(x - 1.2)^5 - 0.5(x + 3.1)^3 - 1.1(x - 0.3)^2 + 3.1(x + 2.0)
     * f1   : 4.2cos(x) - 1.7x
     * f2   : 1 / ln(x) + (x + 2.3)^2
     * f3   : log((π^e)^x) - π
     */
    const auto f0  = [](const double x) {
        return 0.1 * std::pow(x - 1.2, 5) - 0.5 * std::pow(x + 3.1, 3) - 1.1 * std::pow(x - 0.3, 2) + 3.1 * (x + 2.0);
    };
    const auto f1  = [](const double x) { return 4.2 * std::cos(x) - 1.7 * x; };
    const auto f2  = [](const double x) { return 1 / log(x) + std::pow(x + 2.3, 2); };
    const auto f3  = [](const double x) { return std::log10(std::pow(std::numbers::pi, std::exp(x))) - std::numbers::pi; };


    // 二分法による解と実解の差は閾値を下回るか
    EXPECT_LT(std::abs(bisection_method(f0, 5, 7)           - (6.65052)), epsilon);
    EXPECT_LT(std::abs(bisection_method(f1, 1, 1.2)         - (1.10644)), epsilon);
    EXPECT_LT(std::abs(bisection_method(f2, 0.90 , 0.91)    - (0.90737)), epsilon);
    EXPECT_LT(std::abs(bisection_method(f3, 0, 2)           - (1.84359)), epsilon);
}
