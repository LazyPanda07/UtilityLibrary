#include "ConsoleArgumentParser.h"

#include <algorithm>
#include <format>

using namespace std;

#ifndef NO_CONSOLE_ARGUMENT_PARSER
namespace utility
{
	namespace parsers
	{
		optional<string_view> ConsoleArgumentParser::findValue(string_view argumentName) const
		{
			vector<string_view>::const_iterator it = ranges::find(values, argumentName);
			optional<string_view> result;

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

		vector<string> ConsoleArgumentParser::getWarnings(bool clearWarnings) const
		{
			vector<string> result(warnings);

			if (clearWarnings)
			{
				warnings.clear();
			}

			return result;
		}

		template<>
		bool ConsoleArgumentParser::get(string_view argumentName, const bool& defaultValue, errc* errorCode) const
		{
			return ranges::find(values, argumentName) != values.end() || defaultValue;
		}
	}
}
#endif // !NO_CONSOLE_ARGUMENT_PARSER
