#if !defined(GALGEBRA_GRAMMAR)
#define GALGEBRA_GRAMMAR

#include <boost/proto/proto.hpp>
#include <boost/type_traits/is_same.hpp>

#include "./dimension.hpp"

#include "./operations/addition.hpp"
#include "./operations/geometric_product.hpp"
#include "./operations/helper.hpp"

#include "./types/base.hpp"
#include "./types/variable.hpp"
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

      //everything that can be promoted to value_type
      struct scalar
	: boost::proto::terminal< boost::proto::convertible_to< value_type > >
      {};
      //up to 8, not configurable, geometric algebras are cyclic modulo 8
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
      //up to 8, not configurable, geometric algebras are cyclic modulo 8
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
      //operands
      struct terminal
	: boost::proto::or_<basis
			    ,scalar
			    ,variable
			    >
      {};

      //switch cases
      struct multivector_grammar_cases
      {
	//default matches nothing
	template <typename Tag>
	struct case_
	  : boost::proto::not_<boost::proto::_>
	{};
      };
      //terminals
      template<>
      struct multivector_grammar_cases
      ::case_<boost::proto::tag::terminal>
        : terminal
      {};
      //-
      template<>
      struct multivector_grammar_cases
      ::case_<boost::proto::tag::negate>
      : boost::proto::negate<multivector_grammar>
      {};
      //*
      template<>
      struct multivector_grammar_cases
      ::case_<boost::proto::tag::multiplies>
      : boost::proto::multiplies<multivector_grammar, multivector_grammar >
      {};
      //+
      template<>
      struct multivector_grammar_cases
      ::case_<boost::proto::tag::plus>
      : boost::proto::plus<multivector_grammar, multivector_grammar >
      {};
      //-
      template<>
      struct multivector_grammar_cases
      ::case_<boost::proto::tag::minus>
      : boost::proto::minus<multivector_grammar, multivector_grammar >
      {};

      struct multivector_grammar
	: boost::proto::switch_<multivector_grammar_cases>
      {};

    };
  }
}

#endif
