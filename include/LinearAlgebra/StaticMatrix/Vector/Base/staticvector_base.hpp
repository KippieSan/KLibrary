#ifndef static_vectorbase_hpp
#define static_vectorbase_hpp
#include "./../../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./../../Base/staticmatrix_base.hpp"

namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticVectorBase : private StaticMatrixBase<ElemT, Rows, Cols> {
        public:
            StaticVectorBase(const ElemT& elem = ElemT())                   : StaticMatrixBase<ElemT, Rows, Cols>(elem)        { static_assert(Rows == 1 || Cols == 1); }
            StaticVectorBase(std::initializer_list<ElemT>&& input_vector)   : StaticMatrixBase<ElemT, Rows, Cols>(std::move(input_vector)){ static_assert(Rows == 1 || Cols == 1); }
            StaticVectorBase(const Array<ElemT, Rows * Cols>& input_vector) : StaticMatrixBase<ElemT, Rows, Cols>(input_vector){ static_assert(Rows == 1 || Cols == 1); }
            StaticVectorBase(const StaticVectorBase& vector)                : StaticMatrixBase<ElemT, Rows, Cols>(vector)      { static_assert(Rows == 1 || Cols == 1); }
            StaticVectorBase(StaticVectorBase&& vector)                     : StaticMatrixBase<ElemT, Rows, Cols>(vector)      { static_assert(Rows == 1 || Cols == 1); }
            auto& operator=(const StaticVectorBase& vector) {
                StaticMatrixBase<ElemT, Rows, Cols>::operator=(vector);
                return (*this);
            }
            auto& operator=(StaticVectorBase&& vector) {
                StaticMatrixBase<ElemT, Rows, Cols>::operator=(vector);
                return (*this);
            }
            const ElemT& operator[](const SizeT& i) const {
                return StaticMatrixBase<ElemT, Rows, Cols>::operator[](i);
            }
            ElemT& operator[](const SizeT& i) {
                return StaticMatrixBase<ElemT, Rows, Cols>::operator[](i);
            }
            const ElemT& at(const SizeT& i) const {
                return StaticMatrixBase<ElemT, Rows, Cols>::at(i);
            }
            ElemT& at(const SizeT& i) {
                return StaticMatrixBase<ElemT, Rows, Cols>::at(i);
            }
            constexpr SizeT size() const noexcept {
                return Rows * Cols;
            }

            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto& operator+=(const StaticVectorBase<ElemT_R, Rows_R, Cols_R>& vector) {
                StaticMatrixBase<ElemT, Rows, Cols>::operator+=(vector);
                return (*this);
            }
            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto& operator-=(const StaticVectorBase<ElemT_R, Rows_R, Cols_R>& vector) {
                StaticMatrixBase<ElemT, Rows, Cols>::operator-=(vector);
                return (*this);
            }
            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto& operator*=(const StaticVectorBase<ElemT_R, Rows_R, Cols_R>& vector) {
                static_assert(Rows == Rows_R && Cols == Cols_R);
                static_assert(IsConvertibleTo<ElemT_R, ElemT>);
                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    if constexpr(IsMultiplicationDefined<ElemT, ElemT_R>) {
                        (*this)[i] = static_cast<ElemT>((*this)[i] * vector[i]);
                    } else {
                        (*this)[i] *= static_cast<ElemT>(vector[i]);
                    }
                }
                return (*this);
            }
            template <class ScalarType>
            auto& operator*=(const ScalarType& scalar) {
                StaticMatrixBase<ElemT, Rows, Cols>::operator*=(scalar);
                return (*this);
            }
            template <class ScalarType>
            auto& operator/=(const ScalarType& scalar) {
                StaticMatrixBase<ElemT, Rows, Cols>::operator/=(scalar);
                return (*this);
            }
    };
    template <class ElemT, SizeT Rows, SizeT Cols>
    auto operator+(const StaticVectorBase<ElemT, Rows, Cols>& vector) {
        return vector;
    }
    template <class ElemT, SizeT Rows, SizeT Cols>
    auto operator-(const StaticVectorBase<ElemT, Rows, Cols>& vector) {
        auto tmp = vector;
        tmp *= ElemT(-1);
        return tmp;
    }
    template <class ElemT_L, SizeT Rows_L, SizeT Cols_L, class ElemT_R, SizeT Rows_R, SizeT Cols_R>
    auto operator+(
        const StaticVectorBase<ElemT_L, Rows_L, Cols_L>& lhs,
        const StaticVectorBase<ElemT_R, Rows_R, Cols_R>& rhs
    ) {
        static_assert(Rows_L == Rows_R && Cols_L == Cols_R);
        static_assert(HasCommonTypeWith<ElemT_L, ElemT_R>);

        using CommonType = CommonTypeOf<ElemT_L, ElemT_R>;

        constexpr SizeT Rows = Rows_L;
        constexpr SizeT Cols = Cols_L;

        StaticVectorBase<CommonType, Rows, Cols> result;
        for(SizeT i = 0; i < Rows * Cols; ++i) {
            if constexpr(IsAdditionDefined<ElemT_L, ElemT_R>) {
                result[i] = static_cast<CommonType>(lhs[i] + rhs[i]);
            } else {
                static_assert(IsAdditionDefined<CommonType, CommonType>);
                result[i] = static_cast<CommonType>(lhs[i]) + static_cast<CommonType>(rhs[i]);
            }
        }
        return result;
    }
    template <class ElemT_L, SizeT Rows_L, SizeT Cols_L, class ElemT_R, SizeT Rows_R, SizeT Cols_R>
    auto operator-(
        const StaticVectorBase<ElemT_L, Rows_L, Cols_L>& lhs,
        const StaticVectorBase<ElemT_R, Rows_R, Cols_R>& rhs
    ) {
        static_assert(Rows_L == Rows_R && Cols_L == Cols_R);
        static_assert(HasCommonTypeWith<ElemT_L, ElemT_R>);

        using CommonType = CommonTypeOf<ElemT_L, ElemT_R>;

        constexpr SizeT Rows = Rows_L;
        constexpr SizeT Cols = Cols_L;

        StaticVectorBase<CommonType, Rows, Cols> result;
        for(SizeT i = 0; i < Rows * Cols; ++i) {
            if constexpr(IsSubtractionDefined<ElemT_L, ElemT_R>) {
                result[i] = static_cast<CommonType>(lhs[i] - rhs[i]);
            } else {
                static_assert(IsSubtractionDefined<CommonType, CommonType>);
                result[i] = static_cast<CommonType>(lhs[i]) - static_cast<CommonType>(rhs[i]);
            }
        }
        return result;
    }
    template <class ElemT_L, SizeT Rows_L, SizeT Cols_L, class ElemT_R, SizeT Rows_R, SizeT Cols_R>
    auto operator*(
        const StaticVectorBase<ElemT_L, Rows_L, Cols_L>& lhs,
        const StaticVectorBase<ElemT_R, Rows_R, Cols_R>& rhs
    ) {
        static_assert(Rows_L == Rows_R && Cols_L == Cols_R);
        static_assert(HasCommonTypeWith<ElemT_L, ElemT_R>);

        using CommonType = CommonTypeOf<ElemT_L, ElemT_R>;

        constexpr SizeT Rows = Rows_L;
        constexpr SizeT Cols = Cols_L;

        StaticVectorBase<CommonType, Rows, Cols> result;
        for(SizeT i = 0; i < Rows * Cols; ++i) {
            if constexpr(IsMultiplicationDefined<ElemT_L, ElemT_R>) {
                result[i] = static_cast<CommonType>(lhs[i] * rhs[i]);
            } else {
                static_assert(IsMultiplicationDefined<CommonType, CommonType>);
                result[i] = static_cast<CommonType>(lhs[i]) * static_cast<CommonType>(rhs[i]);
            }
        }
        return result;
    }
    template <class ElemT, SizeT Rows, SizeT Cols, class ScalarType>
    auto operator*(
        const StaticVectorBase<ElemT, Rows, Cols>& lhs,
        const ScalarType& rhs
    ) {
        auto tmp = lhs;
        tmp *= rhs;
        return tmp;
    }
    template <class ElemT, SizeT Rows, SizeT Cols, class ScalarType>
    auto operator*(
        const ScalarType& lhs,
        const StaticVectorBase<ElemT, Rows, Cols>& rhs
    ) {
        auto tmp = rhs;
        tmp *= lhs;
        return tmp;
    }
    template <class ElemT, SizeT Rows, SizeT Cols, class ScalarType>
    auto operator/(
        const StaticVectorBase<ElemT, Rows, Cols>& lhs,
        const ScalarType& rhs
    ) {
        auto tmp = lhs;
        tmp /= rhs;
        return tmp;
    }
    template <class ElemT, SizeT Rows, SizeT Cols>
    std::ostream& operator<<(std::ostream& out, const StaticVectorBase<ElemT, Rows, Cols>& vector) {
        out << "{";
        for(SizeT i = 0; i < Rows * Cols; ++i) {
            out << " " << vector[i] << ((i != (Rows * Cols - 1)) ? "," : " }");
        }
        if constexpr(Cols == 1) {
            out << "T";
        }
        return out;
    }
}

#endif // static_vectorbase_hpp