#if !defined(GALGEBRA_MAP_CATEGORY_OF_IMPL)
#define GALGEBRA_MAP_CATEGORY_OF_IMPL

#include <boost/fusion/support/category_of.hpp>

namespace galgebra {
  struct map_sequence_tag;
}

namespace boost {
  namespace fusion {
    namespace extension {
      template<>
      struct category_of_impl<galgebra::map_sequence_tag> {
	template<typename Sequence>
	struct apply {
	  struct type : random_access_traversal_tag, associative_tag {};
	};
      };
    }
  }
}

#endif
