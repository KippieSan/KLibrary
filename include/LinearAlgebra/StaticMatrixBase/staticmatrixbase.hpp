#ifndef staticmatrixbase_hpp
#define staticmatrixbase_hpp
#include "staticmatrixbase_shape.hpp"
#include "staticmatrixbase_alias_and_concepts.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <concepts>

namespace linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticMatrixBase {
        private:
            Array<ElemT, Rows * Cols> matrix_;
        public:
            StaticMatrixBase(const ElemT& elem = 0) {
                this->matrix_.fill(elem);
            }
            StaticMatrixBase(std::initializer_list<std::initializer_list<ElemT>>&& input_matrix) {
                static_assert(Rows != 0 && Cols != 0);
                assert(input_matrix.size() == Rows);
                for(const auto& row: input_matrix) {
                    assert(row.size() == Cols);
                }
                
                auto matrix_iterator = this->matrix_.begin();
                for(const auto& row: input_matrix) {
                    std::move(std::begin(row), std::end(row), matrix_iterator);
                    std::advance(matrix_iterator, Rows);
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
                    std::move(row.begin(), row.end(), matrix_iterator);
                    std::advance(matrix_iterator, Rows);
                }
            }
            StaticMatrixBase(const Array<ElemT, Rows * Cols>& input_matrix) {
                static_assert(Rows != 0 && Cols != 0);

                std::move(input_matrix.begin(), input_matrix.end(), this->matrix_.begin());
            }
            StaticMatrixBase(const StaticMatrixBase<ElemT, Rows, Cols>& input): matrix_(input.matrix_){}
            StaticMatrixBase(StaticMatrixBase<ElemT, Rows, Cols>&& input): matrix_(input.matrix_){}

            const ElemT& operator()(const SizeT& r, const SizeT& c) const {
                assert(r < Rows);
                assert(c < Cols);
                return this->matrix_.at(Rows * r + c);
            }
            ElemT& operator()(const SizeT& r, const SizeT& c) {
                assert(r < Rows);
                assert(c < Cols);
                return this->matrix_.at(Rows * r + c);
            }
            const ElemT& at(const SizeT& i) const {
                assert(i < Rows * Cols);
                return this->matrix_.at(i);
            }
            constexpr MatrixBaseShape shape() const noexcept {
                return MatrixBaseShape(Rows, Cols);
            }

            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            StaticMatrixBase& operator+=(const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& matrix) {
                static_assert(Rows == Rows_R);
                static_assert(Cols == Cols_R);
                static_assert(IsConvertibleTo<ElemT_R, ElemT>);

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    this->matrix_.at(i) += static_cast<ElemT>(matrix.at(i));
                }
                return (*this);
            }
            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            StaticMatrixBase& operator-=(const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& matrix) {
                static_assert(Rows == Rows_R);
                static_assert(Cols == Cols_R);
                static_assert(std::convertible_to<ElemT_R, ElemT>);

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    this->matrix_.at(i) -= static_cast<ElemT>(matrix.at(i));
                }
                return (*this);
            }
            template <class ElemT_R, SizeT Rows_R, SizeT Cols_R>
            StaticMatrixBase& operator*=(const StaticMatrixBase<ElemT_R, Rows_R, Cols_R>& matrix) {
                static_assert(Rows == Cols);
                static_assert(Rows_R == Cols_R);
                static_assert(Rows == Rows_R);
                static_assert(std::convertible_to<ElemT_R, ElemT>);

                const SizeT N = Rows;
                StaticMatrixBase<ElemT, Rows, Cols> result;
                for(SizeT r = 0; r < N; ++r) {
                    for(SizeT i = 0; i < N; ++i) {
                        for(SizeT c = 0; c < N; ++c) {
                            result.matrix_.at(r * N + c) += (*this).at(r * N + i) * static_cast<ElemT>(matrix.at(i * N + c));
                        }
                    }
                }
                this->matrix_ = std::move(result.matrix_);
                return (*this);
            }
            template <class ScalarType>
            StaticMatrixBase& operator*=(const ScalarType& scalar) {
                static_assert(std::convertible_to<ScalarType, ElemT>);

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    this->matrix_.at(i) *= static_cast<ElemT>(scalar);
                }
                return (*this);
            }
            template <class ScalarType>
            StaticMatrixBase& operator/=(const ScalarType& scalar) {
                static_assert(std::convertible_to<ScalarType, ElemT>);
                assert(scalar != ScalarType());

                for(SizeT i = 0; i < Rows * Cols; ++i) {
                    this->matrix_.at(i) /= static_cast<ElemT>(scalar);
                }
                return (*this);
            }

            friend std::ostream& operator<<(std::ostream&, const StaticMatrixBase&);
    };
    template <class ElemT, SizeT Rows, SizeT Cols>
    std::ostream& operator<<(std::ostream& cout, const StaticMatrixBase<ElemT, Rows, Cols>& input_matrix) {
        const auto& matrix = input_matrix.matrix_;
        for(SizeT r = 0; r < Rows; ++r) {
            cout << "{ ";
            SizeT c = 0;
            for(; c < Cols - 1; ++c) {
                cout << matrix.at(Rows * r + c) << ", ";
            }
            cout << matrix.at(Rows * r + c) << " }" << std::endl;
        }
        return cout;
    }
}
#endif // staticmatrixbase_hpp