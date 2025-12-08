#ifndef SETS_PARSER_HPP
#define SETS_PARSER_HPP

#include <data_types.hpp>

namespace petrov
{
  void serializeToMsg(std::string & message, const petrov::circles_map & set, int threads_num, int tries);
  std::pair< double, double > deserializeToResults(char * message);
}

#endif
