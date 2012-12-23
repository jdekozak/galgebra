/*
//to store the multivectors as a fusion::map, needs 2^n as maximum
#define BOOST_MPL_LIMIT_METAFUNCTION_ARITY 32

#define BOOST_PROTO_MAX_ARITY 32
#define BOOST_PROTO_MAX_FUNCTION_CALL_ARITY 32
#define BOOST_PROTO_MAX_LOGICAL_ARITY 32

#define FUSION_MAX_MAP_SIZE 32
*/

#include "./types/base.hpp"
#include "./types/blade.hpp"
#include "./types/vector.hpp"
#include "./types/multivector.hpp"

#include "./dimension.hpp"
#include "./g.hpp"

#include "./physics_5D.hpp"
#include "./grammar.hpp"

namespace galgebra {
  //user interface
  template<typename METRIC = physics_5D::metric
	   ,typename VALUE_TYPE = physics_5D::value_type
	   ,typename BASE_SYMBOLS = physics_5D::base_symbols
	   ,typename VARIABLE_SYMBOLS = physics_5D::variable_symbols
	   >
  struct algebra {
    typedef METRIC metric;
    typedef VALUE_TYPE value_type;
    typedef BASE_SYMBOLS base_symbols;
    typedef VARIABLE_SYMBOLS variable_symbols;
    //dimension
    typedef typename dimension<metric>::type dimension;
    //metric getters
    template<typename I, typename J>
    using g = g<metric, I, J>;
    template<std::size_t I, std::size_t J>
    using g_c = g_c<metric, I, J>;
    //blade
    template<typename Bitfield>
    using blade = types::blade<Bitfield, value_type>;
    template<std::size_t Bitfield>
    using blade_c = types::blade_c<Bitfield, value_type>;
    //get_blade_c
    template <std::size_t BLADE, typename MULTIVECTOR>
    static value_type get_blade_c(const MULTIVECTOR& mv) {
      static_assert(boost::fusion::result_of::has_key<MULTIVECTOR, boost::mpl::integral_c<size_t,BLADE> >::value,"This blade is not in multivector");
      return boost::fusion::at_key<boost::mpl::integral_c<size_t,BLADE> >(mv);
    }
    template <std::size_t BLADE>
    static value_type get_blade_c(const types::blade_c<BLADE, value_type>& blade) {
      return blade.second;
    }
    //grammar
    typedef expression_templates::grammar<metric, value_type, base_symbols> grammar; 
    //base
    template <typename N>
    using base = types::base<metric, base_symbols, N>;
    template <std::size_t N>
    using base_c = types::base_c<metric, base_symbols, N>;
    //vector
    typedef typename types::vector<metric, value_type>::type vector;
  };

}
