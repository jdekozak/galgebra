#if !defined(GALGEBRA_MAP_TAG_OF)
#define GALGEBRA_MAP_TAG_OF

#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include "./map_type.hpp"

namespace galgebra {
  struct map_sequence_tag;
}

namespace boost {
  namespace fusion {
    namespace traits {
      template<typename... Items>
      struct tag_of<galgebra::map<Items...> > {
	typedef galgebra::map_sequence_tag type;
      };
    }
  }
}

namespace boost {
  namespace mpl {
    template<typename... Items>
    struct sequence_tag<galgebra::map<Items...> > {
      typedef galgebra::map_sequence_tag type;
    };
  }
}

#endif
