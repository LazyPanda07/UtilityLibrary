#include "Timers.h"

#ifndef __WITHOUT_TIMERS__
#include <iostream>

static double calculateTime(const std::chrono::high_resolution_clock::time_point& start, utility::timers::OutputTimeType type);

namespace utility::timers
{
	Timer::Timer(OutputTimeType type) :
		output(nullptr),
		type(type),
		start(std::chrono::high_resolution_clock::now())
	{

	}

	Timer::Timer(std::ostream& output, OutputTimeType type) :
		Timer(type)
	{
		this->output = &output;
	}

	double Timer::getCurrentTime() const
	{
		return calculateTime(start, type);
	}

	Timer::~Timer()
	{
		double result = calculateTime(start, type);

		(output ? *output : std::cout) << result;
	}

	AccumulatingTimer::AccumulatingTimer(double& accumulatedTime, OutputTimeType type) :
		accumulatedTime(accumulatedTime),
		type(type),
		start(std::chrono::high_resolution_clock::now())
	{

	}

	double AccumulatingTimer::getCurrentTime() const
	{
		return calculateTime(start, type);
	}

	AccumulatingTimer::~AccumulatingTimer()
	{
		accumulatedTime += calculateTime(start, type);
	}
}

inline double calculateTime(const std::chrono::high_resolution_clock::time_point& start, utility::timers::OutputTimeType type)
{
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

	double resultTime = static_cast<double>((end - start).count());
	intmax_t coeffficient;

	switch (type)
	{
	case utility::timers::OutputTimeType::milliseconds:
		coeffficient = std::chrono::milliseconds::period::den;

		break;

	case utility::timers::OutputTimeType::seconds:
		coeffficient = std::chrono::seconds::period::den;

		break;

	case utility::timers::OutputTimeType::nanoseconds:
		coeffficient = std::chrono::nanoseconds::period::den;

		break;

	case utility::timers::OutputTimeType::minutes:
		coeffficient = std::chrono::minutes::period::den;

		break;

	case utility::timers::OutputTimeType::hours:
		coeffficient = std::chrono::hours::period::den;

		break;

	default:
		std::cerr << "Wrong OutputTimeType" << std::endl;

		return 0.0;
	}

	return resultTime / std::chrono::high_resolution_clock::period::den * coeffficient;
}
#endif
