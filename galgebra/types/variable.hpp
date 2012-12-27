#if !defined(GALGEBRA_TYPES_VARIABLE)
#define GALGEBRA_TYPES_VARIABLE

#include <iostream>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/string.hpp>

#include "../dimension.hpp"

namespace galgebra {
  namespace types {
    template<typename Metric
	     ,typename ValueType
	     ,typename VariableSymbols
	     ,typename N>
    struct variable {
      typedef Metric metric;
      typedef ValueType value_type;
      typedef VariableSymbols variable_symbols;
      typedef N type;

      static_assert(type::value <= dimension<metric>::value, "Variable is not allowed with dimension.");

      friend std::ostream &operator<<(std::ostream &s, variable) {
	//variables are indexed starting at 1,        variable_symbols starts at 0 index
	return s << boost::mpl::c_str<typename boost::mpl::at_c<variable_symbols, type::value - 1>::type >::value;
      }
    };
    template<typename Metric
	     ,typename ValueType
	     ,typename VariableSymbols
	     ,std::size_t N>
    using variable_c = variable<Metric, ValueType, VariableSymbols, boost::mpl::integral_c<size_t, N> >;
  }
}

#endif
