#include "sets_parser.hpp"

void petrov::serializeToMsg(std::string & message, const circles_map & set, int threads_num, int tries)
{
  message += set.size() + ";";
  for (auto it = set.cbegin(); it != set.cend(); ++it)
  {
    message += it->first + ";";
    message += it->second.r + ";";
    message += it->second.x + ";";
    message += it->second.y + ";";
  }
  message += threads_num + ";";
  message += tries + ";";
}
