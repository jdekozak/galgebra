#if !defined(GALGEBRA_G)
#define GALGEBRA_G

#include <boost/mpl/at.hpp>

namespace galgebra {
  template<typename METRIC, typename I, typename J>
  struct g
    : boost::mpl::at<typename boost::mpl::at<METRIC, I>::type, J>::type
  {};
  template<typename METRIC, std::size_t I, std::size_t J>
  struct g_c
    : g<METRIC, boost::mpl::integral_c<size_t,I>, boost::mpl::integral_c<size_t,J> >
  {};
}

#endif
