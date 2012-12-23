#if !defined(GALGEBRA_OPERATIONS_ADDITION)
#define GALGEBRA_OPERATIONS_ADDITION

#include <boost/bind.hpp>

#include <boost/proto/proto_fwd.hpp>

#include <boost/fusion/container/map/convert.hpp>
#include <boost/fusion/include/as_map.hpp>

#include <boost/fusion/algorithm/transformation/join.hpp>
#include <boost/fusion/include/join.hpp>

#include "../types/multivector.hpp"
#include "../utility/utility.hpp"

namespace galgebra {
  struct add_blades
    : boost::proto::callable
  {
    template <typename SIGNATURE>
    struct result;
    template <typename THIS, typename LHS_BLADE, typename RHS_BLADE>
    struct result<THIS(LHS_BLADE, RHS_BLADE)> {
      typedef types::multivector<LHS_BLADE, RHS_BLADE> type;
    };
    template <typename THIS, typename BLADE>
    struct result<THIS(BLADE, BLADE)> {
      typedef types::multivector<BLADE> type;
    };
    template<typename LHS_BLADE, typename RHS_BLADE>
    typename result< add_blades(LHS_BLADE, RHS_BLADE)>::type operator()(const LHS_BLADE& lhs, const RHS_BLADE& rhs) const {
      return typename result< add_blades(LHS_BLADE, RHS_BLADE)>::type(lhs, rhs);
    }
    //base+base
    template<typename BLADE>
    typename result< add_blades(BLADE, BLADE)>::type operator()(const BLADE& lhs, const BLADE& rhs) const {
      return typename result< add_blades(BLADE, BLADE)>::type(lhs.second+rhs.second);
    }      
  };
  template <typename ALREADY_EXISTS, typename DUMMY = boost::mpl::void_>
  struct add_in_multivector;
  //plus
  struct add_multivector_with_blade
    : boost::proto::callable
  {
    template <typename SIGNATURE>
    struct result;
    template <typename THIS, typename MULTIVECTOR, typename BLADE>
    struct result<THIS(MULTIVECTOR, BLADE)> {
      typedef typename boost::mpl::if_<boost::fusion::result_of::has_key<MULTIVECTOR, typename BLADE::first_type>
				       ,MULTIVECTOR
				       ,typename boost::fusion::result_of::as_map<typename boost::fusion::result_of::push_back<MULTIVECTOR, BLADE>::type >::type
				       >::type type;
    };
    template<typename MULTIVECTOR, typename BLADE >
    typename result< add_multivector_with_blade(MULTIVECTOR, BLADE)>::type operator()(const MULTIVECTOR& multivector, const BLADE& blade) const {
      return add_in_multivector<typename boost::fusion::result_of::has_key<MULTIVECTOR, typename BLADE::first_type>::type>()(multivector, blade);
    }
  };

  template<typename DUMMY>
  struct add_in_multivector<boost::mpl::true_, DUMMY> {
    template<typename MULTIVECTOR, typename BLADE >
    typename add_multivector_with_blade::template result< add_multivector_with_blade(MULTIVECTOR, BLADE)>::type operator()(const MULTIVECTOR& multivector, const BLADE& blade) const {
      MULTIVECTOR multivector_copy(multivector);
      boost::fusion::at_key<typename BLADE::first_type>(multivector_copy) += blade.second;
      return multivector_copy;
    }
  };
  template<typename DUMMY>
  struct add_in_multivector<boost::mpl::false_, DUMMY> {
    template<typename MULTIVECTOR, typename BLADE >
    typename add_multivector_with_blade::template result< add_multivector_with_blade(MULTIVECTOR, BLADE)>::type operator()(const MULTIVECTOR& multivector, const BLADE& blade) const {
      return boost::fusion::as_map(boost::fusion::push_back(multivector, blade));
    }
  };

  struct add_multivectors
    : boost::proto::callable
  {
    template <typename SIGNATURE>
    struct result;
    template <typename THIS, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    struct result<THIS(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>
      : boost::fusion::result_of::as_map<typename boost::fusion::result_of::join<LHS_MULTIVECTOR, RHS_MULTIVECTOR>::type >
    {};
    template<typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
    typename result< add_multivectors(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type operator()(const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
      typename result< add_multivectors(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type temporary;
      temporary = boost::fusion::as_map(boost::fusion::join(lhs, rhs));
      boost::fusion::for_each(intersection()(lhs,rhs), boost::bind(assign(), _1, boost::ref(temporary)));
      return temporary;
    }
  };
}

#endif
