#include "sets_parser.hpp"
#include <string>

void petrov::serializeToMsg(std::string & message, const circles_map & set, int threads_num, int tries)
{
  message += std::to_string(set.size()) + ';';
  for (auto it = set.cbegin(); it != set.cend(); ++it)
  {
    message += std::to_string(it->second.r) + ';';
    message += std::to_string(it->second.x) + ';';
    message += std::to_string(it->second.y) + ';';
  }
  message += std::to_string(threads_num) + ';';
  message += std::to_string(tries) + ';';
}

std::pair< double, double > petrov::deserializeToResults(char * message)
{
  std::string cvrg_area_str;
  std::string calc_time_str;
  size_t i = 0;
  while (message[i] != ';')
  {
    cvrg_area_str += message[i++];
  }
  ++i;
  while (message[i] != ';')
  {
    calc_time_str += message[i++];
  }
  return std::make_pair(std::stod(cvrg_area_str), std::stod(calc_time_str));
}

