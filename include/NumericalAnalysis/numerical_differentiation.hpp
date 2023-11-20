#ifndef numerical_differentiation
#define numerical_differentiation
#include <functional>
#include "constants.hpp"
namespace numerical_analysis {
    /*
     * Derivative クラス
     * 
     * 使用法
     * 既に定義された関数f(x)についてその微分f'(x)を返す。
     * 
     * Derivative(f).with_respect_to(x);
     * 
     * f(x)は関数やラムダ式などにより定義することができ、例えばsin(x)の微分は
     * 
     * const auto f = [](double x){ return std::sin(x); };
     * Derivative(f).with_respect_to(x);
     * 
     * により求めることができる。
     * 
     * コンストラクタの第2引数で差分幅h(デフォルトでは0.1)を変更することができ。
     * with_respect_to()関数の第2引数で使用する微分方法(デフォルトでは中心差分法)を変更することができる。
     * 微分方法はType列挙クラスにて定義されており、
     * 
     * - 前進差分法 (Type::Forward)
     * - 後退差分法 (Type::Backward)
     * - 中心差分法 (Type::Central)
     * - 5点公式 (Type::FivePoints)
     * - 7点公式 (Type::SevenPoints)
     * 
     * から選択することができる。
     * 
     * 例えば、差分幅を0.01、微分を5点公式により行うのであれば
     * 
     * Derivative(f, 0.01).with_respect_to(x, Derivative::Type::FivePoints);
     * 
     * のように記述する。5点公式および7点公式の導出は以下のサイト参考
     * https://wwwnucl.ph.tsukuba.ac.jp/~hinohara/compphys2-18/doc/compphys2-5.pdf
     */
    class Derivative {
        private:
            const std::function<double(double)> f_;
            const double h_;

            // 前進差分法
            double forward(const double& x) const noexcept {
                return (1 / h_) * (f_(x + h_) - f_(x));
            }
            // 中心差分法
            double central(const double& x) const noexcept {
                return (1 / h_) * (f_(x + h_ / 2) - f_(x - h_ / 2));
            }
            // 後退差分法
            double backward(const double& x) const noexcept {
                return (1 / h_) * (f_(x) - f_(x - h_));
            }
            // 5点公式
            double five_points(const double& x) const noexcept {
                return (1 / (12 * h_)) * (f_(x - 2 * h_) - 8 * f_(x - h_) + 8 * f_(x + h_) - f_(x + 2 * h_));
            }
            // 7点公式
            double seven_points(const double& x) const noexcept {
                return (1 / (60 * h_)) * (
                    -f_(x - 3 * h_) + 9 * f_(x - 2 * h_) - 45 * f_(x - h_) +
                    45 * f_(x + h_) - 9 * f_(x + 2 * h_) + f_(x + 3 * h_)
                );
            }
        public:
            // f: 数値微分を行う関数, h: 差分幅
            Derivative(const std::function<double(double)>& f, const double h = Constants::h) noexcept : f_(f), h_(h){}
            // 数値微分の方法
            enum class Type { Forward, Central, Backward, FivePoints, SevenPoints };
            // xについてtypeの微分方法を用いて微分する
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
                default:
                    return x;
                }
            }
    };
}
#endif // numerical_differentiation
