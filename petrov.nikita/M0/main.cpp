#include <random>
#include <string>
#include <iostream>
#include <data_types.hpp>
#include "calculations_of_set_area.hpp"

int main(const int argc, const char * const * argv)
{
  if (argc != 2)
  {
    return 1;
  }
  using namespace petrov;
  long int seed = 0, tries = 0, threads = 0;
  std::string circles_num_str;

  seed = std::stoi(argv[1]);
  std::srand(seed);

  while (!(std::cin.eof()))
  {
    std::getline(std::cin, circles_num_str, ';');
    size_t circles_num = std::stoul(circles_num_str);
    circles_map set;
    for (size_t i = 0; i < circles_num; ++i)
    {
      std::string circle_name;
      std::string r_str, x_str, y_str;
      std::getline(std::cin, circle_name, ';');
      std::getline(std::cin, r_str, ';');
      std::getline(std::cin, x_str, ';');
      std::getline(std::cin, y_str, ';');
      int r = std::stoi(r_str);
      int x = std::stoi(x_str);
      int y = std::stoi(y_str);
      set.insert({ circle_name, circle_t{ r, x, y } });
    }
    std::string threads_str, tries_str;
    std::getline(std::cin, threads_str, ';');
    std::getline(std::cin, tries_str, ';');
    threads = std::stol(threads_str);
    tries = std::stol(tries_str);

    std::pair< double, double > results = calculateSetArea(set, tries, threads);
    std::cout << results.first << results.second;
  }
}
