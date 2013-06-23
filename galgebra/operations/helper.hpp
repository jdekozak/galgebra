#if !(GALGEBRA_OPERATIONS_HELPER)
#define GALGEBRA_OPERATIONS_HELPER

#include <boost/proto/proto_fwd.hpp>

#include <boost/type_traits/remove_reference.hpp>

namespace galgebra {
  struct get_base_value
    : boost::proto::callable
  {
    template<typename Signature>
    struct result;

    template<typename This
	     ,typename Base>
    struct result<This(Base)> {
      typedef typename boost::remove_reference<Base>::type::value_type type;
    };

    template<typename Base>
    typename result< get_base_value(Base)>::type operator()(const Base& base) const {
      return base.value_;
    }
  };
}

#endif
