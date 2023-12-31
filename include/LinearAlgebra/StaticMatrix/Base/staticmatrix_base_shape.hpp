#ifndef staticmatrix_base_shape_hpp
#define staticmatrix_base_shape_hpp
#include <cstddef>
namespace klibrary::linear_algebra {
    class MatrixBaseShape {
        private:
            std::size_t row_;
            std::size_t column_;
        public:
            MatrixBaseShape() = delete;
            MatrixBaseShape(const std::size_t& row, const std::size_t& column): row_(row), column_(column){}
            MatrixBaseShape(const MatrixBaseShape& shape): MatrixBaseShape(shape.row_, shape.column_){}
            MatrixBaseShape(MatrixBaseShape&& shape): MatrixBaseShape(shape.row_, shape.column_){}

            constexpr std::size_t row() const noexcept { return this->row_; }
            constexpr std::size_t col() const noexcept { return this->column_; }
    };
}
#endif // staticmatrix_base_shape_hpp