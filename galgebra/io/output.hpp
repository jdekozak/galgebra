#if !defined(GALGEBRA_IO_OUTPUT)
#define GALGEBRA_IO_OUTPUT

#include <iomanip>
#include <iostream>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

#include "../physics_5D.hpp"

namespace galgebra {
  namespace io {
    struct display_value {
      typedef void result_type;
      template<typename Item>
      void operator()(Item i) const {
	std::cout << std::setiosflags(std::ios::right) << std::setw(3) << i;
      }
    };
    struct display_row {
      typedef void result_type;
      template<typename Row>
      void operator()(Row row) const {
	boost::fusion::for_each(row, display_value());
	std::cout << std::endl;
      }
    };
    struct display_metric {
      typedef void result_type;
      template<typename ALGEBRA>
      void operator()(const ALGEBRA& algebra) const {
	boost::fusion::for_each(typename ALGEBRA::metric(), display_row());
      }
    };

    struct print_symbol {
      template<typename BLADE>
      void operator()(const BLADE& value) const {
	if(BLADE::first_type::value) {
	  std::size_t position;
	  bool first;
	  for(first = false, position = 0; position < 8 && !first; ++position) {
	    if(BLADE::first_type::value & (1<<position)) {
	      std::cout << "e_" << (position+1);
	      first = true;
	    }
	  }
	  for(; position < 8; ++position) {
	    if(BLADE::first_type::value & (1<<position)) {
	      std::cout << "^e_" << (position+1);
	    }
	  }
	} else {
	  std::cout << "S";
	}
      }
    };

    struct print_blade {
      template<typename BLADE>
      void operator()(const BLADE& value) const {
	if(value.second != physics_5D::null<typename BLADE::second_type>::value) {
	  std::cout << value.second;
	  print_symbol()(value);
	  std::cout << " ";
	}
      }
    };

    struct print_multivector {
      template<typename MULTIVECTOR>
      void operator()(const MULTIVECTOR& value) const {
	boost::fusion::for_each(value, print_blade());
	std::cout << std::endl;
      }
    };
  }
}

#endif
