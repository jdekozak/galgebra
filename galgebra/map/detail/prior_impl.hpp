#if !defined(GALGEBRA_MAP_PRIOR_IMPL)
#define GALGEBRA_MAP_PRIOR_IMPL

#include "../map_iterator_fwd.hpp"

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct prior_impl;

      template<>
      struct prior_impl<galgebra::map_iterator_tag> {
	template<typename Iterator>
	struct apply {
	  typedef typename Iterator::sequence_type sequence_type;
	  typedef typename Iterator::index index;
	  typedef galgebra::map_iterator<sequence_type, index::value - 1> type;

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
