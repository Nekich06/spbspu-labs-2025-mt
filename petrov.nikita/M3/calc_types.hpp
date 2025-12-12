#ifndef CALC_TYPES_HPP
#define CALC_TYPES_HPP

#include <string>
#include <unistd.h>
#include <iostream>

namespace petrov
{
  struct Process
  {
    int to_pipe_fd;
    int from_pipe_fd;
  };

  enum Status
  {
    IN_PROGRESS,
    FINISHED
  };

  struct Calculation
  {
    Status status;
    std::string process_name;
    double calc_time;
    double cvrg_area;

    int getStatus();
  };

  std::ostream & operator<<(std::ostream & out, const Calculation & cs);
}

#endif
