#ifndef row_vector_hpp
#define row_vector_hpp
#include "./../AliasAndConcepts/staticmatrix_alias_and_concepts.hpp"
#include "./staticvector_base.hpp"
namespace klibrary::linear_algebra {
    template <class ElemT, SizeT Rows>
    class StaticRowVector : public StaticVectorBase<ElemT, Rows, 1> {
        public:
            using StaticVectorBase<ElemT, Rows, 1>::StaticVectorBase;
    };
}
#endif // row_vector_hpp