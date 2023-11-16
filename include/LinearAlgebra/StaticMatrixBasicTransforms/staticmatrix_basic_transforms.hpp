#ifndef staticmatrix_basic_transforms_hpp
#define staticmatrix_basic_transforms_hpp
#include "./../StaticMatrixBase/staticmatrixbase_alias_and_concepts.hpp"
#include "./../StaticMatrixBase/staticmatrixbase.hpp"
namespace linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticMatrixBasicTransforms : public StaticMatrixBase<ElemT, Rows, Cols> {
        public:
            using StaticMatrixBase<ElemT, Rows, Cols>::StaticMatrixBase;

            static StaticMatrixBasicTransforms<ElemT, Cols, Rows> Transpose(const StaticMatrixBasicTransforms& input) {
                StaticMatrixBasicTransforms<ElemT, Cols, Rows> output;
                for(SizeT r = 0; r < Rows; ++r) {
                    for(SizeT c = 0; c < Cols; ++c) {
                        output(c, r) = input(r, c);
                    }
                }
                return output;
            }
            StaticMatrixBasicTransforms<ElemT, Cols, Rows> transpose() {
                static_assert(Rows == Cols);
                for(SizeT r = 0; r < Rows; ++r) {
                    for(SizeT c = r; c < Cols; ++c) {
                        std::swap((*this)(c, r), (*this)(r, c));
                    }
                }
                return (*this);
            }
    };
}
#endif // staticmatrix_basic_transforms_hpp