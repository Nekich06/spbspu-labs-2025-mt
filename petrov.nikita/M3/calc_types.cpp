#include "calc_types.hpp"

petrov::Calculation::Calculation(const std::string & process_name):
  process_name_(process_name)
{}

petrov::Status petrov::Calculation::getStatus()
{
  return status_;
}

std::string petrov::Calculation::getCalculatorProcessName()
{
  return process_name_;
}

double petrov::Calculation::getCoverageArea()
{
  return cvrg_area_;
}


double petrov::Calculation::getCalculationTime()
{
  return calc_time_;
}

void petrov::Calculation::setCalculatedDataAndChangeStatus(double cvrg_area, double calc_time)
{
  if (status_ == IN_PROGRESS)
  {
    cvrg_area_ = cvrg_area;
    calc_time_ = calc_time;
    status_ = FINISHED;
  }
}
