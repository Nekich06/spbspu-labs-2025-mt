#ifndef CALCULATIONS_OF_SET_AREA
#define CALCULATIONS_OF_SET_AREA

#include <utility>
#include <data_types.hpp>

namespace petrov
{
  std::pair< double, double > calculateSetArea(const circles_map & set, long long int tries_num, int threads_num);
}

#endif
