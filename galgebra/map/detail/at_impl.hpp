#if !defined(GALGEBRA_MAP_AT_IMPL)
#define GALGEBRA_MAP_AT_IMPL

#include "../map_iterator_fwd.hpp"

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<galgebra::map_sequence_tag>
        {
            template<typename Sequence, typename N>
            struct apply;

  	    template<typename Sequence, typename N>
            struct apply
            {
	      typedef typename galgebra::map_iterator<Sequence, N::value>::head type;

                static type
                call(Sequence& sequence)
                {
                    return sequence.head;
                };
            };
        };
    }
}}

#endif
