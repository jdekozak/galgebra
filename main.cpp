#include <iostream>

#include <galgebra.hpp>

namespace galgebra {
  struct SomeAction : proto::callable {
     typedef void result_type;
     template<typename Sequence>
     void operator()(Sequence const &range) {
       fusion::for_each(range, display_value());
     }
   };
}

#define theContractTest galgebra::e_1*galgebra::e_1
#define theReviseTest galgebra::e_2*galgebra::e_1
#define theNothingTest galgebra::e_1*galgebra::e_2
#define theRecursiveTest galgebra::e_1*galgebra::e_2*galgebra::e_1
#define theRecursiveNothingTest galgebra::e_1*galgebra::e_2*galgebra::e_3
#define theExpandable (galgebra::e_2+galgebra::e_1)*(galgebra::e_1+galgebra::e_2)

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

int main(int argc, char* argv[]) {
  galgebra::display_metric<metric>()();
  std::cout << "********************************" << std::endl;
  
  std::cout << "dimension G(1,4) = " << galgebra::dimension<metric>::value << std::endl;
  std::cout << "g[0,0]= " << galgebra::g_c<metric,0,0>::value << std::endl;
  std::cout << "g[4,4]="  << galgebra::g_c<metric,4,4>::value << std::endl;
  std::cout << "g[4,4]="  << galgebra::g  <metric,galgebra::e_<4>,galgebra::e_<4> >::value << std::endl;

  std::cout << "********************************" << std::endl;
  proto::display_expr(theExpandable);
  proto::display_expr(cas::distributive()(theExpandable));
  std::cout << "********************************" << std::endl;

  proto::display_expr(theContractTest);
  proto::display_expr(galgebra::contract_revise<metric>()(theContractTest));
  std::cout << "********************************" << std::endl;
  proto::display_expr(theReviseTest);
  proto::display_expr(galgebra::contract_revise<metric>()(theReviseTest));
  std::cout << "********************************" << std::endl;
  proto::display_expr(theNothingTest);
  proto::display_expr(galgebra::contract_revise<metric>()(theNothingTest));
  std::cout << "********************************" << std::endl;
  proto::display_expr(theRecursiveTest);
  proto::display_expr(galgebra::contract_revise<metric>()(theRecursiveTest));
  std::cout << "********************************" << std::endl;
  proto::display_expr(theRecursiveNothingTest);
  proto::display_expr(galgebra::contract_revise<metric>()(theRecursiveNothingTest));
  std::cout << "********************************" << std::endl;

  proto::display_expr(galgebra::e_3*galgebra::e_2);
  proto::display_expr(galgebra::contract_revise<metric>()(galgebra::e_3*galgebra::e_2));
  std::cout << "********************************" << std::endl;
  proto::display_expr(galgebra::e_3*galgebra::e_2*galgebra::e_1);
  proto::display_expr(galgebra::contract_revise<metric>()(galgebra::e_3*galgebra::e_2*galgebra::e_1));
  std::cout << "********************************" << std::endl;
  proto::display_expr(galgebra::e_3*(galgebra::e_2*galgebra::e_1));
  proto::display_expr(galgebra::contract_revise<metric>()(galgebra::e_3*(galgebra::e_2*galgebra::e_1)));
  std::cout << "********************************" << std::endl;
  /*
#define theTest       galgebra::e_2*-galgebra::e_3*(-galgebra::e_1*-galgebra::e_2+(-(galgebra::e_3*galgebra::e_4)))
  proto::display_expr(theTest);
  proto::display_expr(cas::prune_negate()(theTest));
  std::cout << "********************************" << std::endl;
  proto::display_expr(-(-galgebra::e_2*galgebra::e_3));
  proto::display_expr(cas::prune_negate()(-(-galgebra::e_2*galgebra::e_3)));
  std::cout << "********************************" << std::endl;
  proto::display_expr(-(-galgebra::e_1*galgebra::e_2*galgebra::e_3));
  proto::display_expr(cas::prune_negate() (-(-galgebra::e_1*galgebra::e_2*galgebra::e_3)));
  */
  return 0;
}
