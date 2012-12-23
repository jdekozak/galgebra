#if !defined(GALGEBRA_DIMENSION)
#define GALGEBRA_DIMENSION

#include <boost/mpl/size.hpp>

namespace galgebra {
  template<typename Metric>
  struct dimension
    : boost::mpl::size<Metric>::type
  {};
}

#endif
