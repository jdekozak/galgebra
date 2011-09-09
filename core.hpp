#ifndef __CORE_HPP__
#define __CORE_HPP__

#include <boost/proto/proto.hpp>

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/int.hpp>

//warning, limitation is up to 8 because of or_ limit in proto see BOOST_PROTO_MAX_LOGICAL_ARITY
#define GALGEBRA_MAXIMUM_DIMENSIONS BOOST_PROTO_MAX_LOGICAL_ARITY

namespace proto = boost::proto;
namespace mpl = boost::mpl;

namespace galgebra {

  //metric and dimension
  template <typename Metric>
  struct dimension
    : mpl::size<Metric>::type
  {};
  template<typename Metric, int I, int J>
  struct g_c
    : mpl::at_c<typename mpl::at_c<Metric, I>::type, J>::type
  {};
  template<typename Metric, typename I, typename J>
  struct g
    : mpl::at<typename mpl::at<Metric, I>::type, J>::type
  {};

  //symbols
  template<int Position>
  struct x_
    : mpl::int_<Position>
  {
    friend std::ostream &operator <<(std::ostream &p_output, x_<Position> ) {
      return (p_output << "x_" << Position);
    }
  };

  //vectors
  template<int Position>
  struct e_
    : mpl::int_<Position>
  {
    friend std::ostream &operator <<(std::ostream &p_output, e_<Position> ) {
      return (p_output << "e_" << Position);
    }
  };

  //primitive structures (scalar, vector, symbol)
  struct scalar
    : proto::terminal<proto::convertible_to<double> >
  {};
#define TERMINAL_VECTOR(z,N,data)		\
  proto::terminal<e_<N> >

  struct vector
    : proto::or_<
    BOOST_PP_ENUM(GALGEBRA_MAXIMUM_DIMENSIONS, TERMINAL_VECTOR, _)
    >
  {};
#define PREDEFINED_TERMINALS(z,N,data)		\
  proto::terminal<e_<N> >::type const e_##N = {};
  BOOST_PP_REPEAT(GALGEBRA_MAXIMUM_DIMENSIONS, PREDEFINED_TERMINALS, _)

#define TERMINAL_SYMBOL(z,N,data)		\
  proto::terminal<x_<N> >

  struct symbol
    : proto::or_<
    BOOST_PP_ENUM(GALGEBRA_MAXIMUM_DIMENSIONS, TERMINAL_SYMBOL, _)
    >
  {};
#define PREDEFINED_SYMBOLS(z,N,data)		\
  proto::terminal<x_<N> >::type const x_##N = {};
  BOOST_PP_REPEAT(GALGEBRA_MAXIMUM_DIMENSIONS, PREDEFINED_SYMBOLS, _)

  //less primitive structures
  struct basis
    : proto::or_<
    vector
    ,proto::function<proto::_, proto::vararg<vector> >
    >
  {};
  struct function
    : proto::or_<
    symbol
    ,proto::function<proto::_, proto::vararg<symbol> >
    >
  {};

  //geometric algebra simplified expressions are following this grammar after simplification and expansion
  struct gexpression
    : proto::or_<
    scalar
    ,basis
    ,proto::multiplies<scalar, basis>
    ,proto::when<proto::multiplies<basis, scalar>
		 ,proto::_make_multiplies(proto::_right, proto::_left) >
    ,proto::plus<gexpression, gexpression>
    ,proto::minus<gexpression, gexpression>
    >
  {};

  template <typename Expression>
  bool check_grammar(const Expression& expression) {
    BOOST_MPL_ASSERT((proto::matches<Expression,gexpression>));
    return true;
  }


  //really needed ??
  template<typename T>
  struct is_symbol
    : mpl::false_
  {};
#define IS_SYMBOL(z,N,data)			\
  template<>					\
  struct is_symbol<x_<N> >			\
    : mpl::true_				\
  {};
  BOOST_PP_REPEAT(GALGEBRA_MAXIMUM_DIMENSIONS, IS_SYMBOL, _);

  template<typename T>
  struct is_vector
    : public mpl::false_
  {};
#define IS_VECTOR(z,N,data)			\
  template<>					\
  struct is_vector<e_<N> >			\
    : mpl::true_				\
  {};
  BOOST_PP_REPEAT(GALGEBRA_MAXIMUM_DIMENSIONS, IS_VECTOR, _);

}

#endif //__CORE_HPP__
