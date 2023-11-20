#ifndef staticvector_basic_vectors_hpp
#define staticvector_basic_vectors_hpp
#include "./../../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./../Base/staticvector_base.hpp"
namespace {
    using namespace klibrary::linear_algebra::alias_and_concepts;
}
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows, SizeT Cols>
    class StaticVectorBasicVectors : public StaticVectorBase<ElemT, Rows, Cols> {
        public:
            using StaticVectorBase<ElemT, Rows, Cols>::StaticVectorBase;

            static auto Zero() {
                return StaticVectorBasicVectors<ElemT, Rows, Cols>();
            }
            static auto One() {
                return StaticVectorBasicVectors<ElemT, Rows, Cols>(ElemT(1));
            }
    };
}
#endif // staticvector_basic_vectors_hpp