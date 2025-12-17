#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <geometry.hpp>
#include <serializer.hpp>
#include "calculations_of_set_area.hpp"

int main(const int argc, const char * const * argv)
{
  if (argc != 2)
  {
    return 1;
  }
  using namespace petrov;
  long int seed = 0;

  seed = std::stoi(argv[1]);
  std::srand(seed);

  while (!(std::cin.eof()))
  {
    // std::cerr << "[CHILD] - CYCLE STARTED...\n";
    size_t circles_num;
    if ((std::cin >> circles_num).eof())
    {
      break;
    }
    std::cin.ignore(1);
    // std::cerr << "[CHILD] - DESERIALIZING DATA\n";
    std::vector< circle_t > set;
    set.reserve(circles_num - 1);
    for (size_t i = 0; i < circles_num; ++i)
    {
      int r = 0, x = 0, y = 0;
      std::cin >> r;
      std::cin.ignore(1);
      std::cin >> x;
      std::cin.ignore(1);
      std::cin >> y;
      std::cin.ignore(1);
      set.push_back(circle_t{ r, x, y });
    }
    long int threads = 0, tries = 0;
    std::cin >> threads;
    std::cin.ignore(1);
    std::cin >> tries;
    std::cin.ignore(1);

    // std::cerr << "[CHILD] - Threads number is " << threads << "; Tries number is " << tries << "\n";

    std::pair< double, double > results = calculateSetArea(set, tries, threads);
    double cvrg_area = results.first;
    double calc_time = results.second;
    // std::cerr << "AREA CALCULATED: " << cvrg_area << "; TIME ELAPSED: " << calc_time << '\n';
    std::string message;
    serializeResultsToMsg(message, cvrg_area, calc_time);
    std::cout << message.c_str();
  }
  // std::cerr << "[CHILD] - CHILD PROCESS ENDS\n";
}
