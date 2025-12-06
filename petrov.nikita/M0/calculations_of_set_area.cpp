#include "calculations_of_set_area.hpp"
#include <vector>
#include <random>

namespace
{
  using gen_t = std::mt19937;
  using dis_t = std::uniform_real_distribution<>;

  double calculateCircleAreaByMonteCarlo(int radius, long long int tries_num, int threads_num);
}

std::pair< double, double > petrov::calculateSetArea(const circles_map & set, long long int tries_num, int threads_num)
{
  std::vector< int > seeds(threads_num, 0);
  for (size_t i = 0; i < seeds.size(); ++i)
  {
    seeds[i] = std::rand();
  }
}
