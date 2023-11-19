#ifndef staticmatrix_basic_transforms_hpp
#define staticmatrix_basic_transforms_hpp
#include "./../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./../Base/staticmatrix_base.hpp"
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticMatrixBasicTransforms : public StaticMatrixBase<ElemT, Rows, Cols> {
        public:
            using StaticMatrixBase<ElemT, Rows, Cols>::StaticMatrixBase;

            static auto Transpose(const StaticMatrixBasicTransforms& input) {
                StaticMatrixBasicTransforms<ElemT, Cols, Rows> output;
                for(SizeT r = 0; r < Rows; ++r) {
                    for(SizeT c = 0; c < Cols; ++c) {
                        output(c, r) = input(r, c);
                    }
                }
                return output;
            }
            auto transpose() {
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