#include <galgebra/types/multivector.hpp>
#include <galgebra/types/blade.hpp>

#include <boost/test/unit_test.hpp>

#include <boost/type_traits/is_same.hpp> 

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
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at_key.hpp>
#include <boost/fusion/include/value_at_key.hpp>

#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/include/prior.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/include/advance.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/include/value_of.hpp>

#include <iostream>
#include <typeinfo>

BOOST_AUTO_TEST_CASE( Map ) {

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

  BOOST_CHECK_EQUAL(boost::fusion::result_of::empty<theType>::value, boost::mpl::false_());
  BOOST_CHECK_EQUAL(boost::fusion::result_of::empty<galgebra::types::multivector<> >::value, boost::mpl::true_());

  typedef galgebra::types::multivector<int,char> type_t;
  type_t element(1,'a');
  BOOST_CHECK_EQUAL(boost::fusion::deref(boost::fusion::begin(element)), 1);
  BOOST_CHECK_EQUAL(*boost::fusion::next(boost::fusion::begin(element)), 'a');
  BOOST_CHECK_EQUAL(*boost::fusion::prior(boost::fusion::end(element)), 'a');
  BOOST_CHECK_EQUAL(*boost::fusion::advance_c<1>(boost::fusion::begin(element)), 'a');
  BOOST_CHECK_EQUAL(*boost::fusion::advance_c<-1>(boost::fusion::end(element)), 'a');
  BOOST_CHECK_EQUAL(boost::fusion::distance(boost::fusion::begin(element), boost::fusion::end(element)), 2);

  typedef typename boost::fusion::result_of::begin<type_t>::type first;
  typedef typename boost::fusion::result_of::next<first>::type second;
  static_assert((boost::is_same<boost::fusion::result_of::value_of<first>::type, int>::value), "First is different");
  static_assert((boost::is_same<boost::fusion::result_of::value_of<second>::type, char>::value), "Second is different");

  BOOST_CHECK((boost::fusion::begin(element) != boost::fusion::end(element)));
  BOOST_CHECK(boost::fusion::advance_c<2>(boost::fusion::begin(element)) == boost::fusion::end(const_cast<const type_t&>(element)));
  BOOST_CHECK_EQUAL(boost::fusion::at_c<0>(element), 1);
  BOOST_CHECK_EQUAL(boost::fusion::at_c<1>(element), 'a');

  typedef galgebra::types::multivector<boost::fusion::pair<int, char>, boost::fusion::pair<long,char> > map_t;
  map_t aMap('a', 'b');

  BOOST_CHECK_EQUAL(boost::fusion::at_key<int>(aMap), (boost::fusion::pair<int, char>('a')));
  BOOST_CHECK_EQUAL(boost::fusion::at_key<long>(aMap), (boost::fusion::pair<long, char>('b')));

  BOOST_CHECK(boost::fusion::has_key<int>(aMap));
  BOOST_CHECK(boost::fusion::has_key<long>(aMap));
  BOOST_CHECK(!boost::fusion::has_key<char>(aMap));

  static_assert(boost::is_same<boost::fusion::result_of::value_at_c<map_t, 0>::type, boost::fusion::pair<int,char> >::value, "Wrong value type");
  static_assert(boost::is_same<boost::fusion::result_of::value_at_c<map_t, 1>::type, boost::fusion::pair<long,char> >::value, "Wrong value type");

  static_assert(boost::is_same<boost::fusion::result_of::value_at_key<map_t, int>::type, boost::fusion::pair<int,char> >::value, "Wrong value type");
  static_assert(boost::is_same<boost::fusion::result_of::value_at_key<map_t, long>::type, boost::fusion::pair<long,char> >::value, "Wrong value type");

  BOOST_CHECK_EQUAL(boost::fusion::deref_data(boost::fusion::begin(aMap)), (boost::fusion::pair<int, char>('a')) );
  BOOST_CHECK_EQUAL(boost::fusion::deref_data(boost::fusion::next(boost::fusion::begin(aMap))), (boost::fusion::pair<long, char>('b')) );

  BOOST_CHECK_EQUAL( boost::fusion::size(theType()), 20 );
}
