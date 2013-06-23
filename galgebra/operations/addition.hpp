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
/*
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
*/
namespace galgebra {
  struct add_blades
    : boost::proto::callable
  {
    template <typename Signature>
    struct result;
    template <typename This
	      ,typename LhsBlade
	      ,typename RhsBlade>
    struct result<This(LhsBlade
		       ,RhsBlade)> {
      typedef types::multivector<LhsBlade
				 ,RhsBlade> type;
    };
    template <typename This
	      ,typename Blade>
    struct result<This(Blade
		       ,Blade)> {
      typedef types::multivector<Blade> type;
    };
    template<typename LhsBlade, typename RhsBlade>
    typename result< add_blades(LhsBlade
				,RhsBlade)>::type operator()(const LhsBlade& lhs
							     ,const RhsBlade& rhs) const {
      return typename result< add_blades(LhsBlade
					 ,RhsBlade)>::type(lhs, rhs);
    }
    //base+base
    template<typename Blade>
    typename result< add_blades(Blade
				,Blade)>::type operator()(const Blade& lhs
							  ,const Blade& rhs) const {
      return typename result< add_blades(Blade
					 ,Blade)>::type(lhs.second+rhs.second);
    }      
  };
  template <typename ALREADY_EXISTS, typename Dummy = boost::mpl::void_>
  struct add_in_multivector;
  //plus
  struct add_multivector_with_blade
    : boost::proto::callable
  {
    template <typename Signature>
    struct result;
    template <typename This
	      ,typename Multivector
	      ,typename Blade>
    struct result<This(Multivector
		       ,Blade)> {
      typedef typename boost::mpl::if_<boost::fusion::result_of::has_key<Multivector, typename Blade::first_type>
				       ,Multivector
				       ,typename boost::fusion::result_of::as_map<typename boost::fusion::result_of::push_back<Multivector, Blade>::type >::type
				       >::type type;
    };
    template<typename Multivector
	     ,typename Blade >
    typename result<add_multivector_with_blade(Multivector
					       ,Blade)>::type operator()(/*const*/ Multivector& multivector
									 ,const Blade& blade) const {
      return add_in_multivector<typename boost::fusion::result_of::has_key<Multivector, typename Blade::first_type>::type>()(multivector, blade);
    }
  };

  template<typename Dummy>
  struct add_in_multivector<boost::mpl::true_, Dummy> {
    template<typename Multivector
	     ,typename Blade >
    typename add_multivector_with_blade::template result<add_multivector_with_blade(Multivector
										    ,Blade)>::type operator()(/*const*/ Multivector& multivector
													      ,const Blade& blade) const {
      //Multivector multivector_copy(multivector);
      Blade blade_tmp = boost::fusion::at_key<typename Blade::first_type>(multivector);
      blade_tmp.second += blade.second;
      boost::fusion::at_key<typename Blade::first_type>(multivector) = blade_tmp;
      return multivector;
    }
  };
  template<typename Dummy>
  struct add_in_multivector<boost::mpl::false_, Dummy> {
    template<typename Multivector, typename Blade >
    typename add_multivector_with_blade::template result<add_multivector_with_blade(Multivector
										    ,Blade)>::type operator()(const Multivector& multivector
													      ,const Blade& blade) const {
      return boost::fusion::as_map(boost::fusion::push_back(multivector, blade));
    }
  };

  struct add_multivectors
    : boost::proto::callable
  {
    template <typename Signature>
    struct result;
    template <typename This
	      ,typename LhsMultivector
	      ,typename RhsMultivector>
    struct result<This(LhsMultivector
		       ,RhsMultivector)>
      : boost::fusion::result_of::as_map<typename boost::fusion::result_of::join<LhsMultivector, RhsMultivector>::type >
    {};
    template<typename LhsMultivector
	     ,typename RhsMultivector>
    typename result<add_multivectors(LhsMultivector
				     ,RhsMultivector)>::type operator()(const LhsMultivector& lhs
									,const RhsMultivector& rhs) const {
      typename result<add_multivectors(LhsMultivector
				       ,RhsMultivector)>::type temporary;
      temporary = boost::fusion::as_map(boost::fusion::join(lhs, rhs));
      boost::fusion::for_each(intersection()(lhs,rhs), boost::bind(assign(), _1, boost::ref(temporary)));
      return temporary;
    }
  };
}

#endif
