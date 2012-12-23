#include <galgebra/galgebra.hpp>
#include <galgebra/io/output.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SpaceTime
#include <boost/test/unit_test.hpp>

//pick up the default Cl(1,4) over R
typedef galgebra::algebra<> space_time;

//algebra terminal symbols
boost::proto::terminal< space_time::base_c<1> >::type e_1 = {};
boost::proto::terminal< space_time::base_c<2> >::type e_2 = {};
boost::proto::terminal< space_time::base_c<3> >::type e_3 = {};
boost::proto::terminal< space_time::base_c<4> >::type e_4 = {};
boost::proto::terminal< space_time::base_c<5> >::type e_5 = {};

BOOST_AUTO_TEST_CASE( Map )
{
  galgebra::types::multivector<int> my_int;
  galgebra::types::multivector<int, char> my_tuple;

  static_assert(boost::fusion::traits::is_associative<galgebra::types::multivector<int, char> >::value,"Not an associative container !");
  static_assert(boost::fusion::traits::is_random_access<galgebra::types::multivector<int, char> >::value,"Not a random access container !");
  static_assert(boost::fusion::traits::is_sequence<galgebra::types::multivector<int, char> >::value,"Not a sequence !");
}

BOOST_AUTO_TEST_CASE( Numeric )
{
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,0> >::value), 1);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,1> >::value), 2);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,2> >::value), 4);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,3> >::value), 8);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,4> >::value), 16);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,5> >::value), 32);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,6> >::value), 64);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,7> >::value), 128);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power<boost::mpl::integral_c<size_t,2>, boost::mpl::integral_c<size_t,8> >::value), 256);

  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<1>::value), 0);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<2>::value), 1);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<4>::value), 2);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<8>::value), 3);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<16>::value), 4);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<32>::value), 5);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<64>::value), 6);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<128>::value), 7);
  BOOST_CHECK_EQUAL( (galgebra::numeric::power_of_2_c<256>::value), 8);
}

BOOST_AUTO_TEST_CASE( Metric )
{
  galgebra::io::display_metric()(space_time());
  //diagonal - metric signature
  BOOST_CHECK_EQUAL( (space_time::g_c<0,0>::value),  1 );
  BOOST_CHECK_EQUAL( (space_time::g_c<1,1>::value), -1 );
  BOOST_CHECK_EQUAL( (space_time::g_c<2,2>::value), -1 );
  BOOST_CHECK_EQUAL( (space_time::g_c<3,3>::value), -1 );
  BOOST_CHECK_EQUAL( (space_time::g_c<4,4>::value), -1 );

  //dimension
  BOOST_CHECK_EQUAL( space_time::dimension::value, 5 );

  //just one to check
  BOOST_CHECK_EQUAL( (space_time::g_c<0,1>::value), 0);
}

BOOST_AUTO_TEST_CASE( Terminals )
{
  BOOST_CHECK_EQUAL(space_time::grammar::make_blade()(e_3),space_time::blade_c<4>(1.0));
  BOOST_CHECK_EQUAL(space_time::grammar::make_blade()(boost::proto::lit(2.5)), space_time::blade_c<0>(2.5));
}

BOOST_AUTO_TEST_CASE( Plus )
{
  auto e_1_plus_e_3 = space_time::grammar::plus()(e_1 + e_3);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<1>(e_1_plus_e_3)), 1.0 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<4>(e_1_plus_e_3)), 1.0 );

  auto e_1_plus_e_2_plus_e_3 = space_time::grammar::plus()(e_1 + e_2 + e_3);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<1>(e_1_plus_e_2_plus_e_3)), 1.0 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<2>(e_1_plus_e_2_plus_e_3)), 1.0 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<4>(e_1_plus_e_2_plus_e_3)), 1.0 );

  auto e_1_plus_e_2_plus_e_3_plus_e_4 = space_time::grammar::plus()( (e_1 + e_2) + (e_3 + e_4) );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<1>(e_1_plus_e_2_plus_e_3_plus_e_4)), 1.0 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<2>(e_1_plus_e_2_plus_e_3_plus_e_4)), 1.0 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<4>(e_1_plus_e_2_plus_e_3_plus_e_4)), 1.0 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<8>(e_1_plus_e_2_plus_e_3_plus_e_4)), 1.0 );

  auto e_1_plus_3_3 = space_time::grammar::plus()(e_1 + 3.3);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<0>(e_1_plus_3_3)), 3.3 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<1>(e_1_plus_3_3)), 1.0 );

  auto _3_3_plus_e_1 = space_time::grammar::plus()(3.3 + e_1);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<0>(_3_3_plus_e_1)), 3.3 );
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<1>(_3_3_plus_e_1)), 1.0 );

  auto e_1_plus_e_1 = space_time::grammar::plus()(e_1 + e_1);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<1>(e_1_plus_e_1)), 2.0 );
}

BOOST_AUTO_TEST_CASE( Multiplies )
{
  auto _3_3_mul_e_3 = space_time::multiplies()(3.3*e_3);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<4>(_3_3_mul_e_3)), 3.3 );

  auto e_3_mul_3_3 = space_time::multiplies()(e_3*3.3);
  BOOST_CHECK_EQUAL( (space_time::get_blade_c<4>(e_3_mul_3_3)), 3.3 );

  auto e_2_mul_e_3 = space_time::multiplies()(e_2*e_3);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(e_2_mul_e_3)), 0.0 );
  BOOST_CHECK_EQUAL((space_time::get_blade_c<6>(e_2_mul_e_3)), 1.0 );

  auto e_3_mul_e_2 = space_time::multiplies()(e_3*e_2);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(e_3_mul_e_2)), 0.0 );
  BOOST_CHECK_EQUAL((space_time::get_blade_c<6>(e_3_mul_e_2)), -1.0 );

  auto e_1_mul_e_1 = space_time::multiplies()(e_1*e_1);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(e_1_mul_e_1)), 1.0 );
  auto e_2_mul_e_2 = space_time::multiplies()(e_2*e_2);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(e_2_mul_e_2)), -1.0 );


  auto _3_3_mul_2_2 = space_time::multiplies()(boost::proto::lit(3.3)*boost::proto::lit(2.2));
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(_3_3_mul_2_2)), 7.26 );

  auto _2_2_mul_3_3 = space_time::multiplies()(boost::proto::lit(2.2)*boost::proto::lit(3.3));
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(_2_2_mul_3_3)), 7.26 );
  
  boost::proto::display_expr(2.2*e_2*3.3*e_3);
  /*
  auto _2_2e_2_mul_3_3e_3 = space_time::multiplies()(2.2*e_2*3.3*e_3);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<0>(_2_2e_2_mul_3_3e_3)), 0.0);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<6>(_2_2e_2_mul_3_3e_3)), 7.26);
  */
}

BOOST_AUTO_TEST_CASE( Vector )
{
  auto vector_1_1_2_2_3_3_4_4_5_5 = space_time::vector(1.1,2.2,3.3,4.4,5.5);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<1>(vector_1_1_2_2_3_3_4_4_5_5)), 1.1);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<2>(vector_1_1_2_2_3_3_4_4_5_5)), 2.2);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<4>(vector_1_1_2_2_3_3_4_4_5_5)), 3.3);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<8>(vector_1_1_2_2_3_3_4_4_5_5)), 4.4);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<16>(vector_1_1_2_2_3_3_4_4_5_5)), 5.5);

  boost::proto::display_expr(1.1*e_1 + 2.2*e_2 + 3.3*e_3 + 4.4*e_4 + 5.5*e_5);

  auto _1_1e_1_plus_2_2e_2_plus_3_3e_3_plus_4_4e_4_plus_5_5e_5 = space_time::multivector()(1.1*e_1 + 2.2*e_2 + 3.3*e_3 + 4.4*e_4 + 5.5*e_5);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<1>(_1_1e_1_plus_2_2e_2_plus_3_3e_3_plus_4_4e_4_plus_5_5e_5)), 1.1);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<2>(_1_1e_1_plus_2_2e_2_plus_3_3e_3_plus_4_4e_4_plus_5_5e_5)), 2.2);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<4>(_1_1e_1_plus_2_2e_2_plus_3_3e_3_plus_4_4e_4_plus_5_5e_5)), 3.3);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<8>(_1_1e_1_plus_2_2e_2_plus_3_3e_3_plus_4_4e_4_plus_5_5e_5)), 4.4);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<16>(_1_1e_1_plus_2_2e_2_plus_3_3e_3_plus_4_4e_4_plus_5_5e_5)), 5.5);

  auto e_1_plus_1_1e_1 = space_time::multivector()(e_1 + 1.1*e_1);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<1>(e_1_plus_1_1e_1)), 2.1);

  auto _1_1e_1_plus_1_1e_1 = space_time::multivector()(1.1*e_1 + 1.1*e_1);
  BOOST_CHECK_EQUAL((space_time::get_blade_c<1>(_1_1e_1_plus_1_1e_1)), 2.2);
}
