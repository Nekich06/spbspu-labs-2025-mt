#ifndef CALCULATIONS_OF_SET_AREA
#define CALCULATIONS_OF_SET_AREA

#include <vector>
#include <utility>
#include <geometry.hpp>

namespace petrov
{
  std::pair< double, double > calculateSetArea(const std::vector< circle_t > & set, long long int tries_num, int threads_num);
}

#endif
