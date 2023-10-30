#ifndef matrix_base_exception_hpp
#define matrix_base_exception_hpp
#include "exception.hpp"
#include <string>
#include <sstream>
namespace linear_algebra {
    namespace matrix_exception {
        /*
         * TriedToInitializeAnEmptyMatrix
         * 
         * 0行もしくは0列もしくはその両方の要素がある行列を作成しようとした
         * - terminate
         */
        class TriedToInitializeAnEmptyMatrix : public Exception {
            public:
                TriedToInitializeAnEmptyMatrix() : Exception("\'tried to initialize an empty matrix\'."){}

                TriedToInitializeAnEmptyMatrix(const TriedToInitializeAnEmptyMatrix&)   = delete;
                TriedToInitializeAnEmptyMatrix(TriedToInitializeAnEmptyMatrix&&)        = delete;
        };
        /*
         * MatrixSizeDiffersFromDefinition
         * 
         * 行列のサイズが定義と違う
         * - terminate
         */
        class MatrixSizeDiffersFromDefinition : public Exception {
            public:
                MatrixSizeDiffersFromDefinition() : Exception("\'matrix size differs from definition\'."){}

                MatrixSizeDiffersFromDefinition(const MatrixSizeDiffersFromDefinition&) = delete;
                MatrixSizeDiffersFromDefinition(MatrixSizeDiffersFromDefinition&&)      = delete;
        };
    }
}
#endif //  matrix_base_exception_hpp
