#if !defined(GALGEBRA_MPL_SIZE_IMPL)
#define GALGEBRA_MPL_SIZE_IMPL

namespace galgebra {
  struct map_sequence_tag;
}

namespace boost {
  namespace fusion {
    namespace extension {
      template<typename Tag>
      struct size_impl;

      template<>
      struct size_impl<galgebra::map_sequence_tag> {
	template<typename Sequence>
	struct apply
	  : Sequence::size
	{};
      };
    }
  }
}

#endif
