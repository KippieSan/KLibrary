#ifndef staticmatrix_basic_matrices_hpp
#define staticmatrix_basic_matrices_hpp
#include "./../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./../Base/staticmatrix_base.hpp"
namespace {
    using namespace klibrary::linear_algebra::alias_and_concepts;
}
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticMatrixBasicMatrices : public StaticMatrixBase<ElemT, Rows, Cols> {
        public:
            using StaticMatrixBase<ElemT, Rows, Cols>::StaticMatrixBase;

            static auto Zero() {
                return StaticMatrixBasicMatrices();
            }
            static auto One() {
                return StaticMatrixBasicMatrices(ElemT(1));
            }
            static auto I() {
                static_assert(Rows == Cols);
                StaticMatrixBasicMatrices<ElemT, Rows, Cols> identity_matrix;
                for(SizeT i = 0; i < Rows; ++i) {
                    identity_matrix(i, i) = ElemT(1);
                }
                return identity_matrix;
            }
            static auto Scalar(const ElemT& a = ElemT()) {
                static_assert(Rows == Cols);
                StaticMatrixBasicMatrices<ElemT, Rows, Cols> scalar_matrix;
                for(SizeT i = 0; i < Rows; ++i) {
                    scalar_matrix(i, i) = a;
                }
                return scalar_matrix;
            }
            static auto Diag(std::initializer_list<ElemT>&& elements_initializer_list) {
                static_assert(Rows == Cols);
                assert(elements_initializer_list.size() == Rows);
                StaticMatrixBasicMatrices<ElemT, Rows, Cols> diagonal_matrix;
                SizeT i = 0;
                for(const auto& element : elements_initializer_list) {
                    diagonal_matrix(i, i) = element;
                    ++i;
                }
                return diagonal_matrix;
            }
            static auto Diag(const Array<ElemT, Rows>& elements_array) {
                static_assert(Rows == Cols);
                assert(elements_array.size() == Rows);
                StaticMatrixBasicMatrices<ElemT, Rows, Cols> diagonal_matrix;
                SizeT i = 0;
                for(const auto& element : elements_array) {
                    diagonal_matrix(i, i) = element;
                    ++i;
                }
                return diagonal_matrix;
            }
    };
}
#endif // staticmatrix_basic_matrices_hpp