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

  struct product 
  { 
    friend std::ostream &operator <<(std::ostream &sout, product) 
    {
      return sout << "product";
    }
  };

  struct FoldToList
    : proto::or_<
    // Put all terminals at the head of the
    // list that we're building in the "state" parameter
    proto::when<
      proto::terminal<proto::_>
      , fusion::cons<proto::_value, proto::_state>(
						   proto::_value, proto::_state
						   )
      >
    // For multiplies operations, first fold the right
    // child to a list using the current state. Use
    // the result as the state parameter when folding
    // the left child to a list.
    , proto::when<
	proto::multiplies<FoldToList, FoldToList>
	, FoldToList(
		     proto::_left
		     ,FoldToList(proto::_right, proto::_state)
		     )
        >
    >
  {};

  template<typename Metric>
  struct contract
    : proto::if_<mpl::greater_equal<g<Metric,value(proto::_left),value(proto::_right)>
				    ,mpl::int_<0> >()
		 // g[I,I] > 0
		 ,proto::_make_unary_plus(g<Metric,value(proto::_left),value(proto::_right)>())
		 // g[I,I] <= 0
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
							      ,proto::_left))
		 >
  {};

  template<typename Metric>
  struct contract_revise
    : proto::when<proto::multiplies<proto::terminal<e_<proto::N> >
				    ,proto::terminal<e_<proto::N> >
				    >
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
typedef proto::terminal< galgebra::e_<0> >::type gamma_t;
typedef proto::terminal< galgebra::e_<1> >::type gamma_x;
typedef proto::terminal< galgebra::e_<2> >::type gamma_y;
typedef proto::terminal< galgebra::e_<3> >::type gamma_z;
typedef proto::terminal< galgebra::e_<4> >::type gamma_w;

#define theTest ((gamma_x()*gamma_x()*gamma_w()))
#define theTestVector ((gamma_x()*gamma_t()*gamma_w()+gamma_z()*gamma_y()))
#define theRevisionXY (gamma_x()*gamma_y())
#define theRevisionYX (gamma_y()*gamma_x())
#define theContraction (gamma_z()*gamma_z())

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

  proto::display_expr(proto::unpack_expr<galgebra::product>(galgebra::FoldToList()(theTestVector, fusion::nil())));

  std::cout << std::endl;
  /*
  proto::display_expr(proto::unpack_expr<contract_revise>(fusion::as_vector(proto::flatten(theTestVector)
									    )
							  )
		      );
  */
  return 0;
}
