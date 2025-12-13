#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <utility>
#include "../common/data_types.hpp"

namespace petrov
{
  void serializeSetToMsg(std::string & message, const circles_map & set, int threads_num, int tries);
  std::pair< std::string, std::string > serializeResultsToMetadataAndMsg(double cvrg_area, double calc_time);
  std::pair< double, double > deserializeToResults(const std::string & cvrg_area_str, const std::string & calc_time_str);
}

#endif
