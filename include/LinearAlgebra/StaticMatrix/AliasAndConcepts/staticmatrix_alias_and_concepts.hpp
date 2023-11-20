#ifndef staticmatrix_alias_and_concepts_hpp
#define staticmatrix_alias_and_concepts_hpp
#include <concepts>
#include <cstddef>
#include <array>
#include <optional>
#include <cmath>
// 実装内のみで使用される型やコンセプト
namespace klibrary::linear_algebra::alias_and_concepts {
    using SizeT = std::size_t;

    template <class T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    using DefaultFPType = std::double_t;

    template <class ElemT, SizeT size>
    using Array = std::array<ElemT, size>;

    template <class T, class U>
    concept HasCommonTypeWith = std::common_with<T, U>;

    template <class T, class U>
    using CommonTypeOf = std::common_type<T, U>::type;
    
    template <class From, class To>
    concept IsConvertibleTo = std::convertible_to<From, To>;
    
    template <class Operand_L, class Operand_R>
    concept IsAdditionDefined = requires(Operand_L a, Operand_R b) {
        {a + b};
    };
    
    template <class Operand_L, class Operand_R>
    concept IsSubtractionDefined = requires(Operand_L a, Operand_R b) {
        {a - b};
    };
    
    template <class Operand_L, class Operand_R>
    concept IsMultiplicationDefined = requires(Operand_L a, Operand_R b) {
        {a * b};
    };
    
    template <class Operand_L, class Operand_R>
    concept IsDivisionDefined = requires(Operand_L a, Operand_R b) {
        {a / b};
    };

    template <class T>
    concept HasGlobalAbs = requires(T a) {
        { abs(a) } -> std::convertible_to<DefaultFPType>;
    };

    template <class T>
    concept HasMemberAbs = requires(T a) {
        { a.abs() } -> std::convertible_to<DefaultFPType>;
    };

    template <class T>
    concept HasGlobalPow = requires(T a, DefaultFPType b) {
        { pow(a, b) } -> std::convertible_to<DefaultFPType>;
    };

    template <class T>
    concept HasMemberPow = requires(T a, DefaultFPType b) {
        { a.pow(b) } -> std::convertible_to<DefaultFPType>;
    };

    template <class T>
    concept HasGlobalSqrt = requires(T a) {
        { sqrt(a) } -> std::convertible_to<DefaultFPType>;
    };

    template <class T>
    concept HasMemberSqrt = requires(T a) {
        { a.sqrt() } -> std::convertible_to<DefaultFPType>;
    };

}
// ユーザーが使用可能な型やコンセプト
namespace klibrary::linear_algebra {
    template <class T>
    using Infinity = std::optional<T>::nullopt_t;
}
#endif // staticmatrix_alias_and_concepts_hpp