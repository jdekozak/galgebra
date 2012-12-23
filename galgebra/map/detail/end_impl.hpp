#if !defined(GALGEBRA_MAP_END_IMPL)
#define GALGEBRA_MAP_END_IMPL

#include "../map_iterator.hpp"

namespace galgebra
{
    struct map_sequence_tag;
}

namespace boost { namespace fusion {
    
    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<galgebra::map_sequence_tag>
        {
            template<typename Sequence>
            struct apply
            {
	        typedef galgebra::map_iterator<Sequence, Sequence::size::value> type;

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
