#if !defined(GALGEBRA_TYPES_BASE)
#define GALGEBRA_TYPES_BASE

#include <iostream>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/string.hpp>

#include "../dimension.hpp"

namespace galgebra {
  namespace types {
    template<typename Metric
	     ,typename ValueType
	     ,typename BaseSymbols
	     ,typename N>
    struct base {
      typedef Metric metric;
      typedef ValueType value_type;
      typedef BaseSymbols base_symbols;
      typedef N type;

      static_assert(type::value <= dimension<metric>::value, "Base is not allowed with dimension.");

      friend std::ostream &operator<<(std::ostream &s, base) {
	//bases are indexed starting at 1,        base_symbols starts at 0 index
	return s << boost::mpl::c_str<typename boost::mpl::at_c<base_symbols, type::value - 1>::type >::value;
      }

      value_type value_;
    };

    template<typename Metric
	     ,typename ValueType
	     ,typename BaseSymbols
	     ,std::size_t N>
    using base_c = base<Metric, ValueType, BaseSymbols, boost::mpl::integral_c<size_t, N> >;

  }
}

#endif
