#include <boost/proto/proto.hpp>

#include "./dimension.hpp"

#include "./operations/addition.hpp"
#include "./operations/geometric_product.hpp"

#include "./types/base.hpp"
#include "./types/multivector.hpp"

namespace galgebra {
  namespace expression_templates {
    template<typename Metric
	     ,typename ValueType
	     ,typename BaseSymbols
	     ,typename VariableSymbols
	     >
    struct grammar {
      typedef Metric metric;
      typedef ValueType value_type;
      typedef BaseSymbols base_symbols;
      typedef VariableSymbols variable_symbols;

      struct multivector_domain;
      struct multivector_grammar;

      template< typename Expression >
      struct multivector
	: boost::proto::extends< Expression, multivector< Expression >, multivector_domain >
      {
      };

      struct scalar
	: boost::proto::terminal< boost::proto::convertible_to< value_type > >
      {};
      struct basis
	: boost::proto::or_<
	boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 1> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 2> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 3> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 4> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 5> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 6> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 7> > >
	,boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 8> > >
	>
      {};
      struct variable
	: boost::proto::or_<
	boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 1> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 2> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 3> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 4> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 5> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 6> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 7> > >
	,boost::proto::terminal<types::variable<metric, value_type, variable_symbols, boost::mpl::integral_c<size_t, 8> > >	
	>
      {};
      //basis is before scalar as it is more restrictive definition ?
      //scalar before basis => doesn't work !
      //maybe because a base is convertible to a scalar...
      struct terminal
	: boost::proto::or_<basis
			    ,scalar
			    ,variable
			    >
      {};
      struct basis2blade
	: boost::proto::or_<
	boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 1> > >
			   ,types::blade_c<1, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 2> > >
			    ,types::blade_c<2, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 3> > >
			    ,types::blade_c<4, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 4> > >
			    ,types::blade_c<8, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 5> > >
			    ,types::blade_c<16, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 6> > >
			    ,types::blade_c<32, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 7> > >
			    ,types::blade_c<64, value_type>(boost::proto::_value) >
	,boost::proto::when<boost::proto::terminal<types::base<metric, value_type, base_symbols, boost::mpl::integral_c<size_t, 8> > >
			    ,types::blade_c<128, value_type>(boost::proto::_value) >
	>
      {};
      struct make_blade
	: boost::proto::or_<boost::proto::when<basis
					       ,basis2blade(boost::proto::_expr)
					       >
			    ,boost::proto::when<scalar
						,types::blade_c<0, value_type>(boost::proto::_value)
						>
			    ,variable
			    >
      {};
      struct plus
	: boost::proto::or_<boost::proto::when<boost::proto::plus< terminal, terminal >
					       ,add_blades(make_blade(boost::proto::_left)
							   ,make_blade(boost::proto::_right))
					       >
			    ,boost::proto::when<boost::proto::plus< terminal, multivector_grammar>
						,add_multivector_with_blade(multivector_grammar(boost::proto::_right)
									    ,make_blade(boost::proto::_left))
						>
			    ,boost::proto::when<boost::proto::plus< multivector_grammar, terminal>
						,add_multivector_with_blade(multivector_grammar(boost::proto::_left)
									    ,make_blade(boost::proto::_right))
						>
			    ,boost::proto::when<boost::proto::plus< multivector_grammar, multivector_grammar>
						,add_multivectors(multivector_grammar(boost::proto::_left)
								  ,multivector_grammar(boost::proto::_right))
						>
			    >
      {};
      struct multiplies
	: boost::proto::or_<boost::proto::when<boost::proto::multiplies< terminal, terminal >
					       ,operations::product_bases(make_blade(boost::proto::_left)
									  ,make_blade(boost::proto::_right)
									  ,metric()
									  ,value_type())
					       >
			    ,boost::proto::when<boost::proto::multiplies<terminal, multivector_grammar>
						,operations::product_multivectors(make_blade(boost::proto::_left)
										  ,multivector_grammar(boost::proto::_right)
										  ,metric()
										  ,value_type())
						>
			    ,boost::proto::when<boost::proto::multiplies<multivector_grammar, terminal>
						,operations::product_multivectors(make_blade(boost::proto::_right)
										  ,multivector_grammar(boost::proto::_left)
										  ,metric()
										  ,value_type())
						>
			    ,boost::proto::when<boost::proto::multiplies<multivector_grammar, multivector_grammar>
						,operations::product_multivectors(multivector_grammar(boost::proto::_left)
										  ,multivector_grammar(boost::proto::_right)
										  ,metric()
										  ,value_type())
						>
			    >
      {};
      struct multivector_grammar
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
