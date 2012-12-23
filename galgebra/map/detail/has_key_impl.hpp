#if !defined(GALGEBRA_MAP_HAS_KEY_IMPL)
#define GALGEBRA_MAP_HAS_KEY_IMPL

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/or.hpp>

namespace galgebra {
  struct map_sequence_tag;
}

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct has_key_impl;
      /*
      template<>
      struct has_key_impl<galgebra::map_sequence_tag> {
	template<typename Sequence, typename Key>
	struct apply
	  : boost::mpl::or_<
	  is_same<Key, fields::name>,
	  is_same<Key, fields::age> >
	{};
      };
      */
    }
  }
}

#endif
