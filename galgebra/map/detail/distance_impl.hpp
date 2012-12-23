#if !defined(GALGEBRA_MAP_DISTANCE_IMPL)
#define GALGEBRA_MAP_DISTANCE_IMPL

#include <boost/mpl/minus.hpp>

namespace galgebra {
  struct map_iterator_tag;
}

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct distance_impl;

      template<>
      struct distance_impl<galgebra::map_iterator_tag> {
	template<typename First, typename Last>
	struct apply
	  : boost::mpl::minus<typename Last::index, typename First::index> {
	  typedef apply<First, Last> self;

	  static typename self::type
	  call(First const& first, Last const& last) {
	    return typename self::type();
	  }
	};
      };
    }
  }
}

#endif
