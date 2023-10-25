#ifndef approximation_algorithm
#define approximation_algorithm
#include <functional>
#include <limits>
#include <iostream>
#include "constants.hpp"
namespace numerical_analysis {
    using function = std::function<double(double)>;
    class Derivative;

    /*
     * f(x)の微分df(x)が既知である場合にNewton-Raphson法によるf(x)=0の解の探索を行う。
     *
     * 引数
     * - current_x      : 探索を開始するx
     * - f              : f(x)
     * - df             : df(x)
     * - epsilon        : 収束判定の条件
     * - max_attempts   : 最大試行回数
     */
    double newton_raphson(
        double current_x,
        const function&  f,
        const function& df,
        const double& epsilon           = Constants::epsilon,
        const std::size_t& max_attempts = Constants::max_attempts
    ) {
        for(std::size_t i = 0; i < max_attempts; ++i) {
            double next_x = current_x - f(current_x) / df(current_x);
            if(std::abs((next_x - current_x) / current_x) < epsilon) {
                return next_x;
            }
            current_x = next_x;
        }
        return current_x;
    }

    /*
     * f(x)の微分df(x)が未知である場合に数値微分でdf(x)を求め、Newton-Raphson法によるf(x)=0の解の探索を行う。
     *
     * 引数
     * - current_x      : 探索を開始するx
     * - f              : f(x)
     * - h              : 微分変化量
     * - epsilon        : 収束判定条件
     * - type           : 数値微分方法指定 (前進差分、中心差分、後退差分)
     * - max_attempts   : 最大試行回数
     */
    double newton_raphson(
        double current_x,
        const function& f,
        const double& h                 = Constants::h,
        const double& epsilon           = Constants::epsilon,
        const Derivative::Type type     = Derivative::Type::Central,
        const std::size_t& max_attempts = Constants::max_attempts
    ) {
        for(std::size_t i = 0; i < max_attempts; ++i) {
            double next_x = current_x - f(current_x) / Derivative(f, h).with_respect_to(current_x);
            if(std::abs((next_x - current_x) / current_x) < epsilon) {
                return next_x;
            }
            current_x = next_x;
        }
        return current_x;
    }
}
#endif // approximation_algorithm
