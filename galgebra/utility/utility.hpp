#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>

#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/include/has_key.hpp>

#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/include/filter_if.hpp>

#include <boost/fusion/container/map/convert.hpp>
#include <boost/fusion/include/as_map.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/mpl/lambda.hpp>

#include <boost/bind.hpp>

namespace galgebra {
  struct assign {
    typedef void result_type;
    template<typename BLADE, typename MULTIVECTOR>
    void operator()(const BLADE& blade, MULTIVECTOR& multivector) const {
      boost::fusion::at_key<typename BLADE::first_type>(multivector) = blade.second;
    }
  };
  template <typename PAIR>
  struct get_first_type {
    typedef typename PAIR::first_type type;
  };
  struct add {
    typedef void result_type;
    template<typename BLADE, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    void operator()(BLADE& blade, const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
      blade.second = (boost::fusion::at_key<typename BLADE::first_type>(lhs)).second + (boost::fusion::at_key<typename BLADE::first_type>(rhs)).second;
    }
  };
  struct intersection {
    template <typename SIGNATURE>
    struct result;
    template <typename THIS, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    struct result<THIS(LHS_MULTIVECTOR, RHS_MULTIVECTOR)> {
      typedef typename boost::fusion::result_of::as_map<typename boost::fusion::result_of::filter_if<LHS_MULTIVECTOR 
												     ,boost::fusion::result_of::has_key<RHS_MULTIVECTOR
																	,boost::mpl::lambda<get_first_type<boost::mpl::_1>
																			    >
																	>
												     >::type
							>::type type;
    };
    template<typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    typename result<intersection(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type operator()(const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
      typename result<intersection(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type temporary;
      boost::fusion::for_each(temporary, boost::bind(add(), _1, lhs, rhs));
      return temporary;
    }
  };
}
