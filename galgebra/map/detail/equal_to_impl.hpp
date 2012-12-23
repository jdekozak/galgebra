#if !defined(GALGEBRA_MAP_EQUAL_TO_IMPL)
#define GALGEBRA_MAP_EQUAL_TO_IMPL

#include <boost/mpl/equal_to.hpp>

namespace galgebra
{
    struct map_iterator_tag;
}

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<galgebra::map_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : mpl::equal_to<
                typename It1::index,
                typename It2::index>
            {};
        };
    }
}}

#endif
