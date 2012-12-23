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
      //compile time
      template <typename Signature>
      struct result;
      template <typename This
		,typename LhsMultivector
		,typename RhsMultivector
		,typename Metric
		,typename ValueType>
      struct result<This(LhsMultivector
			 ,RhsMultivector
			 ,Metric
			 ,ValueType)> {
	typedef LhsMultivector type;
      };
      //base*mv
      template<typename This
	       ,std::size_t BitField
	       ,typename RhsMultivector
	       ,typename Metric
	       ,typename ValueType>
      struct result<This(types::blade_c<BitField, ValueType>
			 ,RhsMultivector
			 ,Metric
			 ,ValueType)> {
	typedef RhsMultivector type;
      };
      //scalar*mv
      template<typename This
	       ,typename RhsMultivector
	       ,typename Metric
	       ,typename ValueType>
      struct result<This(types::blade_c<0, ValueType>
			 ,RhsMultivector
			 ,Metric
			 ,ValueType)> {
	typedef RhsMultivector type;
      };
      //runtime
      template<typename LhsMultivector
	       ,typename RhsMultivector
	       ,typename Metric
	       ,typename ValueType>
      typename result<product_multivectors(LhsMultivector
					   ,RhsMultivector
					   ,Metric
					   ,ValueType)>::type operator()(const LhsMultivector& lhs
									 ,const RhsMultivector& rhs
									 ,const Metric&
									 ,const ValueType&) const {
	return typename result<product_multivectors(LhsMultivector
						    ,RhsMultivector
						    ,Metric
						    ,ValueType)>::type(lhs);
      }
      //base*mv
      template<std::size_t BitField
	       ,typename RhsMultivector
	       ,typename Metric
	       ,typename ValueType>
      typename result<product_multivectors(types::blade_c<BitField, ValueType>
					   ,RhsMultivector
					   ,Metric
					   ,ValueType)>::type operator()(const types::blade_c<BitField, ValueType>& lhs
									 ,const RhsMultivector& rhs
									 ,const Metric&
									 ,const ValueType&) const {
	return typename result<product_multivectors(types::blade_c<BitField, ValueType>
						    ,RhsMultivector
						    ,Metric
						    ,ValueType)>::type(rhs);
      }
      //scalar*mv
      template<typename RhsMultivector
	       ,typename Metric
	       ,typename ValueType>
      typename result<product_multivectors(types::blade_c<0, ValueType>
					   ,RhsMultivector
					   ,Metric
					   ,ValueType)>::type operator()(const types::blade_c<0, ValueType>& lhs
									 ,const RhsMultivector& rhs
									 ,const Metric&
									 ,const ValueType&) const {
	return typename result<product_multivectors(types::blade_c<0, ValueType>
						    ,RhsMultivector
						    ,Metric
						    ,ValueType)>::type(rhs);
      }
    };

    struct product_bases
      : boost::proto::callable
    {
      //compile-time part
      template <typename Signature>
      struct result;
      template <typename This
		,typename LhsBase
		,typename RhsBase
		,typename Metric
		,typename ValueType>
      struct result<This(LhsBase
			 ,RhsBase
			 ,Metric
			 ,ValueType)> {
	typedef types::multivector<types::blade_c<0, ValueType>
				   ,types::blade_c<(LhsBase::first_type::value ^ RhsBase::first_type::value)
						   ,ValueType> > type;
      };
      //squared base
      template <typename This
		,typename Base
		,typename Metric
		,typename ValueType>
      struct result<This(Base
			 ,Base
			 ,Metric
			 ,ValueType)> {
	typedef types::multivector<types::blade_c<0, ValueType> > type;
      };
      //base*scalar
      template<typename This
	       ,typename LhsBase
	       ,typename Metric
	       ,typename ValueType>
      struct result<This(LhsBase
			 ,types::blade_c<0, ValueType>
			 ,Metric
			 ,ValueType)> {
	typedef types::multivector<LhsBase> type;
      };
      //scalar*base
      template<typename This
	       ,typename RhsBase
	       ,typename Metric
	       ,typename ValueType>
      struct result<This(types::blade_c<0, ValueType>
			 ,RhsBase
			 ,Metric
			 ,ValueType)> {
	typedef types::multivector<RhsBase> type;
      };
      //scalar*scalar
      template <typename This
		,typename Metric
		,typename ValueType>
      struct result<This(types::blade_c<0, ValueType>
			 ,types::blade_c<0, ValueType>
			 ,Metric
			 ,ValueType)> {
	typedef types::multivector<types::blade_c<0, ValueType> > type;
      };
      //runtime part
      template<typename LhsBase
	       ,typename RhsBase
	       ,typename Metric
	       ,typename ValueType>
      typename result< product_bases(LhsBase
				     ,RhsBase
				     ,Metric
				     ,ValueType)>::type operator()(const LhsBase& lhs
								   ,const RhsBase& rhs
								   ,const Metric&
								   ,const ValueType&) const {
	ValueType scalar_factor = lhs.second*rhs.second;
	ValueType dot_value = physics_5D::null<ValueType>::value;
	dot_value = g_c<Metric
	  ,numeric::power_of_2_c<LhsBase::first_type::value>::value
	  ,numeric::power_of_2_c<RhsBase::first_type::value>::value >::value;
	//reorder if j>i, e_j*e_i = 2*(e_i.e_j - e_i^e_j)
	//e_i*e_j = e_i.e_j + e_i^e_j
	if(LhsBase::first_type::value > RhsBase::first_type::value) {
	  dot_value += dot_value;
	  scalar_factor = (-scalar_factor);
	}
	return typename result< product_bases(LhsBase
					      ,RhsBase
					      ,Metric
					      ,ValueType)>::type(scalar_factor*dot_value, scalar_factor);
      }
      //squared base
      template<typename Base
	       ,typename Metric
	       ,typename ValueType>
      typename result< product_bases(Base
				     ,Base
				     ,Metric
				     ,ValueType)>::type operator()(const Base& lhs
								   ,const Base& rhs
								   ,const Metric&
								   ,const ValueType&) const {
	ValueType scalar_factor = lhs.second*rhs.second;
	ValueType dot_value = physics_5D::null<ValueType>::value;
	dot_value = g_c<Metric
	  ,numeric::power_of_2_c<Base::first_type::value>::value
	  ,numeric::power_of_2_c<Base::first_type::value>::value >::value;
	return typename result< product_bases(Base
					      ,Base
					      ,Metric
					      ,ValueType)>::type(scalar_factor*dot_value);
      }
      //base*scalar
      template<typename LhsBase
	       ,typename Metric
	       ,typename ValueType>
      typename result< product_bases(LhsBase
				     ,types::blade_c<0, ValueType>
				     ,Metric
				     ,ValueType)>::type operator()(const LhsBase& lhs
								   ,const types::blade_c<0, ValueType>& rhs
								   ,const Metric&
								   ,const ValueType&) const {
	return typename result< product_bases(LhsBase
					      ,types::blade_c<0, ValueType>
					      ,Metric
					      ,ValueType)>::type(lhs.second*rhs.second);
      }
      //scalar*base
      template<typename RhsBase
	       ,typename Metric
	       ,typename ValueType>
      typename result< product_bases(types::blade_c<0, ValueType>
				     ,RhsBase
				     ,Metric
				     ,ValueType)>::type operator()(const types::blade_c<0, ValueType>& lhs
								   ,const RhsBase& rhs
								   ,const Metric&
								   ,const ValueType&) const {
	return typename result< product_bases(types::blade_c<0, ValueType>
					      ,RhsBase
					      ,Metric
					      ,ValueType)>::type(lhs.second*rhs.second);
      }
      //scalar*scalar
      template<typename Metric
	       ,typename ValueType>
      typename result< product_bases(types::blade_c<0, ValueType>
				     ,types::blade_c<0, ValueType>
				     ,Metric
				     ,ValueType)>::type operator()(const types::blade_c<0, ValueType>& lhs
								   ,const types::blade_c<0, ValueType>& rhs
								   ,const Metric&
								   ,const ValueType) const {
	return typename result< product_bases(types::blade_c<0, ValueType>
					      ,types::blade_c<0, ValueType>
					      ,Metric
					      ,ValueType)>::type(lhs.second*rhs.second);
      }
    };
  }
}

#endif
