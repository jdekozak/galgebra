#if !defined(GALGEBRA_EXPRESSION)
#define GALGEBRA_EXPRESSION

#include "grammar.hpp"

namespace galgebra {
  namespace expression_templates {
    template<typename Metric
	     ,typename ValueType
	     ,typename BaseSymbols
	     ,typename VariableSymbols
	     >
    struct expression {
      typedef Metric metric;
      typedef ValueType value_type;
      typedef BaseSymbols base_symbols;
      typedef VariableSymbols variable_symbols;

      template<typename Expression>
      struct multivector_expression;

      struct multivector_domain
	: boost::proto::domain<boost::proto::generator<multivector_expression>
			       , grammar<metric, value_type, base_symbols, variable_symbols>::multivector_grammar
			       >
      {};

      template< typename Expression >
      struct multivector_expression
	: boost::proto::extends< Expression, multivector_expression< Expression >, multivector_domain >
      {
	typedef boost::proto::extends< Expression, multivector_expression< Expression >, multivector_domain > super;

	multivector_expression(const Expression& geometric_algebra_expression = Expression())
	  : super(geometric_algebra_expression)
	{}

	BOOST_PROTO_EXTENDS_USING_ASSIGN(multivector_expression)

	typedef types::multivector result_type;

	template <typename T>
	void operator()(const T& value) const
	{
	  cout << value << endl;
	}
 
	template <typename U, typename... T>
	void operator()(const U& head, const T&... tail) const
	{
	  cout << head;
	  this->operator()(tail...);
	}

	result_type operator()() const {
	  return types::multivector();
	}

      };
    };
  }
}

#endif
