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
            double five_points(const double& x) const noexcept {
                return (1 / (12 * h_)) * (f_(x - 2 * h_) - 8 * f_(x - h_) + 8 * f_(x + h_) - f_(x + 2 * h_));
            }
            double seven_points(const double& x) const noexcept {
                return (1 / (60 * h_)) * (
                    -f_(x - 3 * h_) + 9 * f_(x - 2 * h_) - 45 * f_(x - h_) +
                    45 * f_(x + h_) - 9 * f_(x + 2 * h_) + f_(x + 3 * h_)
                );
            }
        public:
            Derivative(const std::function<double(double)>& f, const double h = Constants::h) noexcept : f_(f), h_(h){}

            enum class Type { Forward, Central, Backward, FivePoints, SevenPoints };

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
                case Type::FivePoints:
                    return five_points(x);
                    break;
                case Type::SevenPoints:
                    return seven_points(x);
                    break;
                }
            }
    };
}
#endif // numerical_differentiation
