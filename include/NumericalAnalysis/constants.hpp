#ifndef constants
#define constants
#include <cstddef>
#include <numbers>
namespace numerical_analysis {
    /*
     * Constants クラス
     *
     * numerical_analysis名前空間内で提供される関数やクラス内で使用される定数が定義されている。
     * このクラスは静的クラスであり、定数へのアクセスは
     * 
     * Constants::pi;
     * Constants::h;
     * 
     * のようにして行う。
     * 
     * - pi             : 円周率
     * - h              : 数値微分に使用される差分幅
     * - epsilon        : 近似計算における収束判定条件
     * - max_attempts   : 近似計算の最大繰り返し試行回数
     */
    class Constants {
        public:
            Constants()  = delete;
            ~Constants() = delete;

            static constexpr double         pi              = 3.141592653589793;
            static constexpr double         h               = 0.1;
            static constexpr double         epsilon         = 10e-6;
            static constexpr std::size_t    max_attempts    = 10;
    };
}
#endif // constants