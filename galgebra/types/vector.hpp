#if !defined(GALGEBRA_TYPES_VECTOR)
#define GALGEBRA_TYPES_VECTOR

#include <boost/mpl/fold.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/push_back.hpp>

#include "../dimension.hpp"
#include "./blade.hpp"
#include "../utility/numeric.hpp"
#include "../types/multivector.hpp"

namespace galgebra {
  namespace types {
    template<typename Metric
	     ,typename ValueType>
    struct vector {
      typedef Metric metric;
      typedef ValueType value_type;
      typedef typename boost::mpl::fold<boost::mpl::range_c<size_t
							    ,0
							    ,dimension<metric>::value>
					,multivector<>
					,boost::mpl::push_back<boost::mpl::_1
							       ,blade<boost::mpl::lambda<numeric::power<boost::mpl::integral_c<size_t,2>
													,boost::mpl::_2
													>
											 >
								      ,value_type
								      >
							       >
					>::type type;
    };
  }
}

#endif
