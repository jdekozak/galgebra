#if !defined(GALGEBRA_MAP_ITERATOR)
#define GALGEBRA_MAP_ITERATOR

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

#include <boost/mpl/int.hpp>

#include "./detail/next_impl.hpp"
#include "./detail/prior_impl.hpp"
#include "./detail/deref_impl.hpp"
#include "./detail/advance_impl.hpp"
#include "./detail/distance_impl.hpp"
#include "./detail/value_of_impl.hpp"
#include "./detail/equal_to_impl.hpp"
#include "./detail/key_of_impl.hpp"
#include "./detail/value_of_data_impl.hpp"
#include "./detail/deref_data_impl.hpp"

#include "./map_iterator_fwd.hpp"

namespace boost { namespace fusion {

    namespace traits
    {
        template<typename Sequence, int Position>
        struct tag_of<galgebra::map_iterator<Sequence, Position> >
        {
            typedef galgebra::map_iterator_tag type;
        };
    }
}}

namespace galgebra {
    template<typename Sequence, int Position>
    struct map_iterator
        : boost::fusion::iterator_base<map_iterator<Sequence, Position> >
    {
        typedef Sequence sequence_type;
        typedef boost::mpl::int_<Position> index;

        struct category
          : boost::fusion::random_access_traversal_tag
          , boost::fusion::associative_tag
        {};

        map_iterator(const Sequence& sequence)
            : sequence_(sequence) {}

        const Sequence& sequence_;
    };
}

#endif
