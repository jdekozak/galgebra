#if !defined(GALGEBRA_MAP_VALUE_OF_IMPL)
#define GALGEBRA_MAP_VALUE_OF_IMPL

#include "../map_iterator_fwd.hpp"

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<galgebra::map_iterator_tag>
        {
            template<typename Iterator>
            struct apply;

  	    template<typename Struct, int Position>
            struct apply<galgebra::map_iterator<Struct, Position> >
            {
	      typedef typename Struct::head type;
            };
        };
    }
}}

#endif
