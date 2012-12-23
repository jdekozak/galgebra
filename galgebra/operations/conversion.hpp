#if !defined(GALGEBRA_OPERATIONS_CONVERSION)
#define GALGEBRA_OPERATIONS_CONVERSION

#include <boost/proto/proto_fwd.hpp>

#include <boost/mpl/minus.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/int.hpp>

#include "../types/blade.hpp"

#include "../utility/numeric.hpp"

namespace galgebra {

  struct _make_blade
    : boost::proto::callable
  {
    template <typename Signature>
    struct result;
    //basis
    template <typename This
	      ,typename Base
	      ,typename ValueType>
    struct result<This(Base
		       ,ValueType)> {
      typedef typename boost::remove_reference<Base>::type no_ref;
      typedef types::blade_c<numeric::power<boost::mpl::integral_c<size_t,2>
					    ,typename boost::mpl::minus<typename no_ref::type
									,boost::mpl::integral_c<size_t,1>
									>::type
					    >::value
			     ,ValueType
			     > type;
    };
    template<typename Base
	     ,typename ValueType>
    typename result<_make_blade(Base
				,ValueType)>::type operator()(const Base&
							      ,const ValueType&) const {
      return typename result<_make_blade(Base, ValueType)>::type(1.0);
    }
  };
}

#endif
