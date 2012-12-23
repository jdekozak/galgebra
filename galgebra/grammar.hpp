#include <boost/proto/proto.hpp>

#include "./dimension.hpp"

#include "./operations/conversion.hpp"
#include "./operations/addition.hpp"
#include "./operations/geometric_product.hpp"

#include "./types/base.hpp"

namespace galgebra {
  namespace expression_templates {
    template<typename METRIC
	     ,typename VALUE_TYPE
	     ,typename BASE_SYMBOLS
	     >
    struct grammar {
      typedef METRIC metric;
      typedef VALUE_TYPE value_type;
      typedef BASE_SYMBOLS base_symbols;
      //traits
      template <typename T>
      struct is_base :
	boost::mpl::false_
      {};
      template <std::size_t N>
      struct is_base<types::base_c<metric, base_symbols, N> > :
	boost::mpl::true_
      {};
      template <typename N>
      struct is_base<types::base<metric, base_symbols, N> > :
	boost::mpl::true_
      {};
      //multivector grammar
      struct multivector;
      struct scalar
	: boost::proto::terminal< boost::proto::convertible_to< value_type > >
      {};
      struct basis
	: boost::proto::and_<boost::proto::terminal<boost::proto::_>
			     ,boost::proto::if_<is_base<boost::proto::_value>() >
			     >
      {};
      //basis is before scalar as it is more restrictive definition ?
      //scalar before basis => doesn't work !
      //maybe because a base is convertible to a scalar...
      struct terminal
	: boost::proto::or_<basis
			    ,scalar
			    >
      {};
      struct make_blade
	: boost::proto::or_<boost::proto::when<basis
					       ,_make_blade<value_type>(boost::proto::_value)
					       >
			    ,boost::proto::when<scalar
						,_make_blade<value_type>(boost::proto::_value)
						>
			    >
      {};
      struct plus
	: boost::proto::or_<boost::proto::when<boost::proto::plus< terminal, terminal >
					       ,add_blades(make_blade(boost::proto::_left), make_blade(boost::proto::_right))
					       >
			    ,boost::proto::when<boost::proto::plus< terminal, multivector>
						,add_multivector_with_blade(multivector(boost::proto::_right), make_blade(boost::proto::_left))
						>
			    ,boost::proto::when<boost::proto::plus< multivector, terminal>
						,add_multivector_with_blade(multivector(boost::proto::_left), make_blade(boost::proto::_right))
						>
			    ,boost::proto::when<boost::proto::plus< multivector, multivector>
						,add_multivectors(multivector(boost::proto::_left), multivector(boost::proto::_right))
						>
			    >
      {};
      struct multiplies
	: boost::proto::or_<boost::proto::when<boost::proto::multiplies< terminal, terminal >
					       ,operations::product_bases<metric, value_type>(make_blade(boost::proto::_left), make_blade(boost::proto::_right))
					       >
			    ,boost::proto::when<boost::proto::multiplies<terminal, multivector>
						,operations::product_bases<metric, value_type>(make_blade(boost::proto::_left), multivector(boost::proto::_right))
						>
			    ,boost::proto::when<boost::proto::multiplies<multivector, terminal>
						,operations::product_bases<metric, value_type>(make_blade(boost::proto::_right), multivector(boost::proto::_left))
						>
			    ,boost::proto::when<boost::proto::multiplies<multivector, multivector>
						,operations::product_multivectors(multivector(boost::proto::_left), multivector(boost::proto::_right))
						>
			    >
      {};
      struct multivector
	: boost::proto::or_<boost::proto::when<terminal
					       ,make_blade(boost::proto::_value)
					       >
			    ,boost::proto::when<multiplies
						,multiplies(boost::proto::_expr)
						>
			    ,boost::proto::when<plus
						,plus(boost::proto::_expr)
						>
			    >
      {};
    };
  }
}
