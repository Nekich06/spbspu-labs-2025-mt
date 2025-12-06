#ifndef CALCULATE_INTERFACE_HPP
#define CALCULATE_INTERFACE_HPP

#include <map>
#include <unistd.h>
#include <iostream>
#include "calc_types.hpp"
#include "sandbox_interface.hpp"

namespace petrov
{
  using processes_map = std::map< std::string, Process >;
  using statuses_map = std::map< std::string, Calculation >;

	void spawnProcess(std::istream & in, processes_map & processes);
	void calcAreaOn(std::istream & in, const processes_map & processes, const sets_map & sets);
	std::ostream & getStatus(std::istream & in);
	std::ostream & waitEndOfProcess(std::istream & in);
}

#endif
