#include "ConsoleArgumentParser.h"

#ifndef __WITHOUT_CONSOLE_ARGUMENT_PARSER__
#include <format>

namespace utility::parsers
{
	std::optional<std::string_view> ConsoleArgumentParser::findValue(std::string_view argumentName) const
	{
		std::vector<std::string_view>::const_iterator it = std::ranges::find(values, argumentName);
		std::optional<std::string_view> result;

		if (it == values.end())
		{
			warnings.emplace_back(format("Warning: no value for {}", argumentName));

			return result;
		}

		++it;

		if (it != values.end())
		{
			result = *it;
		}
		else
		{
			warnings.emplace_back(format("Warning: no value for {}", argumentName));
		}

		return result;
	}

	ConsoleArgumentParser::ConsoleArgumentParser(int argc, char** argv)
	{
		for (int i = 1; i < argc; i++)
		{
			values.emplace_back(argv[i]);
		}
	}

	std::vector<std::string> ConsoleArgumentParser::getWarnings(bool clearWarnings) const
	{
		std::vector<std::string> result(warnings);

		if (clearWarnings)
		{
			warnings.clear();
		}

		return result;
	}
}
#endif
