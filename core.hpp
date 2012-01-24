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
    : mpl::int_<Index>
  {
    friend std::ostream &operator <<(std::ostream &p_output, x_<Index> ) {
      return (p_output << "x_" << Index);
    }
  };

  //vectors
  template<int Index>
  struct e_
    : mpl::int_<Index>
  {
    friend std::ostream &operator <<(std::ostream &p_output, e_<Index> ) {
      return (p_output << "e_" << Index);
    }
  };

  //proto terminal structures
  //proto scalar
  struct scalar
    : proto::terminal<proto::convertible_to<double> >
  {};
  //proto vectors
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
  //proto symbols
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

  //proto non terminal structures
  struct basis
    : proto::or_<
    vector
    ,proto::multiplies<basis, basis>
    >
  {};
  struct coefficient
    : proto::or_<
    scalar
    ,proto::multiplies<coefficient, coefficient>
    >
  {};
  struct weighted_basis
    : proto::or_<
    proto::multiplies<coefficient, basis>
    ,proto::multiplies<basis, coefficient>
    ,proto::multiplies<weighted_basis, weighted_basis>
    >
  {};

  //multivector expressions = linear combination of bases
  struct multivector
    : proto::or_<
    coefficient
    ,basis
    ,weighted_basis
    ,proto::plus<multivector, multivector>
    ,proto::minus<multivector, multivector>
    >
  {};

  template <typename Expression>
  bool is_multivector(const Expression& expression) {
    BOOST_MPL_ASSERT((proto::matches<Expression,multivector>));
    std::cout << "IS MULTIVECTOR" << std::endl;
    proto::display_expr(expression);
    return true;
  }
  template <typename Expression>
  bool is_not_multivector(const Expression& expression) {
    BOOST_MPL_ASSERT_NOT((proto::matches<Expression,multivector>));
    std::cout << "IS NOT MULTIVECTOR" << std::endl;
    proto::display_expr(expression);
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
