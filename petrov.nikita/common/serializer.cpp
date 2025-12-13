#include "serializer.hpp"
#include <string>

void petrov::serializeSetToMsg(std::string & message, const circles_map & set, int threads_num, int tries)
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

std::pair< std::string, std::string > petrov::serializeResultsToMetadataAndMsg(double cvrg_area, double calc_time)
{
  std::string message;
  message += std::to_string(cvrg_area) + ';';
  message += std::to_string(calc_time) + ';';
  std::string metadata = std::to_string(message.size());
  return std::make_pair(metadata, message);
}

std::pair< double, double > petrov::deserializeToResults(const std::string & cvrg_area_str, const std::string & calc_time_str)
{
  return std::make_pair(std::stod(cvrg_area_str), std::stod(calc_time_str));
}

