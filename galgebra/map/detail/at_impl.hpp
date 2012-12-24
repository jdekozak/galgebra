#if !defined(GALGEBRA_MAP_AT_IMPL)
#define GALGEBRA_MAP_AT_IMPL

#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

#include "../map_iterator_fwd.hpp"

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct at_impl;

      template<>
      struct at_impl<galgebra::map_sequence_tag> {
	template<typename Sequence, typename N>
	struct apply;

	template<typename Sequence, typename N>
	struct apply {
	  typedef apply<typename Sequence::tail, typename boost::mpl::minus<N, boost::mpl::int_<1> >::type > super;
	  typedef typename super::type type;
	  static type
	  call(Sequence& sequence) {
	    return super::call(sequence.tail_);
	  }
	};

	template<typename Sequence>
	struct apply<Sequence, boost::mpl::integral_c<int, 0> > {
	  typedef typename Sequence::head type;
	  static type
	  call(Sequence& sequence) {
	    return sequence.head_;
	  }
	};
	template<typename Sequence>
	struct apply<Sequence, boost::mpl::int_<0> > {
	  typedef typename Sequence::head type;
	  static type
	  call(Sequence& sequence) {
	    return sequence.head_;
	  }
	};
      };
    }
  }
}

#endif
