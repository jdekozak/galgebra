#include <boost/proto/proto.hpp>

#include <boost/mpl/modulus.hpp>

namespace proto = boost::proto;
namespace mpl = boost::mpl;

namespace cas {
  // unary_plus
  struct prune_unary_plus
  : proto::or_<
    proto::when<proto::unary_plus<prune_unary_plus>
		,prune_unary_plus(proto::_child)
		>
    ,proto::terminal<proto::_>
    ,proto::nary_expr<proto::_, proto::vararg<prune_unary_plus> >
    >
  {};
  // negate
  struct erase_negate
    : proto::or_<
    proto::terminal<proto::_>
    ,proto::when<proto::negate<erase_negate>
		,erase_negate(proto::_child)
		>
    ,proto::multiplies<erase_negate, erase_negate>
    >
  {};
  struct count_negate
    : proto::or_<
    proto::when<proto::terminal<proto::_>
		 ,proto::_state>
    ,proto::when<proto::negate<count_negate>
		 ,count_negate(proto::_value
			       ,mpl::next<proto::_state>())
		>
    ,proto::when<proto::multiplies<count_negate, count_negate>
		 ,count_negate(proto::_left
			      ,count_negate(proto::_right, proto::_state))
		 >
    >
  {};
  struct prune_negate
    : proto::or_<
    proto::when<erase_negate
		,proto::if_<mpl::modulus<count_negate(proto::_,mpl::int_<0>())
					 ,mpl::int_<2> >()
			    ,proto::_make_negate(erase_negate(proto::_))
			    ,erase_negate(proto::_)
			    >
		>
    ,proto::plus<prune_negate, prune_negate>
    >
  {};
  //distributive law 
  struct distributive
    : proto::or_<
    proto::when<
      //left
      proto::multiplies< proto::_, proto::plus< proto::_, proto::_ > >
      ,distributive( proto::_make_plus(
				       proto::_make_multiplies(
							       proto::_left,
							       proto::_left( proto::_right )
							       ),
				       proto::_make_multiplies(
							       proto::_left,
							       proto::_right( proto::_right )
							       )
				       )
		     )
      >
    ,proto::when<
      //right
       proto::multiplies< proto::plus< proto::_, proto::_ >, proto::_ >
       ,distributive( proto::_make_plus(
					proto::_make_multiplies(
								proto::_left( proto::_left ),
								proto::_right
								),
					proto::_make_multiplies(
								proto::_right( proto::_left ),
								proto::_right
								)
					)
		      )
       >
    ,proto::nary_expr<proto::_, proto::vararg<distributive> >
    >
  {};
}
