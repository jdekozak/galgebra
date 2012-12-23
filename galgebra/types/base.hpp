#if !defined(GALGEBRA_BASE)
#define GALGEBRA_BASE

#include <iostream>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/string.hpp>

#include "../dimension.hpp"

namespace galgebra {
  namespace types {
    template<typename Metric, typename BaseSymbols, typename N>
    struct base : N {
      typedef Metric metric;
      typedef BaseSymbols base_symbols;
      static_assert(N::value <= dimension<metric>::value, "Base is not allowed with dimension.");
      friend std::ostream &operator<<(std::ostream &s, base) {
	//bases are indexed starting at 1,        base_symbols starts at 0 index
	return s << boost::mpl::c_str<typename boost::mpl::at_c<base_symbols, N::value - 1>::type >::value;
      }
    };
    template<typename Metric, typename BaseSymbols, std::size_t N>
    using base_c = base<Metric, BaseSymbols, boost::mpl::integral_c<size_t, N> >;
  }
}

#endif
