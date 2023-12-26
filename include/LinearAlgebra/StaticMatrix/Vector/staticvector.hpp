#ifndef staticvector_hpp
#define staticvector_hpp
#include "./../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./staticvector_base.hpp"
#include "./BasicVectors/staticvector_basic_vectors.hpp"
#include "./Geometory/staticvector_geometory.hpp"
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows>
    class StaticRowVector : 
        public StaticVectorBase<ElemT, Rows, 1>,
        public StaticVectorBasicVectors<ElemT, Rows, 1>,
        public StaticVectorGeometory<ElemT, Rows, 1>
    {
        public:
            using StaticVectorBase<ElemT, Rows, 1>::StaticVectorBase;
    };

    template <class ElemT, SizeT Cols>
    class StaticColVector : 
        public StaticVectorBase<ElemT, 1, Cols>,
        public StaticVectorBasicVectors<ElemT, 1, Cols>,
        public StaticVectorGeometory<ElemT, 1, Cols>
    {
        public:
            using StaticVectorBase<ElemT, 1, Cols>::StaticVectorBase;
    };
}
#endif // staticvector_hpp