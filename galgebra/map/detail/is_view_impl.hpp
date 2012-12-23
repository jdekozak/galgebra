#if !defined(GALGEBRA_MAP_IS_VIEW_IMPL)
#define GALGEBRA_MAP_IS_VIEW_IMPL

#include <boost/mpl/bool.hpp>

namespace galgebra {
  struct map_sequence_tag;
}

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct is_view_impl;

      template<>
      struct is_view_impl<galgebra::map_sequence_tag>
      {
	template<typename T>
	struct apply : boost::mpl::false_ {};
      };
    }
  }
}

#endif
