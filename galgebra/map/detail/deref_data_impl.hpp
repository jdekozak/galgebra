#if !defined(GALGEBRA_MAP_DEREF_DATA_IMPL)
#define GALGEBRA_MAP_DEREF_DATA_IMPL

namespace galgebra
{
    struct map_iterator_tag;
}

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct deref_data_impl;

        template<>
        struct deref_data_impl<galgebra::map_iterator_tag>
          : deref_impl<galgebra::map_iterator_tag>
        {};
    }
}}

#endif
