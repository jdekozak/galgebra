#if !defined(GALGEBRA_TYPES_BLADE)
#define GALGEBRA_TYPES_BLADE

#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/support/pair.hpp>

#include <boost/mpl/integral_c.hpp>

#include "base.hpp"

namespace galgebra {
  namespace types {

    template <typename Bitfield
	      ,typename ValueType>
    using blade = boost::fusion::pair<Bitfield, ValueType>;

    template <std::size_t Bitfield
	      ,typename ValueType>
    using blade_c = blade<boost::mpl::integral_c<size_t,Bitfield>, ValueType>;

  }
}
/*
      struct basis2blade
	: boost::proto::or_<
	boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 1> > >
			   ,types::blade_c<1, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 2> > >
			    ,types::blade_c<2, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 3> > >
			    ,types::blade_c<4, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 4> > >
			    ,types::blade_c<8, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 5> > >
			    ,types::blade_c<16, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 6> > >
			    ,types::blade_c<32, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 7> > >
			    ,types::blade_c<64, value_type>(get_base_value(boost::proto::_value)) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 8> > >
			    ,types::blade_c<128, value_type>(get_base_value(boost::proto::_value)) >
	>
      {};
*/
#endif
