#if !defined(GALGEBRA_MAP_DEREF_IMPL)
#define GALGEBRA_MAP_DEREF_IMPL

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include "../map_iterator_fwd.hpp"

template<typename Sequence>
struct get_head {
  typedef typename Sequence::head type;
};

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct deref_impl;

      template<>
      struct deref_impl<galgebra::map_iterator_tag> {
	template<typename Iterator>
	struct apply;

	template<typename Sequence, int Position>
	struct apply<galgebra::map_iterator<Sequence, Position> > {
	  typedef apply<galgebra::map_iterator<typename Sequence::tail, Position - 1> > super;
	  typedef typename super::type type;
	  static type
	  call(galgebra::map_iterator<Sequence, Position> const& it) {
	    return super::call(galgebra::map_iterator<typename Sequence::tail, Position - 1>(it.sequence_.tail_)) ;
	  }
	};

	template <typename Sequence>
	struct apply<galgebra::map_iterator<Sequence, 0> > {
	  typedef typename Sequence::head type;
	  static type
	  call(galgebra::map_iterator<Sequence, 0> const& it) {
	    return it.sequence_.head_;
	  }
	};
      };
    }
  }
}

#endif
