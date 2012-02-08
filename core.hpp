#ifndef __CORE_HPP__
#define __CORE_HPP__

#include <iostream>
#include <iomanip>

#include <boost/proto/proto.hpp>

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/less_equal.hpp>

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/as_vector.hpp>

//warning, limitation is up to 8 because of or_ limit in proto see BOOST_PROTO_MAX_LOGICAL_ARITY
#define GALGEBRA_MAXIMUM_DIMENSIONS BOOST_PROTO_MAX_LOGICAL_ARITY

namespace proto = boost::proto;
namespace mpl = boost::mpl;
namespace fusion = boost::fusion;

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
  //display
  struct display_value {
     typedef void result_type;
     template<typename Item>
     void operator()(Item i) const {
       std::cout << std::setiosflags(std::ios::right) << std::setw(3) << i;
     }
   };
  struct display_row {
    typedef void result_type;
    template<typename Row>
    void operator()(Row row) const {
      fusion::for_each(row, display_value());
      std::cout << std::endl;
    }
  };
  template<typename Metric>
  struct display_metric {
    typedef void result_type;
    void operator()() const {
      fusion::for_each(Metric(), display_row());
    }
  };
  //symbols
  template<int Index>
  struct x_
  {
    static const int value = Index;
    friend std::ostream &operator <<(std::ostream &p_output, x_<Index> ) {
      return (p_output << "x_" << Index);
    }
  };
  //vectors
  template<int Index>
  struct e_
  {
    static const int value = Index;
    friend std::ostream &operator <<(std::ostream &p_output, e_<Index> ) {
      return (p_output << "e_" << Index);
    }
  };
  template<typename T1, typename T2>
  struct greater
    : mpl::greater<mpl::int_<T1::value>, mpl::int_<T2::value> >
  {};
  template<typename T1, typename T2>
  struct less_equal
    : mpl::less_equal<mpl::int_<T1::value>, mpl::int_<T2::value> >
  {};
  //proto terminal structures
  //proto scalar
  struct scalar_terminal
    : proto::terminal<proto::convertible_to<double> >
  {};
  //proto vectors
#define TERMINAL_VECTOR(z,N,data)		\
  proto::terminal<e_<N> >
  struct vector_terminal
    : proto::or_<
    BOOST_PP_ENUM(GALGEBRA_MAXIMUM_DIMENSIONS, TERMINAL_VECTOR, _)
    >
  {};
  //proto symbols
#define TERMINAL_SYMBOL(z,N,data)		\
  proto::terminal<x_<N> >
  struct symbol_terminal
    : proto::or_<
    BOOST_PP_ENUM(GALGEBRA_MAXIMUM_DIMENSIONS, TERMINAL_SYMBOL, _)
    >
  {};

  //geometric algebra grammar
  struct gterminal
    : proto::or_<
    scalar_terminal
    ,vector_terminal
    ,symbol_terminal
    >
  {};
  struct gexpression_grammar
    : proto::or_<
    gterminal
    ,proto::multiplies<gexpression_grammar, gexpression_grammar>
    ,proto::divides<gexpression_grammar, gexpression_grammar>
    ,proto::plus<gexpression_grammar, gexpression_grammar>
    ,proto::minus<gexpression_grammar, gexpression_grammar>
    ,proto::negate<gexpression_grammar>
    >
  {};

  //gexpression wrapper forward declaration
  template<typename Expression>
  struct gexpression;
  //gexpression domain
  struct gexpression_domain
    : proto::domain< proto::pod_generator<gexpression>, gexpression_grammar>
  {};
  //gexpression wrapper
  template<typename Expression>
  struct gexpression
  {
    BOOST_PROTO_EXTENDS(Expression, gexpression<Expression>, gexpression_domain)
  };
#define PREDEFINED_TERMINALS(z,N,data)		\
  gexpression<proto::terminal<e_<N> >::type> const e_##N = {{{}}};
  BOOST_PP_REPEAT(GALGEBRA_MAXIMUM_DIMENSIONS, PREDEFINED_TERMINALS, _)
#define PREDEFINED_SYMBOLS(z,N,data)		\
  gexpression<proto::terminal<x_<N> >::type> const x_##N = {{{}}};
  BOOST_PP_REPEAT(GALGEBRA_MAXIMUM_DIMENSIONS, PREDEFINED_SYMBOLS, _)

  template <typename Expression>
  bool is_gexpression(const Expression& expression) {
    BOOST_MPL_ASSERT((proto::matches<Expression,gexpression_grammar>));
    std::cout << "IS GEXPRESSION" << std::endl;
    proto::display_expr(expression);
    return true;
  }
  template <typename Expression>
  bool is_not_gexpression(const Expression& expression) {
    BOOST_MPL_ASSERT_NOT((proto::matches<Expression,gexpression_grammar>));
    std::cout << "IS NOT GEXPRESSION" << std::endl;
    proto::display_expr(expression);
    return true;
  }
}

#endif //__CORE_HPP__
