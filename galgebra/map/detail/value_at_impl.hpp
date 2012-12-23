#if !defined(GALGEBRA_MAP_VALUE_AT_IMPL)
#define GALGEBRA_MAP_VALUE_AT_IMPL

namespace galgebra
{
    struct map_sequence_tag;
}

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<galgebra::map_sequence_tag>
        {
            template<typename Sequence, typename N>
            struct apply;

	    template<typename Sequence, typename N>
            struct apply
            {
  	        typedef typename Sequence::head type;
            };
        };
    }
}}

#endif
