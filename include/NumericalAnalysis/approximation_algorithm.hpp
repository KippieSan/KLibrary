#ifndef approximation_algorithm
#define approximation_algorithm
#include <functional>
#include <limits>
#include <iostream>
#include "constants.hpp"
namespace numerical_analysis {
    class Derivative;
    double newton_raphson(
              double                          current_x,
        const std::function<double(double)>&  f,
              std::function<double(double)>&  df,
        const double&                         h               = Constants::h,
        const double&                         epsilon         = Constants::epsilon,
        const std::size_t&                    max_attempts    = Constants::max_attempts
    )
    {
        if(df == nullptr) {
            df = [&](double x){ return (f(x + h / 2) - f(x - h / 2)) / h; };
        }
        for(std::size_t i = 0; i < max_attempts; ++i) {
            double next_x = current_x - f(current_x) / df(current_x);
            if(std::abs((next_x - current_x) / current_x) < epsilon) {
                return next_x;
            }
            current_x = next_x;
        }
        return current_x;
    }
    double newton_raphson(
        double                                  current_x,
        const std::function<double(double)>&    f,
        const double&                           h               = Constants::h,
        const double&                           epsilon         = Constants::epsilon,
        const std::size_t&                      max_attempts    = Constants::max_attempts
    ) {
        for(std::size_t i = 0; i < max_attempts; ++i) {
            double next_x = current_x - f(current_x) / Derivative(f).with_respect_to(current_x);
            if(std::abs((next_x - current_x) / current_x) < epsilon) {
                return next_x;
            }
            current_x = next_x;
        }
        return current_x;
    }
}
#endif // approximation_algorithm
