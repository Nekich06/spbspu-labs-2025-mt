#include <random>
#include <string>
#include <iostream>
#include <data_types.hpp>
#include "calculations_of_set_area.hpp"

int main(const int argc, const char * const * argv)
{
  using namespace petrov;
  sets_map sets;
  long int seed = 0, tries = 0, threads = 0;
  size_t circles_num;

  seed = std::stoi(argv[1]);
  std::srand(seed);

  while (!std::cin.eof())
  {
    std::cin >> circles_num;

    circles_map set;
    for (size_t i = 0; i < circles_num; ++i)
    {
      std::string circle_name;
      std::string r_str, x_str, y_str;
      std::getline(std::cin, circle_name, ';');
      std::getline(std::cin, r_str, ';');
      std::getline(std::cin, x_str, ';');
      std::getline(std::cin, y_str, ';');
      int r = std::stoi(r_str, nullptr, 10);
      int x = std::stoi(x_str, nullptr, 10);
      int y = std::stoi(y_str, nullptr, 10);
      set.insert({ circle_name, circle_t{ r, x, y } });
    }
    std::string threads_str, tries_str;
    std::getline(std::cin, threads_str, ';');
    std::getline(std::cin, tries_str, ';');
    threads = std::stoi(threads_str, nullptr, 10);
    tries = std::stoi(tries_str, nullptr, 10);

    std::pair< double, double > results = calculateSetArea(set, tries, threads);
    std::cout << results.first << ';' << results.second << ';';
  }
}
