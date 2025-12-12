#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <map>
#include <string>
#include "geometry.hpp"

namespace petrov
{
  using circles_map = std::map< std::string, petrov::circle_t >;
  using sets_map = std::map< std::string, circles_map >;
}

#endif
