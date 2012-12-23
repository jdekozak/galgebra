#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/support/pair.hpp>

#include <boost/mpl/integral_c.hpp>

namespace galgebra {
  namespace types {

    template <typename BITFIELD, typename VALUE_TYPE>
    using blade = boost::fusion::pair<BITFIELD, VALUE_TYPE>;

    template <std::size_t BITFIELD, typename VALUE_TYPE>
    using blade_c = blade<boost::mpl::integral_c<size_t,BITFIELD>, VALUE_TYPE >;

  }
}
