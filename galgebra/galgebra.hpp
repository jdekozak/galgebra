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
  template<typename Metric = physics_5D::metric
	   ,typename ValueType = physics_5D::value_type
	   ,typename BaseSymbols = physics_5D::base_symbols
	   ,typename VariableSymbols = physics_5D::variable_symbols
	   >
  struct algebra {
    typedef Metric metric;
    typedef ValueType value_type;
    typedef BaseSymbols base_symbols;
    typedef VariableSymbols variable_symbols;
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
    template <std::size_t Blade, typename Multivector>
    static value_type get_blade_c(const Multivector& mv) {
      static_assert(boost::fusion::result_of::has_key<Multivector, boost::mpl::integral_c<size_t,Blade> >::value,"This blade is not in multivector");
      types::blade_c<Blade, value_type> blade = boost::fusion::at_key<boost::mpl::integral_c<size_t,Blade> >(mv);
      return blade.second;
    }
    template <std::size_t Blade>
    static value_type get_blade_c(const types::blade_c<Blade, value_type>& blade) {
      return blade.second;
    }
    //grammar
    typedef expression_templates::grammar<metric, value_type, base_symbols> grammar; 

    //base
    template <typename N>
    using base = types::base<metric, value_type, base_symbols, N>;
    template <std::size_t N>
    using base_c = types::base_c<metric, value_type, base_symbols, N>;

    //vector
    typedef typename types::vector<metric, value_type>::type vector;
  };

}
