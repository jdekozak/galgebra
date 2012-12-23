#include "galgebra/map/map.hpp"

namespace galgebra {
  namespace types {
    template <typename... Blades>
    using multivector = galgebra::map<Blades...>;
  }
}
