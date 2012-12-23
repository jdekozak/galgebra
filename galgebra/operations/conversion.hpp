#include <boost/proto/proto_fwd.hpp>

#include <boost/mpl/minus.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/int.hpp>

#include "../types/blade.hpp"

#include "../utility/numeric.hpp"

namespace galgebra {
  //conversion
  template<typename ValueType>
  struct _make_blade
    : boost::proto::callable
  {
    typedef ValueType value_type;
    template <typename SIGNATURE>
    struct result;
    //basis
    template <typename THIS, typename BASE>
    struct result<THIS(BASE)> {
      typedef types::blade_c<numeric::power<boost::mpl::integral_c<size_t,2>
					    ,typename boost::mpl::minus<typename boost::remove_reference<BASE>::type
									,boost::mpl::integral_c<size_t,1>
									>::type
					    >::value
			     ,value_type
			     > type;
    };
    template<typename BASE>
    typename result<_make_blade(BASE)>::type operator()(const BASE&) const {
      return typename result<_make_blade(BASE)>::type(1.0);
    }
    //const scalar
    template <typename THIS>
    struct result<THIS(const value_type&)> {
      typedef types::blade_c<0, value_type> type;
    };
    typename result<_make_blade(const value_type&)>::type operator()(const value_type& value) const {
      return typename result<_make_blade(const value_type&)>::type(value);
    }
    //scalar
    template <typename THIS>
    struct result<THIS(value_type)> {
      typedef types::blade_c<0, value_type> type;
    };
    typename result<_make_blade(value_type)>::type operator()(value_type& value) const {
      return typename result<_make_blade(value_type)>::type(value);
    }
  };
}
