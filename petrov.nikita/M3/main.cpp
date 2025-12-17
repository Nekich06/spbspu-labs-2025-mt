#include <map>
#include <string>
#include <limits>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <geometry.hpp>
#include "sandbox_interface.hpp"
#include "calculate_interface.hpp"

namespace
{
  using namespace petrov;
	void initCmds(commands_map & cmds, circles_map & circles, sets_map & sets, processes_map & processes, calcs_map & calculations)
	{
		cmds.insert({ "circle", std::bind(createCircle, std::ref(std::cin), std::ref(circles)) });
		cmds.insert({ "set", std::bind(createSet, std::ref(std::cin), std::ref(sets), std::cref(circles)) });
		cmds.insert({ "show", std::bind(showShapeInfo, std::ref(std::cout), std::ref(std::cin), std::cref(circles)) });
		cmds.insert({ "showset", std::bind(showSetInfo, std::ref(std::cout), std::ref(std::cin), std::cref(sets)) });
		cmds.insert({ "frame", std::bind(showShapeFrame, std::ref(std::cout), std::ref(std::cin), std::cref(circles)) });
		cmds.insert({ "frameset", std::bind(showSetFrame, std::ref(std::cout), std::ref(std::cin), std::cref(sets)) });
		cmds.insert({ "spawn", std::bind(spawnProcess, std::ref(std::cin), std::ref(processes))});
		cmds.insert({ "area-on", std::bind(calcAreaOn, std::ref(std::cin), std::cref(processes), std::ref(calculations), std::cref(sets))});
		cmds.insert({ "status", std::bind(getCalculationStatus, std::ref(std::cout), std::ref(std::cin), std::cref(calculations))});
		cmds.insert({ "wait", std::bind(waitResultAndPrint, std::ref(std::cout), std::ref(std::cin), std::cref(processes), std::ref(calculations))});
	}
}

int main()
{
  using namespace petrov;
	commands_map cmds;
	circles_map circles;
	sets_map sets;
  processes_map processes;
  calcs_map calculations;
	initCmds(cmds, circles, sets, processes, calculations);

	std::string command;
	while (!(std::cin >> command).eof())
	{
		try
		{
			cmds.at(command)();
		}
		catch (const std::bad_alloc & e)
		{
			std::cerr << e.what();
			std::cerr << "\n";
			return 1;
		}
		catch (const std::invalid_argument & e)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
			std::cout << e.what();
			std::cout << "\n";
		}
		catch (const std::out_of_range & e)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
			std::cout << "<UNKNOWN COMMAND>";
			std::cout << "\n";
		}
		catch (const std::runtime_error & e)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
			std::cerr << e.what() << strerror(errno) << std::endl;
			return 2;
		}
	}
}
