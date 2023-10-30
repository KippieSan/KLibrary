#include "matrix_base_exceptions.hpp"
#include <array>
#include <ranges>
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
                try {
                    // サイズが0の行列は入力不可
                    if(RowSize == 0 || ColumnSize == 0)             throw TriedToInitializeAnEmptyMatrix();
                    // 定義と異なるサイズの入力は不可
                    if(input_matrix.size() != RowSize)              throw MatrixSizeDiffersFromDefinition();
                    for(const auto& row: input_matrix) {
                        if(std::end(row) - std::begin(row) != ColumnSize) throw MatrixSizeDiffersFromDefinition();
                    }
                }
                catch(TriedToInitializeAnEmptyMatrix& e) {
                    std::cerr << e.what() << std::endl;
                    std::terminate();
                }
                catch(MatrixSizeDiffersFromDefinition& e) {
                    std::cerr << e.what() << std::endl;
                    std::terminate();
                }
                auto matrix_iterator = this->matrix_.begin();
                for(const auto& row: input_matrix) {
                    std::move(std::begin(row), std::end(row), matrix_iterator);
                    std::advance(matrix_iterator, RowSize);
                }
            }
            MatrixBase(std::initializer_list<ElementType>&& input_matrix) {
                try {
                    // サイズが0の行列は入力不可
                    if(RowSize == 0 || ColumnSize == 0)             throw TriedToInitializeAnEmptyMatrix();
                    // 定義と異なるサイズの入力は不可
                    if(input_matrix.size() != RowSize * ColumnSize) throw MatrixSizeDiffersFromDefinition();
                }
                catch(TriedToInitializeAnEmptyMatrix& e) {
                    std::cerr << e.what() << std::endl;
                    std::terminate();
                }
                catch(MatrixSizeDiffersFromDefinition& e) {
                    std::cerr << e.what() << std::endl;
                    std::terminate();
                }
                std::move(input_matrix.begin(), input_matrix.end(), this->matrix_.begin());
            }
            MatrixBase(const MatrixBase<ElementType, RowSize, ColumnSize>& input): matrix_(input.matrix){}
            MatrixBase(MatrixBase<ElementType, RowSize, ColumnSize>&& input): matrix_(input.matrix){} 
    };
}