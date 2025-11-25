#pragma once

#ifndef __WITHOUT_CONSOLE_ARGUMENT_PARSER__
#include <vector>
#include <string>
#include <optional>
#include <charconv>
#include <cstdint>
#include <algorithm>

#include "Defines.h"

namespace utility::parsers
{
	/**
	 * @brief Console argument parser
	*/
	class UTILITY_LIBRARY_API ConsoleArgumentParser
	{
	private:
		std::vector<std::string_view> values;
		mutable std::vector<std::string> warnings;

	private:
		std::optional<std::string_view> findValue(std::string_view argumentName) const;

		template<typename T>
		T getNumeric(std::string_view integralValue, const T& defaultValue = T(), std::errc* errorCode = nullptr) const;

	public:
		ConsoleArgumentParser(int argc, char** argv);

		/**
		 * @brief Get warnings from get and getValues
		 * @param clearWarnings Clear previous warnings
		 * @return
		*/
		std::vector<std::string> getWarnings(bool clearWarnings = true) const;

		/**
		 * @brief Get command line value
		 * @tparam T
		 * @param argumentName
		 * @param defaultValue Returned value if can't find argumentName
		 * @param errorCode Conversion error
		 * @return
		*/
		template<typename T>
		T get(std::string_view argumentName, const T& defaultValue = T(), std::errc* errorCode = nullptr) const;

		/**
		 * @brief Get all command line values with same argument name
		 * @tparam T
		 * @param argumentName
		 * @return
		*/
		template<typename T>
		std::vector<T> getValues(std::string_view argumentName) const;

		~ConsoleArgumentParser() = default;
	};
}

#include "ConsoleArgumentParser.inl"
#endif
