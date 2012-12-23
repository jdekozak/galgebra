#include <galgebra/types/multivector.hpp>
#include <galgebra/types/blade.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataStructure
#include <boost/test/unit_test.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/include/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/include/end.hpp>

#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/include/prior.hpp>

#include <iostream>
#include <typeinfo>

struct print {
  template<typename T>
  void operator()(const T& value) const {
    std::cout << value << std::endl;
  }
};
BOOST_AUTO_TEST_CASE( Map ) {
/*
int main(int argc, char* argv[]) {

    example::example_struct bert("bert", 99);
    using namespace boost::fusion;

    BOOST_TEST(deref(begin(bert)) == "bert");
    BOOST_TEST(*next(begin(bert)) == 99);
    BOOST_TEST(*prior(end(bert)) == 99);
    BOOST_TEST(*advance_c<1>(begin(bert)) == 99);
    BOOST_TEST(*advance_c<-1>(end(bert)) == 99);
    BOOST_TEST(distance(begin(bert), end(bert)) == 2);

    typedef result_of::begin<example::example_struct>::type first;
    typedef result_of::next<first>::type second;
    BOOST_MPL_ASSERT((boost::is_same<result_of::value_of<first>::type, std::string>));
    BOOST_MPL_ASSERT((boost::is_same<result_of::value_of<second>::type, int>));

    BOOST_TEST(begin(bert) != end(bert));
    BOOST_TEST(advance_c<2>(begin(bert)) == end(const_cast<const example::example_struct&>(bert)));

    BOOST_TEST(at_c<0>(bert) == "bert");
    BOOST_TEST(at_c<1>(bert) == 99);

    BOOST_TEST(at_key<fields::name>(bert) == "bert");
    BOOST_TEST(at_key<fields::age>(bert) == 99);

    BOOST_TEST(has_key<fields::name>(bert));
    BOOST_TEST(has_key<fields::age>(bert));
    BOOST_TEST(!has_key<int>(bert));

    BOOST_MPL_ASSERT((boost::is_same<result_of::value_at_c<example::example_struct, 0>::type, std::string>));
    BOOST_MPL_ASSERT((boost::is_same<result_of::value_at_c<example::example_struct, 1>::type, int>));

    BOOST_MPL_ASSERT((boost::is_same<result_of::value_at_key<example::example_struct, fields::name>::type, std::string>));
    BOOST_MPL_ASSERT((boost::is_same<result_of::value_at_key<example::example_struct, fields::age>::type, int>));

    BOOST_TEST(deref_data(begin(bert)) == "bert");
    BOOST_TEST(deref_data(next(begin(bert))) == 99);

    BOOST_TEST(size(bert) == 2);

    return boost::report_errors();

    */

  galgebra::types::multivector<int> my_int;
  galgebra::types::multivector<int, char> my_tuple;

  static_assert(boost::fusion::traits::is_associative<galgebra::types::multivector<int, char> >::value,"Not an associative container !");
  static_assert(boost::fusion::traits::is_random_access<galgebra::types::multivector<int, char> >::value,"Not a random access container !");
  static_assert(boost::fusion::traits::is_sequence<galgebra::types::multivector<int, char> >::value,"Not a sequence !");


  typedef galgebra::types::multivector<galgebra::types::blade_c<1, double>
    ,galgebra::types::blade_c<2, double>
    ,galgebra::types::blade_c<3, double>
    ,galgebra::types::blade_c<4, double>
    ,galgebra::types::blade_c<5, double>
    ,galgebra::types::blade_c<6, double>
    ,galgebra::types::blade_c<7, double>
    ,galgebra::types::blade_c<8, double>
    ,galgebra::types::blade_c<9, double>
    ,galgebra::types::blade_c<10, double>
    ,galgebra::types::blade_c<11, double>
    ,galgebra::types::blade_c<12, double>
    ,galgebra::types::blade_c<13, double>
    ,galgebra::types::blade_c<14, double>
    ,galgebra::types::blade_c<15, double>
    ,galgebra::types::blade_c<16, double>
    ,galgebra::types::blade_c<17, double>
    ,galgebra::types::blade_c<18, double>
    ,galgebra::types::blade_c<19, double>
    ,galgebra::types::blade_c<20, double> > theType;

  int the_size = boost::fusion::result_of::size< galgebra::types::multivector<galgebra::types::blade_c<1, double>
    ,galgebra::types::blade_c<2, double>
    ,galgebra::types::blade_c<3, double>
    ,galgebra::types::blade_c<4, double>
    ,galgebra::types::blade_c<5, double>
    ,galgebra::types::blade_c<6, double>
    ,galgebra::types::blade_c<7, double>
    ,galgebra::types::blade_c<8, double>
    ,galgebra::types::blade_c<9, double>
    ,galgebra::types::blade_c<10, double>
    ,galgebra::types::blade_c<11, double>
    ,galgebra::types::blade_c<12, double>
    ,galgebra::types::blade_c<13, double>
    ,galgebra::types::blade_c<14, double>
    ,galgebra::types::blade_c<15, double>
    ,galgebra::types::blade_c<16, double>
    ,galgebra::types::blade_c<17, double>
    ,galgebra::types::blade_c<18, double>
    ,galgebra::types::blade_c<19, double>
    ,galgebra::types::blade_c<20, double> > >::value;

  BOOST_CHECK_EQUAL( the_size, 20 );

  std::cout << boost::fusion::result_of::empty<theType>::value << std::endl;
  std::cout << boost::fusion::result_of::empty<galgebra::types::multivector<> >::value << std::endl;

  typedef galgebra::types::multivector<int,char> theBlade;
  typedef typename boost::fusion::result_of::begin<theBlade>::type start;
  typedef typename boost::fusion::result_of::end<theBlade>::type ending;
  typedef typename boost::fusion::result_of::prior<ending>::type last;
  std::cout << typeid(boost::fusion::result_of::deref<start>::type() ).name() << std::endl;
  std::cout << typeid(boost::fusion::result_of::deref<last>::type() ).name() << std::endl;
  std::cout << typeid(boost::fusion::result_of::deref<typename boost::fusion::result_of::next<start>::type>::type() ).name() << std::endl;
  std::cout << typeid(boost::fusion::result_of::deref<typename boost::fusion::result_of::prior<last>::type>::type() ).name() << std::endl;

  typedef typename boost::fusion::result_of::begin<galgebra::types::multivector<> >::type last_bis;
  std::cout << typeid(last_bis()).name() << std::endl;

  boost::fusion::for_each(theType(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20), print());

  
}
