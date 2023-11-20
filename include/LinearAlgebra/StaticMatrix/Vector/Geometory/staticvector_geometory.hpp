#ifndef staticvector_geometory_hpp
#define staticvector_geometory_hpp
#include "./../../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./../Base/staticvector_base.hpp"
#include <optional>
#include <functional>
#include <limits>
namespace {
    using namespace klibrary::linear_algebra::alias_and_concepts;
}
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticVectorGeometory : public StaticVectorBase<ElemT, Rows, Cols> {
        public:
            using StaticVectorBase<ElemT, Rows, Cols>::StaticVectorBase;

            template <FloatingPoint FPType = DefaultFPType>
            FPType norm(const std::optional<SizeT>& p = 2) const {
                if(p == Infinity || p.value() == 0) {
                    FPType max = std::numeric_limits<FPType>::min();
                    for(SizeT i = 0; i < Rows * Cols; ++i) {
                        max = (max < (*this)[i]) ? (*this)[i] : max;
                    }
                    return max;
                }

                static_assert(HasGlobalAbs<ElemT> || HasMemberAbs<ElemT>);
                static_assert(HasGlobalPow<FPType> || HasMemberPow<FPType>);
                static_assert(IsConvertibleTo<SizeT, FPType>);

                auto result = FPType();
                std::function<FPType(SizeT)> f;
                if constexpr(HasGlobalAbs<ElemT>) {
                    if constexpr(HasGlobalPow<FPType>) {
                        f = [&](const SizeT& i){ return pow(abs((*this)[i]), static_cast<FPType>(p.value())); };
                    } else {
                        f = [&](const SizeT& i){ return abs((*this)[i]).pow(static_cast<FPType>(p.value())); };
                    }
                } else {
                    if constexpr(HasGlobalPow<FPType>) {
                        f = [&](const SizeT& i){ return pow(((*this)[i]).abs(), static_cast<FPType>(p.value())); };
                    } else {
                        f = [&](const SizeT& i){ return (((*this)[i]).abs()).pow(static_cast<FPType>(p.value())); };
                    }
                }
                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    result += f(i);
                }
                switch(p.value()) {
                case 1:
                    return result;
                case 2:
                    if constexpr(HasGlobalSqrt<FPType>) {
                        return sqrt(result);
                    } else if constexpr(HasMemberSqrt<FPType>) {
                        return result.sqrt();
                    }
                    [[fallthrough]];
                default:
                    return pow(result, static_cast<FPType>(1.0) / static_cast<FPType>(p.value()));
                }
            }

            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto dot(const StaticVectorGeometory<ElemT_R, Rows_R, Cols_R>& rhs) {
                static_assert(Rows == Rows_R && Cols == Cols_R);
                static_assert(HasCommonTypeWith<ElemT, ElemT_R>);

                using CommonType = CommonTypeOf<ElemT, ElemT_R>;
                
                auto result = CommonType();
                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    if constexpr(IsMultiplicationDefined<ElemT, ElemT_R>) {
                        result += static_cast<CommonType>((*this)[i] * rhs[i]);
                    } else {
                        static_assert(IsMultiplicationDefined<CommonType, CommonType>);
                        result += static_cast<CommonType>((*this)[i]) * static_cast<CommonType>(rhs[i]);
                    }
                }
                return result;
            }

            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto cross(const StaticVectorGeometory<ElemT_R, Rows_R, Cols_R>& rhs) {
                static_assert(Rows == Rows_R && Cols == Cols_R);
                static_assert(Rows == 3 || Cols == 3);
                static_assert(HasCommonTypeWith<ElemT, ElemT_R>);

                using CommonType = CommonTypeOf<ElemT, ElemT_R>;

                auto result = StaticVectorGeometory<CommonType, Rows, Cols>();

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    const SizeT j = (i + 1) % 3;
                    const SizeT k = (i + 2) % 3;
                    if constexpr(IsMultiplicationDefined<ElemT, ElemT_R> && IsSubtractionDefined<ElemT, ElemT_R>) {
                        result[i] = static_cast<CommonType>((*this)[j] * rhs[k] - (*this)[k] * rhs[j]);
                    } else {
                        result[i] =
                            static_cast<CommonType>((*this)[j]) * static_cast<CommonType>(rhs[k]) -
                            static_cast<CommonType>((*this)[k]) * static_cast<CommonType>(rhs[j]);
                    }
                }
                return result;
            }
    };
}
#endif // staticvector_geometory_hpp