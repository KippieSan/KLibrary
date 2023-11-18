#ifndef staticmatrixbase_hpp
#define staticmatrixbase_hpp
#include "staticmatrixbase_shape.hpp"
#include "./../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <concepts>
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticMatrixBase {
        private:
            Array<ElemT, Rows * Cols> matrix_;
        public:
            StaticMatrixBase(const ElemT& elem = ElemT()) {
                this->matrix_.fill(elem);
            }
            StaticMatrixBase(std::initializer_list<std::initializer_list<ElemT>>&& input_matrix) {
                static_assert(Rows != 0 && Cols != 0);
                assert(input_matrix.size() == Rows);
                for(const auto& row: input_matrix) {
                    assert(row.size() == Cols);
                }
                
                auto matrix_iterator = this->matrix_.begin();
                for(auto&& row: input_matrix) {
                    std::move(std::begin(row), std::end(row), matrix_iterator);
                    if(std::distance(matrix_iterator, this->matrix_.end()) > Cols) {
                        std::advance(matrix_iterator, Cols);
                    }
                }
            }
            StaticMatrixBase(std::initializer_list<ElemT>&& input_matrix) {
                static_assert(Rows != 0 && Cols != 0);
                assert(input_matrix.size() == Rows * Cols);

                std::move(input_matrix.begin(), input_matrix.end(), this->matrix_.begin());
            }
            StaticMatrixBase(const Array<Array<ElemT, Cols>, Rows>& input_matrix) {
                static_assert(Rows != 0 && Cols != 0);

                auto matrix_iterator = this->matrix_.begin();
                for(const auto& row: input_matrix) {
                    std::copy(row.begin(), row.end(), matrix_iterator);
                    if(std::distance(matrix_iterator, this->matrix_.end()) > Cols) {
                        std::advance(matrix_iterator, Cols);
                    }
                }
            }
            StaticMatrixBase(const Array<ElemT, Rows * Cols>& input_matrix) {
                static_assert(Rows != 0 && Cols != 0);

                std::copy(input_matrix.begin(), input_matrix.end(), this->matrix_.begin());
            }
            StaticMatrixBase(const StaticMatrixBase<ElemT, Rows, Cols>& input): matrix_(input.matrix_){}
            StaticMatrixBase(StaticMatrixBase<ElemT, Rows, Cols>&& input): matrix_(std::move(input.matrix_)){}
            auto& operator=(const StaticMatrixBase<ElemT, Rows, Cols>& input) {
                this->matrix_ = input.matrix_;
                return (*this);
            }
            auto& operator=(StaticMatrixBase<ElemT, Rows, Cols>&& input) {
                std::move(input.matrix_.begin(), input.matrix_.end(), this->matrix_.begin());
                return (*this);
            }

            const ElemT& operator()(const SizeT& r, const SizeT& c) const {
                assert(r < Rows);
                assert(c < Cols);
                return this->matrix_.at(Cols * r + c);
            }
            ElemT& operator()(const SizeT& r, const SizeT& c) {
                assert(r < Rows);
                assert(c < Cols);
                return this->matrix_.at(Cols * r + c);
            }
            const ElemT& at(const SizeT& i) const {
                assert(i < Rows * Cols);
                return this->matrix_.at(i);
            }
            constexpr MatrixBaseShape shape() const noexcept {
                return MatrixBaseShape(Rows, Cols);
            }

            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto& operator+=(const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& matrix) {
                static_assert(Rows == Rows_R);
                static_assert(Cols == Cols_R);
                static_assert(IsConvertibleTo<ElemT_R, ElemT>);

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    this->matrix_.at(i) += static_cast<ElemT>(matrix.at(i));
                }
                return (*this);
            }
            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto& operator-=(const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& matrix) {
                static_assert(Rows == Rows_R);
                static_assert(Cols == Cols_R);
                static_assert(IsConvertibleTo<ElemT_R, ElemT>);

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    this->matrix_.at(i) -= static_cast<ElemT>(matrix.at(i));
                }
                return (*this);
            }
            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            auto& operator*=(const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& matrix) {
                static_assert(Rows == Cols);        // 左オペランドは正方行列であるか
                static_assert(Rows_R == Cols_R);    // 右オペランドは正方行列であるか
                static_assert(Rows == Rows_R);      // 行列の次数は等しいか
                static_assert(IsConvertibleTo<ElemT_R, ElemT>);

                const SizeT N = Rows;
                StaticMatrixBase<ElemT, Rows, Cols> result;
                for(SizeT r = 0; r < N; ++r) {
                    for(SizeT i = 0; i < N; ++i) {
                        for(SizeT c = 0; c < N; ++c) {
                            if constexpr(IsMultiplicationDefined<ElemT, ElemT_R>) {
                                result.matrix_.at(r * N + c) += static_cast<ElemT>((*this).at(r * N + i) * matrix.at(i * N + c));
                            } else {
                                result.matrix_.at(r * N + c) += (*this).at(r * N + i) * static_cast<ElemT>(matrix.at(i * N + c));
                            }
                        }
                    }
                }
                this->matrix_ = std::move(result.matrix_);
                return (*this);
            }
            template <class ScalarType>
            auto& operator*=(const ScalarType& scalar) {
                static_assert(std::convertible_to<ScalarType, ElemT>);

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    if constexpr(IsMultiplicationDefined<ElemT, ScalarType>) {
                        this->matrix_.at(i) = static_cast<ElemT>(this->matrix_.at(i) * scalar);
                    } else {
                        this->matrix_.at(i) *= static_cast<ElemT>(scalar);
                    }
                }
                return (*this);
            }
            template <class ScalarType>
            auto& operator/=(const ScalarType& scalar) {
                static_assert(std::convertible_to<ScalarType, ElemT>);
                assert(scalar != ScalarType());

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    if constexpr(IsDivisionDefined<ElemT, ScalarType>) {
                        this->matrix_.at(i) = static_cast<ElemT>(this->matrix_.at(i) / scalar);
                    } else {
                        this->matrix_.at(i) /= static_cast<ElemT>(scalar);
                    }
                }
                return (*this);
            }

            void swap_rows(const SizeT& r1, const SizeT& r2) {
                assert(r1 < Rows && r2 < Rows);
                std::array<ElemT, Cols> temp;
                auto r1_begin = std::next(this->matrix_.begin(), r1 * Cols);
                auto r2_begin = std::next(this->matrix_.begin(), r2 * Cols);
                auto r1_end = (r1 == Rows - 1) ? this->matrix_.end() : std::next(this->matrix_.begin(), (r1 + 1) * Cols);
                auto r2_end = (r2 == Rows - 1) ? this->matrix_.end() : std::next(this->matrix_.begin(), (r2 + 1) * Cols);
                
                std::move(r1_begin, r1_end, temp.begin());
                std::move(r2_begin, r2_end, r1_begin);
                std::move(temp.begin(), temp.end(), r2_begin);
                return;
            }
            void swap_cols(const SizeT& c1, const SizeT& c2) {
                assert(c1 < Cols && c2 < Cols);
                for(SizeT r = 0; r < Rows; ++r) {
                    std::swap(this->matrix_.at(r * Cols + c1), this->matrix_.at(r * Cols + c2));
                }
                return;
            }
    };
    template <class ElemT, SizeT Rows, SizeT Cols>
    auto operator+(const StaticMatrixBase<ElemT, Rows, Cols>& matrix) {
        return matrix;
    }
    template <class ElemT, SizeT Rows, SizeT Cols>
    auto operator-(const StaticMatrixBase<ElemT, Rows, Cols>& matrix) {
        auto tmp = matrix;
        tmp *= -1;
        return tmp;
    }
    template <class ElemT_L, SizeT Rows_L, SizeT Cols_L, class ElemT_R, SizeT Rows_R, SizeT Cols_R>
    auto operator+(
        const StaticMatrixBase<ElemT_L, Rows_L, Cols_L>& lhs,
        const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& rhs
    ) {
        static_assert(Rows_L == Rows_R && Cols_L == Cols_R);
        static_assert(HasCommonTypeWith<ElemT_L, ElemT_R>);

        using CommonType = CommonTypeOf<ElemT_L, ElemT_R>;

        constexpr SizeT Rows = Rows_L;
        constexpr SizeT Cols = Cols_L;

        StaticMatrixBase<CommonType, Rows, Cols> result;
        for(SizeT r = 0; r < Rows; ++r) {
            for(SizeT c = 0; c < Cols; ++c) {
                if constexpr(IsAdditionDefined<ElemT_L, ElemT_R>) {
                    result(r, c) = static_cast<CommonType>(lhs(r, c) + rhs(r, c));
                } else {
                    static_assert(IsAdditionDefined<CommonType, CommonType>);
                    result(r, c) = static_cast<CommonType>(lhs(r, c)) + static_cast<CommonType>(rhs(r, c));
                }
            }
        }
        return result;
    }
    template <class ElemT_L, SizeT Rows_L, SizeT Cols_L, class ElemT_R, SizeT Rows_R, SizeT Cols_R>
    auto operator-(
        const StaticMatrixBase<ElemT_L, Rows_L, Cols_L>& lhs,
        const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& rhs
    ) {
        auto tmp = rhs;
        return lhs + (-tmp);
    }
    template <class ElemT_L, SizeT Rows_L, SizeT Cols_L, class ElemT_R, SizeT Rows_R, SizeT Cols_R>
    auto operator*(
        const StaticMatrixBase<ElemT_L, Rows_L, Cols_L>& lhs,
        const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& rhs
    ) {
        static_assert(Cols_L == Rows_R);
        static_assert(HasCommonTypeWith<ElemT_L, ElemT_R>);

        using CommonType = CommonTypeOf<ElemT_L, ElemT_R>;

        constexpr SizeT Rows = Rows_L;
        constexpr SizeT Cols = Cols_R;
        constexpr SizeT Mids = Rows_R;

        StaticMatrixBase<CommonType, Rows_L, Cols_R> result;
        for(SizeT r = 0; r < Rows; ++r) {
            for(SizeT c = 0; c < Cols; ++c) {
                for(SizeT m = 0; m < Mids; ++m) {
                    if constexpr(IsMultiplicationDefined<ElemT_L, ElemT_R>) {
                        result(r, c) += static_cast<CommonType>(lhs(r, m) * rhs(m, c));
                    } else {
                        static_assert(IsMultiplicationDefined<CommonType, CommonType>);
                        result(r, c) += static_cast<CommonType>(lhs(r, m)) * static_cast<CommonType>(rhs(m, c));
                    }
                }
            }
        }
        return result;
    }
    template <class ElemT, SizeT Rows, SizeT Cols, class ScalarType>
    auto operator*(
        const StaticMatrixBase<ElemT, Rows, Cols>& lhs,
        const ScalarType& rhs
    ) {
        auto tmp = lhs;
        tmp *= rhs;
        return tmp;
    }
    template <class ElemT, SizeT Rows, SizeT Cols, class ScalarType>
    auto operator*(
        const ScalarType& lhs,
        const StaticMatrixBase<ElemT, Rows, Cols>& rhs
    ) {
        auto tmp = rhs;
        tmp *= lhs;
        return tmp;
    }
    template <class ElemT, SizeT Rows, SizeT Cols, class ScalarType>
    auto operator/(
        const StaticMatrixBase<ElemT, Rows, Cols>& lhs,
        const ScalarType& rhs
    ) {
        auto tmp = lhs;
        tmp /= rhs;
        return tmp;
    }

    template <class ElemT, SizeT Rows, SizeT Cols>
    std::ostream& operator<<(std::ostream& out, const StaticMatrixBase<ElemT, Rows, Cols>& input_matrix) {
        for(SizeT r = 0; r < Rows; ++r) {
            out << "{ ";
            for(SizeT c = 0; c < Cols; ++c) {
                out << input_matrix(r, c) << (c < Cols - 1 ? ", " : " ");
            }
            out << (r < Rows - 1 ? "}," : "}") << std::endl;
        }
        return out;
    }
}


#endif // staticmatrixbase_hpp