#pragma once

#ifndef __WITHOUT_TIMERS__
#include <chrono>

#include "Defines.h"

namespace utility::timers
{
	/**
	 * @brief Output time units
	 */
	enum class OutputTimeType
	{
		milliseconds,
		seconds,
		nanoseconds,
		minutes,
		hours
	};

	/**
	 * @brief Calculate time
	*/
	class UTILITY_LIBRARY_API Timer
	{
	private:
		std::ostream* output;
		OutputTimeType type;
		std::chrono::high_resolution_clock::time_point start;

	public:
		/**
		 * @brief Return calculation time result into std::cout stream
		 * @param type
		*/
		Timer(OutputTimeType type = OutputTimeType::milliseconds);

		/**
		 * @brief Return calculation time result into output stream
		 * @param output
		 * @param type
		*/
		Timer(std::ostream& output, OutputTimeType type = OutputTimeType::milliseconds);

		/**
		 * @brief Get current time
		 * @return
		*/
		double getCurrentTime() const;

		~Timer();
	};

	/**
	 * @brief Accumulate calculation time
	*/
	class UTILITY_LIBRARY_API AccumulatingTimer
	{
	private:
		double& accumulatedTime;
		OutputTimeType type;
		std::chrono::high_resolution_clock::time_point start;

	public:
		AccumulatingTimer(double& accumulatedTime, OutputTimeType type = OutputTimeType::milliseconds);

		/**
		 * @brief Get current time
		 * @return
		*/
		double getCurrentTime() const;

		~AccumulatingTimer();
	};
}
#endif
