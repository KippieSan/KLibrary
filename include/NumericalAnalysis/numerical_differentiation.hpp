#ifndef numerical_differentiation
#define numerical_differentiation
#include <functional>
#include "constants.hpp"
namespace numerical_analysis {
    class Derivative {
        private:
            const std::function<double(double)> f_;
            const double h_;

            double forward(const double& x) const noexcept {
                return (1 / h_) * (f_(x + h_) - f_(x));
            }
            double central(const double& x) const noexcept {
                return (1 / h_) * (f_(x + h_ / 2) - f_(x - h_ / 2));
            }
            double backward(const double& x) const noexcept {
                return (1 / h_) * (f_(x) - f_(x - h_));
            }
        public:
            Derivative(const std::function<double(double)>& f, const double h = Constants::h) noexcept : f_(f), h_(h){}

            enum class Type { Forward, Central, Backward };

            double with_respect_to(const double& x, const Type type = Type::Central) {
                switch(type) {
                case Type::Forward:
                    return forward(x);
                    break;
                case Type::Central:
                    return central(x);
                    break;
                case Type::Backward:
                    return backward(x);
                    break;
                }
            }
    };
}
#endif // numerical_differentiation
