#ifndef CALCULATE_INTERFACE_HPP
#define CALCULATE_INTERFACE_HPP

#include <map>
#include <iostream>
#include <sbox_types.hpp>
#include "calc_types.hpp"

namespace petrov
{
  using processes_map = std::map< std::string, Process >;
  using calcs_map = std::map< std::string, Calculation >;

	void spawnProcess(std::istream & in, processes_map & processes);
	void calcAreaOn(std::istream & in, const processes_map & processes, calcs_map & calcs, const sets_map & sets);
	std::ostream & getCalculationStatus(std::ostream & out, std::istream & in, const calcs_map & calcs);
	std::ostream & waitResultAndPrint(std::ostream & out, std::istream & in, const processes_map & processes, calcs_map & calcs);
}

#endif
