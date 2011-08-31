#include <vector>
#include <iostream>

#include <boost/proto/proto.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>

#include <boost/mpl/size.hpp>

#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/negate.hpp>

#include <boost/fusion/include/vector.hpp>

using namespace boost;

//library
namespace galgebra
{
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

  //vectors
  template<int Position>
  struct e_
    : mpl::int_<Position>
  {
    friend std::ostream &operator <<(std::ostream &p_output, e_<Position> ) {
      return (p_output << "e_" << Position);
    }
  };

  struct value
    : proto::when<proto::terminal<proto::_>
		  ,proto::_value
		  >
  {};

  //geomtric algebra over reals
  struct scalar
    : proto::terminal<proto::convertible_to<double> >
  {};

  struct vector
    : proto::or_<
    proto::terminal<e_<0> >
    ,proto::terminal<e_<1> >
    ,proto::terminal<e_<2> >
    ,proto::terminal<e_<3> >
    ,proto::terminal<e_<4> >
    ,proto::terminal<e_<5> >
    ,proto::terminal<e_<6> >
    ,proto::terminal<e_<7> >
    >
  {};
  proto::terminal<e_<0> >::type e_0 = {};
  proto::terminal<e_<1> >::type e_1 = {};
  proto::terminal<e_<2> >::type e_2 = {};
  proto::terminal<e_<3> >::type e_3 = {};
  proto::terminal<e_<4> >::type e_4 = {};
  proto::terminal<e_<5> >::type e_5 = {};
  proto::terminal<e_<6> >::type e_6 = {};
  proto::terminal<e_<7> >::type e_7 = {};

  struct distributive
    : proto::or_<
    proto::when<
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

  struct galgebra_grammar
    : proto::or_<
    scalar
    ,vector
    ,proto::multiplies<galgebra_grammar, galgebra_grammar>
    ,proto::plus<galgebra_grammar, galgebra_grammar>
    ,proto::minus<galgebra_grammar, galgebra_grammar>
    >
  {};

  template <typename Expression>
  bool check_grammar(const Expression& expression) {
    BOOST_MPL_ASSERT((proto::matches<Expression, galgebra_grammar>));
    return true;
  }

  template<typename Metric>
  struct contract
    : proto::if_<mpl::greater_equal<g<Metric,value(proto::_left),value(proto::_right)>
				    ,mpl::int_<0> >()
		 // g[I,I] >= 0
		 ,proto::_make_unary_plus(g<Metric,value(proto::_left),value(proto::_right)>())
		 // g[I,I] < 0
		 ,proto::_make_negate(mpl::negate<g<Metric,value(proto::_left),value(proto::_right)> >())
		 >
  {};

  template<typename Metric>
  struct revise
    : proto::if_<mpl::equal_to<g<Metric,value(proto::_left),value(proto::_right)>
			       ,mpl::int_<0> >()
		 // g[I,J]=0
		 ,proto::_make_negate(proto::_make_multiplies(proto::_right
							      ,proto::_left)
				      )
		 // g[I,J]!=0
		 ,proto::_make_minus(proto::_make_multiplies(mpl::int_<2>()
							     ,g<Metric,value(proto::_left),value(proto::_right)>())
				     ,proto::_make_multiplies(proto::_right
							      ,proto::_left)
				     )
		 >
  {};

  template<typename Metric>
  struct contract_revise
    : proto::when<proto::multiplies<vector, vector>
		  // e_<I> * e_<J>
		  ,proto::if_<mpl::less<value(proto::_right)
					,value(proto::_left)
					>()
			      // J < I
			      ,proto::call<revise<Metric> >()
			      // J >= I
			      ,proto::if_<mpl::equal_to<value(proto::_left)
							,value(proto::_right)
							>()
					  // I == J
					  ,proto::call<contract<Metric> >()
					  // J > I
					  ,proto::_expr
					  >
			      >
		  >
  {};

};

//metric
typedef mpl::vector_c<int, 1, 0, 0, 0, 0> row_0;
typedef mpl::vector_c<int, 0,-1, 0, 0, 0> row_1;
typedef mpl::vector_c<int, 0, 0,-1, 0, 0> row_2;
typedef mpl::vector_c<int, 0, 0, 0,-1, 0> row_3;
typedef mpl::vector_c<int, 0, 0, 0, 0,-1> row_4;

typedef mpl::vector<row_0
		    ,row_1
		    ,row_2
		    ,row_3
		    ,row_4
		    > metric;
//vectors
proto::terminal< galgebra::e_<0> >::type gamma_t = {};
proto::terminal< galgebra::e_<1> >::type gamma_x = {};
proto::terminal< galgebra::e_<2> >::type gamma_y = {};
proto::terminal< galgebra::e_<3> >::type gamma_z = {};
proto::terminal< galgebra::e_<4> >::type gamma_w = {};

#define theTest ((gamma_x*gamma_x*gamma_w))
#define theTestVector ((gamma_x*gamma_t*gamma_w+gamma_z*gamma_y))
#define theRightDistributionTest ((gamma_x+gamma_t)*gamma_w)
#define theLeftDistributionTest (gamma_w*(gamma_x+gamma_t))
#define theRevisionXY (gamma_x*gamma_y)
#define theRevisionYX (gamma_y*gamma_x)
#define theContraction (gamma_z*gamma_z)
#define theDistribution ((gamma_x+gamma_t)*(gamma_w*gamma_x))

int main(int argc, char* argv[])
{

  std::cout << "dimension G(1,4) = " << galgebra::dimension<metric>::value << std::endl;
  std::cout << "g[0,0]= " << galgebra::g_c<metric,0,0>::value << std::endl;
  std::cout << "g[4,4]="  << galgebra::g_c<metric,4,4>::value << std::endl;
  std::cout << "g[4,4]="  << galgebra::g  <metric,galgebra::e_<4>,galgebra::e_<4> >::value << std::endl;

  proto::display_expr(galgebra::contract_revise<metric>()theRevisionXY);

  std::cout << std::endl;

  proto::display_expr(galgebra::contract_revise<metric>()theRevisionYX);

  std::cout << std::endl;

  proto::display_expr(galgebra::contract_revise<metric>()theContraction);

  std::cout << std::endl;

  proto::display_expr(theRightDistributionTest);
  proto::display_expr(galgebra::distributive()theRightDistributionTest);

  std::cout << std::endl;

  proto::display_expr(theLeftDistributionTest);
  proto::display_expr(galgebra::distributive()theLeftDistributionTest);

  std::cout << std::endl;

  proto::display_expr(theDistribution);
  proto::display_expr(galgebra::galgebra_grammar()theDistribution);

  std::cout << std::endl;

 return 0;
}
