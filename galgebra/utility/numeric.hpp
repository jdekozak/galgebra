#if !defined(GALGEBRA_UTILITY_NUMERIC)
#define GALGEBRA_UTILITY_NUMERIC

#include <cstddef>

#include <boost/mpl/times.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/integral_c.hpp>

namespace galgebra {
  namespace numeric {
    // Value^Exponent = power(Value, Exponent)
    template <typename VALUE, typename EXPONENT>
    struct power : boost::mpl::times<VALUE
				     ,power<VALUE
					    ,typename boost::mpl::minus<EXPONENT
									,boost::mpl::integral_c<size_t,1>
									>::type
					    >
				     >
    {};
    // specialization for 0
    template <typename VALUE>
    struct power<VALUE, boost::mpl::integral_c<size_t,0> > : boost::mpl::integral_c<size_t,1>
    {};

    template <typename VALUE>
    struct power_of_2
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 1> > : boost::mpl::integral_c<size_t, 0>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 2> > : boost::mpl::integral_c<size_t, 1>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 4> > : boost::mpl::integral_c<size_t, 2>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 8> > : boost::mpl::integral_c<size_t, 3>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 16> > : boost::mpl::integral_c<size_t, 4>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 32> > : boost::mpl::integral_c<size_t, 5>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 64> > : boost::mpl::integral_c<size_t, 6>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 128> > : boost::mpl::integral_c<size_t, 7>
    {};
    template <>
    struct power_of_2<boost::mpl::integral_c<size_t, 256> > : boost::mpl::integral_c<size_t, 8>
    {};
    template <std::size_t VALUE>
    struct power_of_2_c : power_of_2<boost::mpl::integral_c<size_t, VALUE> >
    {};
  }
}

#endif
