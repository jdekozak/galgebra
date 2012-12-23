#if !defined(GALGEBRA_MAP_BEGIN_IMPL)
#define GALGEBRA_MAP_BEGIN_IMPL

#include "../map_iterator.hpp"

namespace galgebra
{
    struct map_sequence_tag;
}

namespace boost { namespace fusion {
    
    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<galgebra::map_sequence_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef galgebra::map_iterator<Sequence, 0> type;

                static type
                call(Sequence& sequence)
                {
                    return type(sequence);
                }
            };
        };
    }
}}

#endif
