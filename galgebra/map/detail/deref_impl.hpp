#if !defined(GALGEBRA_MAP_DEREF_IMPL)
#define GALGEBRA_MAP_DEREF_IMPL

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace galgebra
{
    struct map_iterator_tag;

    template<typename Sequence, int Position>
    struct map_iterator;
}

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<galgebra::map_iterator_tag>
        {
            template<typename Iterator>
            struct apply;

	    template<typename Sequence, int Position>
            struct apply<galgebra::map_iterator<Sequence, Position> >
            {
	        typedef typename Sequence::head type;

                static type
                call(galgebra::map_iterator<Sequence, Position> const& it)
                {
                    return it.sequence_.head_;
                }
            };
        };
    }
}}

#endif
