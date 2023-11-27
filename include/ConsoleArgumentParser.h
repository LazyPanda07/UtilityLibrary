#pragma once

#include <vector>
#include <string>
#include <optional>
#include <charconv>

#ifndef NO_CONSOLE_ARGUMENT_PARSER
namespace utility
{
	namespace parsers
	{
		class ConsoleArgumentParser
		{
		private:
			std::vector<std::string_view> values;
			mutable std::vector<std::string> warnings;

		private:
			std::optional<std::string_view> findValue(std::string_view argumentName) const;

			template<typename T>
			T getIntegral(std::string_view integralValue, const T& defaultValue, std::errc* errorCode) const;

		public:
			ConsoleArgumentParser(int argc, char** argv);

			std::vector<std::string> getWarnings(bool clearWarnings = true) const;

			template<typename T>
			T get(std::string_view argumentName, const T& defaultValue = {}, std::errc* errorCode = nullptr) const;

			template<typename T>
			std::vector<T> getValues(std::string_view argumentName) const;

			~ConsoleArgumentParser() = default;
		};
	}
}

#endif // !NO_CONSOLE_ARGUMENT_PARSER

#include "ConsoleArgumentParser.inl"
