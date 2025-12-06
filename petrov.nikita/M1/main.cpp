#include <stdexcept>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <random>
#include "calculations_of_circle_area.hpp"

namespace
{
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios< char > & s):
      s_(s),
      precision_(s.precision()),
      flags_(s.flags())
    {}
    ~StreamGuard()
    {
      s_.precision(precision_);
      s_.flags(flags_);
    }
  private:
    std::basic_ios< char > & s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };

  void unsafeInit(long long int & tries_val, const char * const * argv)
  {
    char * end = nullptr;
    tries_val = std::strtoll(argv[1], &end, 10);
  }

  void unsafeInit(long long int & tries_val, long int & seed_val, const char * const * argv)
  {
    unsafeInit(tries_val, argv);
    char * end = nullptr;
    seed_val = std::strtol(argv[2], &end, 10);
  }

  void safeInit(long long int & tries_val, long int & seed_val, const int argc, const char * const * argv)
  {
    switch (argc - 1)
    {
    case 1:
      unsafeInit(tries_val, argv);
      break;
    case 2:
      unsafeInit(tries_val, seed_val, argv);
      break;
    default:
      throw std::logic_error("Invalid number of command line arguments");
    }
    if (tries_val <= 0)
    {
      throw std::logic_error("Invalid value of tries number");
    }
    if (seed_val < 0)
    {
      throw std::logic_error("Invalid value of seed");
    }
  }

  void checkValues(int & radius, int & threads_num)
  {
    if (radius <= 0)
    {
      throw std::logic_error("Invalid value of radius");
    }
    if (threads_num <= 0)
    {
      throw std::logic_error("Invalid value of threads' number");
    }
  }

  std::istream & inputData(std::istream & in, int & radius, int & threads_num)
  {
    if (!(in >> radius))
    {
      throw std::invalid_argument("Invalid input of radius");
    }
    if (!(in >> threads_num))
    {
      throw std::invalid_argument("Invalid input of threads' number");
    }
    checkValues(radius, threads_num);
    return in;
  }
}

int main(const int argc, const char * const * argv)
{
  using namespace petrov;

  long long int tries = 0;
  long int seed = 0;
  try
  {
    safeInit(tries, seed, argc, argv);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  std::srand(seed);

  int radius = 0, threads = 0;
  try
  {
    StreamGuard out_guard(std::cout);
    std::cout << std::fixed << std::setprecision(3);

    while (!std::cin.eof())
    {
      inputData(std::cin, radius, threads);
      std::pair< double, double > calc_results = calculateCircleAreaByMonteCarlo(radius, tries, threads);
      std::cout << calc_results.first << " " << calc_results.second << "\n";
    }
  }
  catch (const std::invalid_argument & e)
  {
    if (std::cin.eof())
    {
      return 0;
    }
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    return 3;
  }
}
