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
                if(p == Infinity<SizeT> || p == 0) {
                    FPType max = std::numeric_limits<FPType>::min();
                    for(SizeT i = 0; i < Rows * Cols; ++i) {
                        max = (max < (*this)[i]) ? (*this)[i] : max;
                    }
                    return max;
                }

                static_assert(HasGlobalAbs<ElemT> || HasMemberAbs<ElemT>);
                static_assert(HasGlobalPow<FPType> || HasMemberPow<FPType>);
                static_assert(IsConvertibleTo<SizeT, FPType>);

                FPType result;
                std::function<FPType(SizeT)> f;
                if constexpr(HasGlobalAbs<ElemT>) {
                    if constexpr(HasGlobalPow<FPType>) {
                        f = [&](const SizeT& i){ return pow(abs((*this)[i]), static_cast<FPType>(p)); };
                    } else {
                        f = [&](const SizeT& i){ return abs((*this)[i]).pow(static_cast<FPType>(p)); };
                    }
                } else {
                    if constexpr(HasGlobalPow<FPType>) {
                        f = [&](const SizeT& i){ return pow(((*this)[i]).abs(), static_cast<FPType>(p)); };
                    } else {
                        f = [&](const SizeT& i){ return (((*this)[i]).abs()).pow(static_cast<FPType>(p)); }
                    }
                }
                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    result += f(i);
                }
                switch(p) {
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
                    return pow(result, static_cast<FPType>(1.0) / static_cast<FPType>(p));
                }
            }
    };
}
#endif // staticvector_geometory_hpp