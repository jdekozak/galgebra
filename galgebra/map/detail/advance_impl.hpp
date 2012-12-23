#if !defined(GALGEBRA_MAP_ADVANCE_IMPL)
#define GALGEBRA_MAP_ADVANCE_IMPL

#include "../map_iterator_fwd.hpp"

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct advance_impl;

      template<>
      struct advance_impl<galgebra::map_iterator_tag> {
	template<typename Iterator, typename N>
	struct apply {
	  typedef typename Iterator::sequence_type sequence_type;
	  typedef typename Iterator::index index;
	  typedef galgebra::map_iterator<
	    sequence_type, index::value + N::value> type;

	  static type
	  call(Iterator const& it) {
	    return type(it.sequence_);
	  }
	};
      };
    }
  }
}

#endif
