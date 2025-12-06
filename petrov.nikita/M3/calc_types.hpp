#ifndef CALC_TYPES_HPP
#define CALC_TYPES_HPP

#include <string>
#include <unistd.h>
#include <iostream>

namespace petrov
{
  struct Process
  {
    pid_t id;
    int * to_pipe_fds;
    int * from_pipe_fds;
  };

  struct Calculation
  {
    enum Statuses
    {
      IN_PROGRESS,
      FINISHED
    };

    std::string name;
    double calc_time;
    double cvrg_area;

    int getStatus();
  };

  std::ostream & operator<<(std::ostream & out, const Calculation & cs);
}

#endif
