#if !defined(GALGEBRA_MAP_IS_SEQUENCE_IMPL)
#define GALGEBRA_MAP_IS_SEQUENCE_IMPL

#include <boost/mpl/bool.hpp>

namespace galgebra
{
    struct map_sequence_tag;
}

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<galgebra::map_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif
