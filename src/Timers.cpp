#include "Timers.h"

#include <iostream>

using namespace std;

double calculateTime(const chrono::high_resolution_clock::time_point& start, utility::timers::OutputTimeType type);

namespace utility
{
	namespace timers
	{
		Timer::Timer(OutputTimeType type) :
			output(nullptr),
			type(type),
			start(chrono::high_resolution_clock::now())
		{
			chrono::steady_clock::period::den;
		}

		Timer::Timer(ostream& output, OutputTimeType type) :
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

			(output ? *output : cout) << result;
		}

		AccumulatingTimer::AccumulatingTimer(double& accumulatedTime, OutputTimeType type) :
			accumulatedTime(accumulatedTime),
			type(type),
			start(chrono::high_resolution_clock::now())
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
}

__forceinline double calculateTime(const chrono::high_resolution_clock::time_point& start, utility::timers::OutputTimeType type)
{
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

	double resultTime = static_cast<double>((end - start).count());
	intmax_t coeffficient;

	switch (type)
	{
	case utility::timers::OutputTimeType::milliseconds:
		coeffficient = chrono::milliseconds::period::den;

		break;

	case utility::timers::OutputTimeType::seconds:
		coeffficient = chrono::seconds::period::den;

		break;

	case utility::timers::OutputTimeType::nanoseconds:
		coeffficient = chrono::nanoseconds::period::den;

		break;

	case utility::timers::OutputTimeType::minutes:
		coeffficient = chrono::minutes::period::den;

		break;

	case utility::timers::OutputTimeType::hours:
		coeffficient = chrono::hours::period::den;

		break;

	default:
		cerr << "Wrong OutputTimeType" << endl;

		return 0.0;
	}

	return resultTime / chrono::high_resolution_clock::period::den * coeffficient;
}
