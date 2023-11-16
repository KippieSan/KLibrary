#ifndef staticmatrix_alias_and_concepts_hpp
#define staticmatrix_alias_and_concepts_hpp
#include <concepts>
#include <cstddef>
#include <array>
namespace linear_algebra {
    // 添え字に使用する型の定義
    using SizeT = std::size_t;
    // 配列型の定義
    template <class ElemT, SizeT size>
    using Array = std::array<ElemT, size>;
    // T, Uから変換可能な共通の型が存在するか
    template <class T, class U>
    concept HasCommonTypeWith = std::common_with<T, U>;
    // T, Uから変換可能な共通の型を返す
    template <class T, class U>
    using CommonTypeOf = std::common_type<T, U>::type;
    // FromからToに変換可能であるか
    template <class From, class To>
    concept IsConvertibleTo = std::convertible_to<From, To>;
    // 加算は定義されているか
    template <class Operand_L, class Operand_R>
    concept IsAdditionDefined = requires(Operand_L a, Operand_R b) {
        {a + b};
    };
    // 減算は定義されているか
    template <class Operand_L, class Operand_R>
    concept IsSubtractionDefined = requires(Operand_L a, Operand_R b) {
        {a - b};
    };
    // 乗算は定義されているか
    template <class Operand_L, class Operand_R>
    concept IsMultiplicationDefined = requires(Operand_L a, Operand_R b) {
        {a * b};
    };
    // 除算は定義されているか
    template <class Operand_L, class Operand_R>
    concept IsDivisionDefined = requires(Operand_L a, Operand_R b) {
        {a / b};
    };
}
#endif // staticmatrix_alias_and_concepts_hpp