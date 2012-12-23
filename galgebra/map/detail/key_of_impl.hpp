#if !defined(GALGEBRA_MAP_KEY_OF_IMPL)
#define GALGEBRA_MAP_KEY_OF_IMPL

#include <boost/mpl/if.hpp>

namespace galgebra
{
    struct map_iterator_tag;
}

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct key_of_impl;

        template<>
        struct key_of_impl<galgebra::map_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
  	        typedef typename Iterator::sequence_type::head type;
	    };
        };
    }
}}

#endif
