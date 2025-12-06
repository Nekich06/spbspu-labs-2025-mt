#ifndef CALCULATIONS_OF_CIRCLE_AREA
#define CALCULATIONS_OF_CIRCLE_AREA

#include <utility>

namespace petrov
{
	std::pair< double, double > calculateCircleAreaByMonteCarlo(int radius, long long int tries_num, int threads_num);
}

#endif
