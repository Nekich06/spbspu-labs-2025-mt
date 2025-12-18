#ifndef CALC_TYPES_HPP
#define CALC_TYPES_HPP

#include <string>
#include "posix_api_handle.hpp"

namespace petrov
{
  struct Process
  {
    PosixApiHandle to_pipe_fd;
    PosixApiHandle from_pipe_fd;
  };

  struct Calculation
  {
    enum Status
    {
      IN_PROGRESS,
      FINISHED
    };

    Calculation(const std::string & process_name);

    Status getStatus() const;
    std::string getCalculatorProcessName() const;
    double getCoverageArea() const;
    double getCalculationTime() const;
    void setCalculatedDataAndChangeStatus(double cvrg_area, double calc_time);

  private:
    Status status_ = IN_PROGRESS;
    const std::string process_name_;
    double cvrg_area_ = 0.0;
    double calc_time_ = 0.0;
  };
}

#endif
