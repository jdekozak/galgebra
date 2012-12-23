#if !defined(GALGEBRA_MAP_VALUE_OF_DATA_IMPL)
#define GALGEBRA_MAP_VALUE_OF_DATA_IMPL

namespace galgebra {
  struct map_iterator_tag;
}

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct value_of_data_impl;

      template<>
      struct value_of_data_impl<galgebra::map_iterator_tag>
	: value_of_impl<galgebra::map_iterator_tag>
      {};
    }
  }
}

#endif
