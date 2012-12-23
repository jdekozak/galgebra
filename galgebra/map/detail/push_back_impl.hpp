#if !defined(GALGEBRA_MAP_PUSH_BACK_IMPL)
#define GALGEBRA_MAP_PUSH_BACK_IMPL

namespace boost {
  namespace mpl {
    template <typename Tag>
    struct push_back_impl;
    template <>
    struct push_back_impl<galgebra::map_sequence_tag> {
      template<typename Sequence, typename Item>
      struct apply;
      template<typename Item, typename... Items>
      struct apply<galgebra::map<Items...>, Item> {
	typedef galgebra::map<Items..., Item> type;
      };
    };
  }
}

#endif
