#if !defined(GALGEBRA_MAP_TYPE)
#define GALGEBRA_MAP_TYPE

#include <boost/mpl/int.hpp>
#include <boost/mpl/void_fwd.hpp>

namespace galgebra
{
  template<typename... Items>
  struct map;

  template<>
  struct map<> {
    typedef boost::mpl::void_ head;
    typedef boost::mpl::int_<0> size;
  };

  template<typename Item, typename... Items>
  struct map<Item, Items...>
  {
    typedef Item head;
    typedef map<Items...> tail;
    typedef boost::mpl::int_<1 + map<Items...>::size::value> size;

    head head_;
    tail tail_;

    map() : head_(), tail_() {}
    map(const head& hd, const Items&... tl) : head_(hd), tail_(tl...) {}
    map(const map<Item, Items...>& source) : head_(source.head_), tail_(source.tail_) {}
  };
}

#endif
