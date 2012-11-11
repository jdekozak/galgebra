/*
//to store the multivectors as a fusion::map, needs 2^n as maximum
#define BOOST_MPL_LIMIT_METAFUNCTION_ARITY 32

#define BOOST_PROTO_MAX_ARITY 32
#define BOOST_PROTO_MAX_FUNCTION_CALL_ARITY 32
#define BOOST_PROTO_MAX_LOGICAL_ARITY 32

#define FUSION_MAX_MAP_SIZE 32
*/
#include <boost/mpl/size_t.hpp>

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/string.hpp>

#include <boost/mpl/times.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/proto/proto.hpp>

#include <boost/fusion/container/vector.hpp>

#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/support/pair.hpp>

#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/container/map/map_fwd.hpp>
#include <boost/fusion/include/map_fwd.hpp>

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/include/insert.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/include/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/join.hpp>
#include <boost/fusion/include/join.hpp>

#include <boost/fusion/mpl.hpp>

#include <boost/bind.hpp>

#include <string>
#include <iomanip>

namespace mpl = boost::mpl;
namespace proto = boost::proto;
namespace fusion = boost::fusion;

namespace galgebra {
  //numeric
  // Value^Exponent = power(Value, Exponent)
  template <typename VALUE, typename EXPONENT>
  struct power : mpl::times< VALUE
			    ,power<VALUE
				   ,typename mpl::minus<EXPONENT
							,mpl::integral_c<size_t,1>
							>::type
				   >
			     >
  {};
  // specialization for 0
  template <typename VALUE>
  struct power<VALUE, mpl::integral_c<size_t,0> > : mpl::integral_c<size_t,1>
  {};

  template <typename VALUE>
  struct power_of_2
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 1> > : mpl::integral_c<size_t, 0>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 2> > : mpl::integral_c<size_t, 1>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 4> > : mpl::integral_c<size_t, 2>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 8> > : mpl::integral_c<size_t, 3>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 16> > : mpl::integral_c<size_t, 4>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 32> > : mpl::integral_c<size_t, 5>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 64> > : mpl::integral_c<size_t, 6>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 128> > : mpl::integral_c<size_t, 7>
  {};
  template <>
  struct power_of_2<mpl::integral_c<size_t, 256> > : mpl::integral_c<size_t, 8>
  {};
  template <std::size_t VALUE>
  struct power_of_2_c : power_of_2<mpl::integral_c<size_t, VALUE> >
  {};

  //default
  //default metric is Cl(1,4)
  typedef mpl::vector_c<int, 1, 0, 0, 0, 0> row_0;
  typedef mpl::vector_c<int, 0,-1, 0, 0, 0> row_1;
  typedef mpl::vector_c<int, 0, 0,-1, 0, 0> row_2;
  typedef mpl::vector_c<int, 0, 0, 0,-1, 0> row_3;
  typedef mpl::vector_c<int, 0, 0, 0, 0,-1> row_4;

  typedef mpl::vector< row_0
		      ,row_1
		      ,row_2
		      ,row_3
		      ,row_4
		      > default_metric;

  typedef mpl::vector< mpl::string<'g','a','m','m','a','_','t'>
		      ,mpl::string<'g','a','m','m','a','_','x'>
		      ,mpl::string<'g','a','m','m','a','_','y'>
		      ,mpl::string<'g','a','m','m','a','_','z'>
		      ,mpl::string<'g','a','m','m','a','_','w'>
		      > default_base_symbols;
  //default scalar is R
  typedef double default_value_type;
  template<typename VALUE_TYPE = default_value_type>
  struct null {
    static constexpr VALUE_TYPE value = 0.0;
  };
  //utility
  struct assign {
    typedef void result_type;
    template<typename BLADE, typename MULTIVECTOR>
    void operator()(const BLADE& blade, MULTIVECTOR& multivector) const {
      fusion::at_key<typename BLADE::first_type>(multivector) = blade.second;
    }
  };
  struct add {
    typedef void result_type;
    template<typename BLADE, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    void operator()(BLADE& blade, const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
      blade.second = fusion::at_key<typename BLADE::first_type>(lhs) + fusion::at_key<typename BLADE::first_type>(rhs);
    }
  };
  template <typename PAIR>
  struct get_first_type {
    typedef typename PAIR::first_type type;
  };
  struct intersection {
    template <typename SIGNATURE>
    struct result;
    template <typename THIS, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    struct result<THIS(LHS_MULTIVECTOR, RHS_MULTIVECTOR)> {
      typedef typename fusion::result_of::as_map<typename fusion::result_of::filter_if<LHS_MULTIVECTOR 
										       ,fusion::result_of::has_key<RHS_MULTIVECTOR
														   ,mpl::lambda<get_first_type<mpl::_1> > >
										       >::type >::type type;
    };
    template<typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    typename result<intersection(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type operator()(const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
      typename result<intersection(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type temporary;
      fusion::for_each(temporary, boost::bind(add(), _1, lhs, rhs));
      return temporary;
    }
  };

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
  struct display_metric {
    typedef void result_type;
    template<typename ALGEBRA>
    void operator()(const ALGEBRA& algebra) const {
      fusion::for_each(typename ALGEBRA::metric(), display_row());
    }
  };

  struct print_symbol {
    template<typename BLADE>
    void operator()(const BLADE& value) const {
      if(BLADE::first_type::value) {
	std::size_t position;
	bool first;
	for(first = false, position = 0; position < 8 && !first; ++position) {
	  if(BLADE::first_type::value & (1<<position)) {
	    std::cout << "e_" << (position+1);
	    first = true;
	  }
	}
	for(; position < 8; ++position) {
	  if(BLADE::first_type::value & (1<<position)) {
	    std::cout << "^e_" << (position+1);
	  }
	}
      } else {
	std::cout << "S";
      }
    }
  };

  struct print_blade {
    template<typename BLADE>
    void operator()(const BLADE& value) const {
      if(value.second != null<typename BLADE::second_type>::value) {
	std::cout << value.second;
	print_symbol()(value);
	std::cout << " ";
      }
    }
  };

  struct print_multivector {
    template<typename MULTIVECTOR>
    void operator()(const MULTIVECTOR& value) const {
      fusion::for_each(value, print_blade());
      std::cout << std::endl;
    }
  };

  //user interface
  template< typename METRIC = default_metric
	   ,typename BASE_SYMBOLS = default_base_symbols
	   ,typename VALUE_TYPE = default_value_type>
  struct algebra {
    typedef METRIC metric;
    typedef VALUE_TYPE value_type;
    typedef BASE_SYMBOLS base_symbols;
    //dimension
    struct dimension
      : mpl::size<metric>::type
    {};
    //metric
    template<typename I, typename J>
    struct g
      : mpl::at<typename mpl::at<metric, I>::type, J>::type
    {};
    template<std::size_t I, std::size_t J>
    struct g_c
      : g<mpl::integral_c<size_t,I>, mpl::integral_c<size_t,J> >
    {};
    //blade
    template <typename BITFIELD>
    using blade = fusion::pair<BITFIELD, value_type>;
    template <std::size_t BITFIELD>
    using blade_c = blade<mpl::integral_c<size_t,BITFIELD> >;
    //get_blade_c
    template <std::size_t BLADE, typename MULTIVECTOR>
    static value_type get_blade_c(const MULTIVECTOR& mv) {
      static_assert(fusion::result_of::has_key<MULTIVECTOR, mpl::integral_c<size_t,BLADE> >::value,"This blade is not in multivector");
      return fusion::at_key<mpl::integral_c<size_t,BLADE> >(mv);
    }
    template <std::size_t BLADE>
    static value_type get_blade_c(const blade_c<BLADE>& blade) {
      return blade.second;
    }
    //semantic actions for the expression templates
    //terminals
    struct _make_blade
      : proto::callable
    {
      template <typename SIGNATURE>
      struct result;
      //basis
      template <typename THIS, typename BASE>
      struct result<THIS(BASE)> {
	typedef blade_c<power<mpl::integral_c<size_t,2>
			      ,typename mpl::minus<typename boost::remove_reference<BASE>::type
						   ,mpl::integral_c<size_t,1> >::type>::value > type;
      };
      template<typename BASE>
      typename result<_make_blade(BASE)>::type operator()(const BASE&) const {
	return typename result<_make_blade(BASE)>::type(1.0);
      }
      //const scalar
      template <typename THIS>
      struct result<THIS(const value_type&)> {
	typedef blade_c<0> type;
      };
      typename result<_make_blade(const value_type&)>::type operator()(const value_type& value) const {
	return typename result<_make_blade(const value_type&)>::type(value);
      }
      //scalar
      template <typename THIS>
      struct result<THIS(value_type)> {
	typedef blade_c<0> type;
      };
      typename result<_make_blade(value_type)>::type operator()(value_type& value) const {
	return typename result<_make_blade(value_type)>::type(value);
      }
    };
    //plus
    struct add_bases
      : proto::callable
    {
      template <typename SIGNATURE>
      struct result;
      template <typename THIS, typename LHS_BLADE, typename RHS_BLADE>
      struct result<THIS(LHS_BLADE, RHS_BLADE)> {
	typedef fusion::map<LHS_BLADE, RHS_BLADE> type;
      };
      //base+base
      template <typename THIS, typename BLADE>
      struct result<THIS(BLADE, BLADE)> {
	typedef fusion::map<BLADE> type;
      };
      template<typename LHS_BLADE, typename RHS_BLADE>
      typename result< add_bases(LHS_BLADE, RHS_BLADE)>::type operator()(const LHS_BLADE& lhs, const RHS_BLADE& rhs) const {
	return typename result< add_bases(LHS_BLADE, RHS_BLADE)>::type(lhs, rhs);
      }
      //base+base
      template<typename BLADE>
      typename result< add_bases(BLADE, BLADE)>::type operator()(const BLADE& lhs, const BLADE& rhs) const {
	return typename result< add_bases(BLADE, BLADE)>::type(lhs.second+rhs.second);
      }      
    };
    //multiplies
    struct product_bases
      : proto::callable
    {
      template <typename SIGNATURE>
      struct result;
      template <typename THIS, typename LHS_BASE, typename RHS_BASE>
      struct result<THIS(LHS_BASE, RHS_BASE)> {
	typedef fusion::map<blade_c<0>, blade_c<(LHS_BASE::first_type::value ^ RHS_BASE::first_type::value)> > type;
      };
      //specialization 0 : squared base
      template <typename THIS, typename BASE>
      struct result<THIS(BASE, BASE)> {
	typedef fusion::map<blade_c<0> > type;
      };
      //specialization 1 : base*scalar
      template<typename THIS, typename LHS_BASE>
      struct result<THIS(LHS_BASE, blade_c<0>)> {
	typedef fusion::map<LHS_BASE> type;
      };
      //specialization 2 : scalar*base
      template<typename THIS, typename RHS_BASE>
      struct result<THIS(blade_c<0>, RHS_BASE)> {
	typedef fusion::map<RHS_BASE> type;
      };
      //specialization 3 : scalar*scalar
      template <typename THIS>
      struct result<THIS(blade_c<0>, blade_c<0>)> {
	typedef fusion::map<blade_c<0> > type;
      };

      template<typename LHS_BASE, typename RHS_BASE>
      typename result< product_bases(LHS_BASE, RHS_BASE)>::type operator()(const LHS_BASE& lhs, const RHS_BASE& rhs) const {
	value_type scalar_factor = lhs.second*rhs.second;
	value_type dot_value = null<value_type>::value;
	dot_value = g_c<power_of_2_c<LHS_BASE::first_type::value>::value, power_of_2_c<RHS_BASE::first_type::value>::value >::value;
	//reorder if j>i, e_j*e_i = 2*(e_i.e_j - e_i^e_j)
	//e_i*e_j = e_i.e_j + e_i^e_j
	if(LHS_BASE::first_type::value > RHS_BASE::first_type::value) {
	  dot_value += dot_value;
	  scalar_factor = (-scalar_factor);
	}
	return typename result< product_bases(LHS_BASE, RHS_BASE)>::type(scalar_factor*dot_value, scalar_factor);
      }
      //specialization 0 : squared base
      template<typename BASE>
      typename result< product_bases(BASE, BASE)>::type operator()(const BASE& lhs, const BASE& rhs) const {
	value_type scalar_factor = lhs.second*rhs.second;
	value_type dot_value = null<value_type>::value;
	dot_value = g_c<power_of_2_c<BASE::first_type::value>::value, power_of_2_c<BASE::first_type::value>::value >::value;
	return typename result< product_bases(BASE, BASE)>::type(scalar_factor*dot_value);
      }
      //specialization 1 : base*scalar
      template<typename LHS_BASE>
      typename result< product_bases(LHS_BASE, blade_c<0>)>::type operator()(const LHS_BASE& lhs, const blade_c<0>& rhs) const {
	return typename result< product_bases(LHS_BASE, blade_c<0>)>::type(lhs.second*rhs.second);
      }
      //specialization 2 : scalar*base
      template<typename RHS_BASE>
      typename result< product_bases(blade_c<0>, RHS_BASE)>::type operator()(const blade_c<0>& lhs, const RHS_BASE& rhs) const {
	return typename result< product_bases(blade_c<0>, RHS_BASE)>::type(lhs.second*rhs.second);
      }
      //specialization 3 : scalar*scalar
      typename result< product_bases(blade_c<0>, blade_c<0>)>::type operator()(const blade_c<0>& lhs, const blade_c<0>& rhs) const {
	return typename result< product_bases(blade_c<0>, blade_c<0>)>::type(lhs.second*rhs.second);
      }

    };
    template <typename ALREADY_EXISTS, typename DUMMY = mpl::void_>
    struct add_in_multivector;
    //plus
    struct add_blade
      : proto::callable
    {
      template <typename SIGNATURE>
      struct result;
      template <typename THIS, typename MULTIVECTOR, typename BLADE>
      struct result<THIS(MULTIVECTOR, BLADE)> {
	typedef typename mpl::if_<fusion::result_of::has_key<MULTIVECTOR, typename BLADE::first_type>
				  ,MULTIVECTOR
				  ,typename fusion::result_of::as_map<typename fusion::result_of::push_back<MULTIVECTOR, BLADE>::type >::type
				  >::type type;
      };
      template<typename MULTIVECTOR, typename BLADE >
      typename result< add_blade(MULTIVECTOR, BLADE)>::type operator()(const MULTIVECTOR& multivector, const BLADE& blade) const {
	return add_in_multivector<typename fusion::result_of::has_key<MULTIVECTOR, typename BLADE::first_type>::type>()(multivector, blade);
      }
    };

    template<typename DUMMY>
    struct add_in_multivector<mpl::true_, DUMMY> {
      template<typename MULTIVECTOR, typename BLADE >
      typename add_blade::template result< add_blade(MULTIVECTOR, BLADE)>::type operator()(const MULTIVECTOR& multivector, const BLADE& blade) const {
	MULTIVECTOR multivector_copy(multivector);
	fusion::at_key<typename BLADE::first_type>(multivector_copy) += blade.second;
	return multivector_copy;
      }
    };
    template<typename DUMMY>
    struct add_in_multivector<mpl::false_, DUMMY> {
      template<typename MULTIVECTOR, typename BLADE >
      typename add_blade::template result< add_blade(MULTIVECTOR, BLADE)>::type operator()(const MULTIVECTOR& multivector, const BLADE& blade) const {
	return fusion::as_map(fusion::push_back(multivector, blade));
      }
    };

    //plus
    struct add_multivectors
      : proto::callable
    {
      template <typename SIGNATURE>
      struct result;
      template <typename THIS, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
      struct result<THIS(LHS_MULTIVECTOR, RHS_MULTIVECTOR)> : fusion::result_of::as_map<typename fusion::result_of::join<LHS_MULTIVECTOR, RHS_MULTIVECTOR>::type >
      {};
      template<typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
      typename result< add_multivectors(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type operator()(const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
	typename result< add_multivectors(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type temporary;
	temporary = fusion::as_map(fusion::join(lhs, rhs));
	fusion::for_each(intersection()(lhs,rhs), boost::bind(assign(), _1, boost::ref(temporary)));
	return temporary;
      }
    };
    //vector
    typedef typename fusion::result_of::as_map<typename mpl::fold<mpl::range_c< size_t
										,0
										,dimension::value>
								  ,mpl::vector<>
								  ,mpl::push_back<mpl::_1, blade<mpl::lambda< power<mpl::integral_c<size_t,2>, mpl::_2 > > > >
								  >::type
					       >::type vector;
    //proto
    template<typename BASE>
    struct base : BASE {
      static_assert(BASE::value <= dimension::value, "Base is not allowed with dimension.");
      friend std::ostream &operator<<(std::ostream &s, base) {
	//bases are indexed starting at 1,        base_symbols starts at 0 index
	return s << mpl::c_str<typename mpl::at_c<base_symbols, BASE::value - 1>::type >::value;
      }
    };
    template<std::size_t BASE>
    using base_c = base<mpl::integral_c<size_t, BASE> >;

    template <typename T>
    struct is_base:
      mpl::false_
    {};
    template <int BASE>
    struct is_base<base_c<BASE> > :
      mpl::true_
    {};
    template <typename BASE>
    struct is_base<base<BASE> > :
      mpl::true_
    {};
    template<typename T>
    struct is_scalar :
      mpl::false_
    {};

    //multivector
    struct multivector;
    struct scalar : proto::terminal< proto::convertible_to< value_type > >
    {};
    struct basis : proto::and_< proto::terminal<proto::_>
			       ,proto::if_<is_base<proto::_value>() >
				>
    {};
    //basis is before scalar as it is more restrictive definition ?
    //scalar before basis => doesn't work !
    //maybe because a base is convertible to a scalar...
    struct terminal
      : proto::or_< basis
		   ,scalar
		    >
    {};
    struct make_blade
      : proto::or_< proto::when< basis
				 ,_make_blade(proto::_value)
				 >
		    ,proto::when< scalar
				  ,_make_blade(proto::_value)
				  >
		    >
    {};
    struct plus
      : proto::or_< proto::when<proto::plus< terminal, terminal >
				,add_bases(make_blade(proto::_left), make_blade(proto::_right))
				>
		   ,proto::when<proto::plus< terminal, multivector>
				,add_blade(multivector(proto::_right), make_blade(proto::_left))
				>
		   ,proto::when<proto::plus< multivector, terminal>
				,add_blade(multivector(proto::_left), make_blade(proto::_right))
				>
		   ,proto::when<proto::plus< multivector, multivector>
				,add_multivectors(multivector(proto::_left), multivector(proto::_right))
				>
		   >
    {};
    struct multiplies
      : proto::or_<proto::when<proto::multiplies< terminal, terminal >
			       ,product_bases(make_blade(proto::_left), make_blade(proto::_right))
			       >
		   ,proto::when<proto::multiplies<terminal, multivector>
				,product_bases(make_blade(proto::_left), multivector(proto::_right))
			       >
		   ,proto::when<proto::multiplies<multivector, terminal>
				,product_bases(multivector(proto::_left), make_blade(proto::_right))
			       >
		   ,proto::when<proto::multiplies<multivector, multivector>
				,product_bases(multivector(proto::_left),multivector(proto::_right))
				>
		   >
    {};
    struct multivector
      : proto::or_<proto::when<terminal
			       ,make_blade(proto::_value)
			       >
		   ,proto::when<multiplies
				,multiplies(proto::_expr)
				>
		   ,proto::when<plus
				,plus(proto::_expr)
				>
		   >
    {};

  };


}
