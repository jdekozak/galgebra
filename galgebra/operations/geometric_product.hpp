#if !defined(GALGEBRA_OPERATIONS_GEOMETRIC_PRODUCT)
#define GALGEBRA_OPERATIONS_GEOMETRIC_PRODUCT

#include <boost/proto/proto_fwd.hpp>

#include "../types/blade.hpp"
#include "../types/multivector.hpp"

#include "../utility/numeric.hpp"

#include "../g.hpp"
#include "../physics_5D.hpp"

namespace galgebra {
  namespace operations {
    struct product_multivectors
      : boost::proto::callable
    {
      template <typename SIGNATURE>
      struct result;
      template <typename THIS, typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
      struct result<THIS(LHS_MULTIVECTOR, RHS_MULTIVECTOR)> {
	typedef LHS_MULTIVECTOR type;
      };
      template<typename LHS_MULTIVECTOR, typename RHS_MULTIVECTOR>
      typename result<product_multivectors(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type operator()(const LHS_MULTIVECTOR& lhs, const RHS_MULTIVECTOR& rhs) const {
	return typename result<product_multivectors(LHS_MULTIVECTOR, RHS_MULTIVECTOR)>::type(lhs);
      }
    };
    template<typename Metric,
	     typename ValueType>
    struct product_bases
      : boost::proto::callable
    {
      typedef Metric metric;
      typedef ValueType value_type;
      //compile-time part
      template <typename SIGNATURE>
      struct result;
      template <typename THIS, typename LHS_BASE, typename RHS_BASE>
      struct result<THIS(LHS_BASE, RHS_BASE)> {
	typedef types::multivector<types::blade_c<0, value_type>, types::blade_c<(LHS_BASE::first_type::value ^ RHS_BASE::first_type::value), value_type> > type;
      };
      //specialization 0 : squared base
      template <typename THIS, typename BASE>
      struct result<THIS(BASE, BASE)> {
	typedef types::multivector<types::blade_c<0, value_type> > type;
      };
      //specialization 1 : base*scalar
      template<typename THIS, typename LHS_BASE>
      struct result<THIS(LHS_BASE, types::blade_c<0, value_type>)> {
	typedef types::multivector<LHS_BASE> type;
      };
      //specialization 2 : scalar*base
      template<typename THIS, typename RHS_BASE>
      struct result<THIS(types::blade_c<0, value_type>, RHS_BASE)> {
	typedef types::multivector<RHS_BASE> type;
      };
      //specialization 3 : scalar*scalar
      template <typename THIS>
      struct result<THIS(types::blade_c<0, value_type>, types::blade_c<0, value_type>)> {
	typedef types::multivector<types::blade_c<0, value_type> > type;
      };
      //runtime part
      template<typename LHS_BASE, typename RHS_BASE>
      typename result< product_bases(LHS_BASE, RHS_BASE)>::type operator()(const LHS_BASE& lhs, const RHS_BASE& rhs) const {
	value_type scalar_factor = lhs.second*rhs.second;
	value_type dot_value = physics_5D::null<value_type>::value;
	dot_value = g_c<metric, numeric::power_of_2_c<LHS_BASE::first_type::value>::value, numeric::power_of_2_c<RHS_BASE::first_type::value>::value >::value;
	//reorder if j>i, e_j*e_i = 2*(e_i.e_j - e_i^e_j)
	//e_i*e_j = e_i.e_j + e_i^e_j
	if(LHS_BASE::first_type::value > RHS_BASE::first_type::value) {
	  dot_value += dot_value;
	  scalar_factor = (-scalar_factor);
	}
	return typename result< product_bases(LHS_BASE, RHS_BASE)>::type(scalar_factor*dot_value, scalar_factor);
      }
      //specialization 0 : squared base
      template<typename BASE>
      typename result< product_bases(BASE, BASE)>::type operator()(const BASE& lhs, const BASE& rhs) const {
	value_type scalar_factor = lhs.second*rhs.second;
	value_type dot_value = physics_5D::null<value_type>::value;
	dot_value = g_c<metric, numeric::power_of_2_c<BASE::first_type::value>::value, numeric::power_of_2_c<BASE::first_type::value>::value >::value;
	return typename result< product_bases(BASE, BASE)>::type(scalar_factor*dot_value);
      }
      //specialization 1 : base*scalar
      template<typename LHS_BASE>
      typename result< product_bases(LHS_BASE, types::blade_c<0, value_type>)>::type operator()(const LHS_BASE& lhs, const types::blade_c<0, value_type>& rhs) const {
	return typename result< product_bases(LHS_BASE, types::blade_c<0, value_type>)>::type(lhs.second*rhs.second);
      }
      //specialization 2 : scalar*base
      template<typename RHS_BASE>
      typename result< product_bases(types::blade_c<0, value_type>, RHS_BASE)>::type operator()(const types::blade_c<0, value_type>& lhs, const RHS_BASE& rhs) const {
	return typename result< product_bases(types::blade_c<0, value_type>, RHS_BASE)>::type(lhs.second*rhs.second);
      }
      //specialization 3 : scalar*scalar
      typename result< product_bases(types::blade_c<0, value_type>, types::blade_c<0, value_type>)>::type operator()(const types::blade_c<0, value_type>& lhs, const types::blade_c<0, value_type>& rhs) const {
	return typename result< product_bases(types::blade_c<0, value_type>, types::blade_c<0, value_type>)>::type(lhs.second*rhs.second);
      }
    };
  }
}

#endif
