#if !defined(GALGEBRA_TYPES_MULTIVECTOR)
#define GALGEBRA_TYPES_MULTIVECTOR

#include "galgebra/map/map.hpp"

namespace galgebra {
  namespace types {
    template <typename... Blades>
    using multivector = galgebra::map<Blades...>;
  }
}

#endif
