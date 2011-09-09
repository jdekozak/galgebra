#include <core.hpp>

#include <boost/mpl/less_equal.hpp>

namespace galgebra {
  struct _revise_contract : proto::transform<_revise_contract >
  {
    //general case, different vectors, not orthogonal, metric must be diagonal
    template<typename Expression, typename State, typename Data>
    struct impl : proto::transform_impl<Expression, State, Data>
    {
      typedef
      typename proto::result_of::make_expr<proto::tag::minus
					   ,typename proto::result_of::make_expr<proto::tag::multiplies
										 ,typename proto::result_of::make_expr<proto::tag::terminal
														       ,typename mpl::int_<2>::type
														       >::type
										 ,typename impl::data>::type
					   ,typename proto::result_of::make_expr<proto::tag::multiplies
										 ,typename impl::state
										 ,typename impl::expr>::type
					   >::type
      result_type;
      result_type operator ()(typename impl::expr_param expression
			      ,typename impl::state_param state
			      ,typename impl::data_param data
			      ) const
      {
	return proto::make_expr<proto::tag::minus>(proto::make_expr<proto::tag::multiplies>(mpl::int_<2>()
											    ,data)
						   ,proto::make_expr<proto::tag::multiplies>(state
											     ,expression)
						   );
      }
    };
    //1st specialization, different vectors, vectors are orthogonal
    template<typename Expression, typename State>
    struct impl<Expression, State, mpl::integral_c<int, 0> >
      : proto::transform_impl<Expression, State, mpl::integral_c<int, 0> >
    {
      typedef
      typename proto::result_of::make_expr<proto::tag::negate
					   ,typename proto::result_of::make_expr<proto::tag::multiplies
										 ,typename impl::state
										 ,typename impl::expr>::type
					   >::type
      result_type;
      result_type operator ()(typename impl::expr_param expression
			      ,typename impl::state_param state
			      ,typename impl::data_param data
			      ) const
      {
	return proto::make_expr<proto::tag::negate>(proto::make_expr<proto::tag::multiplies>(state, expression));
      }
    };
    //2nd specialization, same vectors, square must be a scalar (=> terminal)
    template<typename Expression, typename Data>
    struct impl<Expression, Expression, Data >
      : proto::transform_impl<Expression, Expression, Data >
    {
      typedef
      typename proto::result_of::make_expr<proto::tag::terminal, typename impl::data>::type
      result_type;
      result_type operator ()(typename impl::expr_param expression
			      ,typename impl::state_param state
			      ,typename impl::data_param data
			      ) const
      {
	return proto::make_expr<proto::tag::terminal>(data);
      }
    };
  };

  template<typename Metric>
  struct contract_revise
    : proto::or_<
    proto::when<proto::multiplies<vector,vector>
		,proto::if_<mpl::less_equal<proto::functional::value(proto::_right)
					    ,proto::functional::value(proto::_left)
					    >()
			    ,_revise_contract(proto::_left
					      ,proto::_right
					      ,g<Metric
						 ,proto::functional::value(proto::_left)
					         ,proto::functional::value(proto::_right)>()
					      )
			    >
		>
    ,proto::when<proto::multiplies<proto::multiplies<proto::_, vector>, vector>
		 ,proto::if_<mpl::less_equal<proto::functional::value(proto::_right)
					     ,proto::functional::value(proto::_right(proto::_left))
					     >()
			     ,proto::_make_multiplies(proto::_left(proto::_left)
						      ,_revise_contract(proto::_right(proto::_left)
									,proto::_right
									,g<Metric
									   ,proto::functional::value(proto::_right(proto::_left))
									   ,proto::functional::value(proto::_right)>()
						                        )
						      )
			     >
		 >
    ,proto::when<proto::multiplies<vector, proto::multiplies<vector, proto::_> >
		 ,proto::if_<mpl::less_equal<proto::functional::value(proto::_left(proto::_right))
					     ,proto::functional::value(proto::_left)
					     >()
			     ,proto::_make_multiplies(_revise_contract(proto::_left
								       ,proto::_left(proto::_right)
								       ,g<Metric
								          ,proto::functional::value(proto::_left)
								          ,proto::functional::value(proto::_left(proto::_right))>()
								       )
						      ,proto::_right(proto::_right)
						      )
			     >
		 >
   >
  {};
}
