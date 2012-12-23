#if !defined(GALGEBRA_TYPES_BLADE)
#define GALGEBRA_TYPES_BLADE

#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/support/pair.hpp>

#include <boost/mpl/integral_c.hpp>

#include "base.hpp"

namespace galgebra {
  namespace types {
    /*
    template <typename Bitfield
	      ,typename ValueType>
    using blade = boost::fusion::pair<Bitfield, ValueType>;
    */
    template <typename Bitfield
	      ,typename ValueType>
    struct blade
      : boost::fusion::pair<Bitfield, ValueType> {
      blade() : boost::fusion::pair<Bitfield, ValueType>() {}
      blade(const ValueType& value) : boost::fusion::pair<Bitfield, ValueType>(value) {}

      template<typename Metric, typename BaseSymbols, typename N>
      blade(const base<Metric, ValueType, BaseSymbols, N>& base) : boost::fusion::pair<Bitfield, ValueType>(base.value_) {}
      template<typename Metric, typename BaseSymbols, std::size_t N>
      blade(const base_c<Metric, ValueType, BaseSymbols, N>& base) : boost::fusion::pair<Bitfield, ValueType>(base.value_) {}
    };

    template <std::size_t Bitfield
	      ,typename ValueType>
    using blade_c = blade<boost::mpl::integral_c<size_t,Bitfield>, ValueType>;

  }
}

#endif
