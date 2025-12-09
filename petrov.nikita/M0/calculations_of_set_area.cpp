#include "calculations_of_set_area.hpp"
#include <numeric>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

namespace
{
  using gen_t = std::mt19937;
  using dis_t = std::uniform_real_distribution<>;

  double getDistanceFromCircleCenter(const petrov::point_t_dbl & point)
  {
    return std::sqrt(point.x * point.x + point.y * point.y);
  }

  bool doesPointBelongToCircle(const petrov::point_t_dbl & point, int radius)
  {
    return getDistanceFromCircleCenter(point) < radius;
  }

  void calculateInsidePointsNumTh(int seed, long long int tries_num, int radius, size_t & res)
  {
    gen_t gen(seed);
    dis_t dis(0.0, double(radius));

    size_t inside_points = 0;

    for (long long int i = 0; i < tries_num; ++i)
    {
      petrov::point_t_dbl point{ dis(gen), dis(gen) };
      if (doesPointBelongToCircle(point, radius))
      {
        ++inside_points;
      }
    }

    res = inside_points;
  }

  double calculateAreaOfCircle(int radius, size_t inside_points, size_t outside_points)
  {
    return 4 * radius * radius * (inside_points / double(outside_points));
  }
}

std::pair< double, double > petrov::calculateSetArea(const circles_map & set, long long int tries_num, int threads_num)
{
  std::vector< int > seeds(threads_num, 0);
  for (size_t i = 0; i < seeds.size(); ++i)
  {
    seeds[i] = std::rand();
  }

  std::vector< std::thread > threads;
  threads.reserve(threads_num - 1);
  std::vector< double > circles_areas(set.size(), 0.0);
  std::vector< size_t > inside_points(threads_num, 0);

  auto start = std::chrono::high_resolution_clock::now();

  size_t per_th = tries_num / threads_num;
  size_t area_index = 0;
  for (auto it = set.cbegin(); it != set.cend(); ++it)
  {
    int i = 0;
    for (; i < threads_num - 1; ++i)
    {
      threads.emplace_back(calculateInsidePointsNumTh, seeds[i], per_th, it->second.r, std::ref(inside_points[i]));
    }
    calculateInsidePointsNumTh(seeds[i], per_th + tries_num % threads_num, it->second.r, inside_points.back());
    for (auto && th : threads) th.join();
    size_t inside_points_sum = std::accumulate(inside_points.cbegin(), inside_points.cend(), 0);
    circles_areas[area_index++] = calculateAreaOfCircle(it->second.r, inside_points_sum, tries_num);
    threads.clear();
  }
  double set_area = std::accumulate(circles_areas.cbegin(), circles_areas.cend(), 0.0);

  auto stop = std::chrono::high_resolution_clock::now();

  using fpMilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;
  auto duration = fpMilliseconds(stop - start);
  auto time = duration.count();

  return std::make_pair(set_area, time);
}
