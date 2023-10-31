#include "matrix_base_exceptions.hpp"
#include <array>
#include <cassert>
namespace {
    using namespace linear_algebra::matrix_exception;
}
namespace linear_algebra {
    template <class ElementType, std::size_t RowSize, std::size_t ColumnSize>
    class MatrixBase {
        private:
            std::array<ElementType, RowSize * ColumnSize> matrix_;
        public:
            MatrixBase(std::initializer_list<std::initializer_list<ElementType>>&& input_matrix) {
                static_assert(RowSize != 0 && ColumnSize != 0);
                assert(input_matrix.size() == RowSize);
                for(const auto& row: input_matrix) {
                    assert(row.size() == ColumnSize);
                }
                
                auto matrix_iterator = this->matrix_.begin();
                for(const auto& row: input_matrix) {
                    std::move(std::begin(row), std::end(row), matrix_iterator);
                    std::advance(matrix_iterator, RowSize);
                }
            }
            MatrixBase(std::initializer_list<ElementType>&& input_matrix) {
                static_assert(RowSize != 0 && ColumnSize != 0);
                assert(input_matrix.size() == RowSize * ColumnSize);

                std::move(input_matrix.begin(), input_matrix.end(), this->matrix_.begin());
            }
            MatrixBase(const MatrixBase<ElementType, RowSize, ColumnSize>& input): matrix_(input.matrix){}
            MatrixBase(MatrixBase<ElementType, RowSize, ColumnSize>&& input): matrix_(input.matrix){} 
    };
}