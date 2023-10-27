#ifndef constants
#define constants
#include <cstddef>
#include <numbers>
namespace numerical_analysis {
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