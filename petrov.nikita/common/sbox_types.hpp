#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <map>
#include <string>

namespace petrov
{
	struct point_t_dbl
	{
		double x, y;
	};

	struct point_t_int
	{
		int x, y;
	};

	struct circle_t
	{
		int r, x, y;
	};

	using circles_map = std::map< std::string, circle_t >;
  using sets_map = std::map< std::string, circles_map >;
}

#endif
