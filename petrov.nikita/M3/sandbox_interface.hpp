#ifndef SANDBOX_INTERFACE_HPP
#define SANDBOX_INTERFACE_HPP

#include <map>
#include <iostream>
#include <functional>
#include "../common/geometry.hpp"
#include "../common/data_types.hpp"

namespace petrov
{
	using commands_map = std::map< std::string, std::function< void() > >;

	void createCircle(std::istream & in, circles_map & circles);
	void createSet(std::istream & in, sets_map & sets, const circles_map & circles);

	std::ostream & showShapeInfo(std::ostream & out, std::istream & in, const circles_map & circles);
	std::ostream & showSetInfo(std::ostream & out, std::istream & in, const sets_map & sets);

	std::ostream & showShapeFrame(std::ostream & out, std::istream & in, const circles_map & circles);
	std::ostream & showSetFrame(std::ostream & out, std::istream & in, const sets_map & sets);
}

#endif
