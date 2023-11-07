#include <concepts>
#include <cstddef>
namespace linear_algebra {
    using SizeT = std::size_t;
    
    template <class T, class U>
    using CommonTypeOf = std::common_type<T, U>::type;

    template <class From, class To>
    concept IsConvertibleTo = std::convertible_to<From, To>;

    template <class T, class U>
    concept CommonTypeWith = std::common_with<T, U>;

    template <class Operand_L, class Operand_R>
    concept Addable = requires(Operand_L a, Operand_R b) {
        {a + b};
    };
}