#if !defined(GALGEBRA_MAP_KEY_OF_IMPL)
#define GALGEBRA_MAP_KEY_OF_IMPL

#include "../map_iterator_fwd.hpp"

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct key_of_impl;

      template<>
      struct key_of_impl<galgebra::map_iterator_tag> {
	template<typename Iterator>
	struct apply;

	template <typename Sequence, int Position>
	struct apply<galgebra::map_iterator<Sequence, Position> > {
	  typedef apply<galgebra::map_iterator<typename Sequence::tail, Position - 1> > super;
	  typedef typename super::type type;
	};

	template <typename Sequence>
	struct apply<galgebra::map_iterator<Sequence, 0> > {
	  typedef typename Sequence::head::first_type type;
	};

      };
    }
  }
}

#endif
