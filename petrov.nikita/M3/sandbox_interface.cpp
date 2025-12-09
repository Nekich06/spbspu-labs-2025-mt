#include "sandbox_interface.hpp"
#include <algorithm>

namespace
{
	std::ostream & printShapeInfo(std::ostream & out, const petrov::circle_t & circle)
	{
		out << circle.r;
		out << " (";
		out << circle.x;
		out << " ";
		out << circle.y;
		out << ")";
		out << "\n";
		return out;
	}

	std::ostream & printFrame(std::ostream & out, const petrov::point_t_int & l, const petrov::point_t_int & r)
	{
		out << "(" << l.x;
		out << " " << l.y;
		out << ")" << " ";
		out << "(" << r.x;
		out << " " << r.y;
		out << ")" << "\n";
		return out;
	}
}

void petrov::createCircle(std::istream & in, circles_map & circles)
{
	std::string name;
	int radius = 0, x = 0, y = 0;
	if (!(in >> name >> radius >> x >> y))
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}
	try
	{
		circles.insert({ name, circle_t{ radius, x, y } });
	}
	catch (const std::bad_alloc & e)
	{
		throw std::bad_alloc();
	}
}

void petrov::createSet(std::istream & in, sets_map & sets, const circles_map & circles)
{
	std::string set_name;
	size_t set_size = 0;
	if (!(in >> set_name >> set_size))
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}

	circles_map set;
	std::string circle_name;
	try
	{
		for (size_t i = 0; i < set_size; ++i)
		{
			in >> circle_name;
			set.insert({ circle_name, circles.at(circle_name) });
		}
	}
	catch (const std::bad_alloc & e)
	{
		throw std::bad_alloc();
	}
	catch (const std::out_of_range & e)
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}
	sets.insert({ set_name, set });
}

std::ostream & petrov::showShapeInfo(std::ostream & out, std::istream & in, const circles_map & circles)
{
	std::string name;
	in >> name;
	try
	{
		circle_t requested = circles.at(name);
		printShapeInfo(out, requested);
	}
	catch (const std::out_of_range & e)
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}
	return out;
}

std::ostream & petrov::showSetInfo(std::ostream & out, std::istream & in, const sets_map & sets)
{
	std::string name;
	in >> name;
	try
	{
		circles_map requested = sets.at(name);
		for (auto it = requested.cbegin(); it != requested.cend(); ++it)
		{
			printShapeInfo(out, it->second);
		}
	}
	catch (const std::out_of_range & e)
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}
	return out;
}

std::ostream & petrov::showShapeFrame(std::ostream & out, std::istream & in, const circles_map & circles)
{
	std::string name;
	in >> name;
	try
	{
		circle_t requested = circles.at(name);
		point_t_int left{ requested.x - requested.r, requested.y - requested.r };
		point_t_int right{ requested.x + requested.r, requested.y + requested.r };
		printFrame(out, left, right);
	}
	catch (const std::out_of_range & e)
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}
	return out;
}

std::ostream & petrov::showSetFrame(std::ostream & out, std::istream & in, const sets_map & sets)
{
	std::string name;
	in >> name;
	try
	{
		circles_map requested = sets.at(name);
		point_t_int left_min{ 0, 0 };
		point_t_int right_max{ 0, 0 };
		for (auto it = requested.cbegin(); it != requested.cend(); ++it)
		{
			left_min.x = std::min(left_min.x, it->second.x - it->second.r);
			left_min.y = std::min(left_min.x, it->second.y - it->second.r);
			right_max.x = std::max(right_max.x, it->second.x + it->second.r);
			right_max.y = std::max(right_max.x, it->second.y + it->second.r);
		}
		printFrame(out, left_min, right_max);
	}
	catch (const std::out_of_range & e)
	{
		throw std::invalid_argument("<INVALID COMMAND>");
	}
	return out;
}
