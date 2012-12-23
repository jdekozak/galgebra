#if !defined(GALGEBRA_MAP_VALUE_AT_IMPL)
#define GALGEBRA_MAP_VALUE_AT_IMPL

#include "../map_iterator_fwd.hpp"

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct value_at_impl;

      template<>
      struct value_at_impl<galgebra::map_sequence_tag> {
	template<typename Sequence, typename N>
	struct apply;

	template<typename Sequence, typename N>
	struct apply {
	  typedef typename apply<typename Sequence::tail
				 ,boost::mpl::minus<N
						    ,boost::mpl::int_<1>
						    >
				 >::type type;
	};
	template<typename Sequence>
	struct apply<Sequence, boost::mpl::integral_c<int, 0> > {
	  typedef typename Sequence::head type;
	};
      };
    }
  }
}

#endif
