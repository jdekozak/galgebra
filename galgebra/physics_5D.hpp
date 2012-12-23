#if !defined(GALGEBRA_PHYSICS_5D)
#define GALGEBRA_PHYSICS_5D

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/string.hpp>

namespace galgebra {
  namespace physics_5D {
    //metric is Clifford(1,4)
    typedef boost::mpl::vector_c<int, 1, 0, 0, 0, 0> row_0;
    typedef boost::mpl::vector_c<int, 0,-1, 0, 0, 0> row_1;
    typedef boost::mpl::vector_c<int, 0, 0,-1, 0, 0> row_2;
    typedef boost::mpl::vector_c<int, 0, 0, 0,-1, 0> row_3;
    typedef boost::mpl::vector_c<int, 0, 0, 0, 0,-1> row_4;

    typedef boost::mpl::vector<row_0
			       ,row_1
			       ,row_2
			       ,row_3
			       ,row_4
			       > metric;
    //base symbols : gamma_t, gamma_x, gamma_y, gamma_z, gamma_w
    typedef boost::mpl::vector<boost::mpl::string<'g','a','m','m','a','_','t'>
			       ,boost::mpl::string<'g','a','m','m','a','_','x'>
			       ,boost::mpl::string<'g','a','m','m','a','_','y'>
			       ,boost::mpl::string<'g','a','m','m','a','_','z'>
			       ,boost::mpl::string<'g','a','m','m','a','_','w'>
			       > base_symbols;
    //variables symbols : t, x, y, z, w
    typedef boost::mpl::vector<boost::mpl::string<'t'>
			       ,boost::mpl::string<'x'>
			       ,boost::mpl::string<'y'>
			       ,boost::mpl::string<'z'>
			       ,boost::mpl::string<'w'>
			       > variable_symbols;
    //scalar is reals
    typedef double value_type;
    template<typename VALUE_TYPE = value_type>
    struct null {
      static constexpr VALUE_TYPE value = 0.0;
    };
  }
}

#endif
