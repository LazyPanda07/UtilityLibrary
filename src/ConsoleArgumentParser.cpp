#include "ConsoleArgumentParser.h"

#ifndef __WITHOUT_CONSOLE_ARGUMENT_PARSER__
namespace utility::parsers
{
	bool ConsoleArgumentParser::ConstIterator::isBool() const
	{
		if (begin == end)
		{
			return false;
		}

		return begin + 1 == end || (begin + 1)->starts_with("--");
	}

	ConsoleArgumentParser::ConstIterator::ConstIterator(std::vector<std::string_view>::const_iterator begin, std::vector<std::string_view>::const_iterator end) :
		begin(begin),
		end(end)
	{

	}

	std::string_view ConsoleArgumentParser::ConstIterator::key() const
	{
		return *begin;
	}

	ConsoleArgumentParser::ConstIterator ConsoleArgumentParser::ConstIterator::operator *() const noexcept
	{
		return ConstIterator(begin, begin + 1 == end ? end : begin + 2);
	}

	ConsoleArgumentParser::ConstIterator& ConsoleArgumentParser::ConstIterator::operator ++()
	{
		if (begin == end)
		{
			return *this;
		}

		begin += this->isBool() ? 1 : 2;

		return *this;
	}

	bool ConsoleArgumentParser::ConstIterator::operator !=(const ConstIterator& other) const noexcept
	{
		return begin != other.begin;
	}

	std::optional<std::string_view> ConsoleArgumentParser::findValue(std::string_view argumentName) const
	{
		std::vector<std::string_view>::const_iterator it = std::ranges::find(values, argumentName);
		std::optional<std::string_view> result;

		if (it == values.end())
		{
			warnings.emplace_back(std::format("Warning: no value for {}", argumentName));

			return result;
		}

		++it;

		if (it != values.end())
		{
			result = *it;
		}
		else
		{
			warnings.emplace_back(std::format("Warning: no value for {}", argumentName));
		}

		return result;
	}

	ConsoleArgumentParser::ConsoleArgumentParser(int argc, char** argv) :
		currentExecutable(argv[0]),
		argc(argc)
	{
		for (int i = 1; i < argc; i++)
		{
			values.emplace_back(argv[i]);
		}
	}

	int ConsoleArgumentParser::argcSize() const
	{
		return argc;
	}

	size_t ConsoleArgumentParser::size() const
	{
		return std::ranges::count_if(values, [](std::string_view value) { return value.starts_with("--"); });
	}

	std::string_view ConsoleArgumentParser::getCurrentExecutable() const
	{
		return currentExecutable;
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

	ConsoleArgumentParser::ConstIterator ConsoleArgumentParser::begin() const noexcept
	{
		return ConstIterator(values.begin(), values.end());
	}

	ConsoleArgumentParser::ConstIterator ConsoleArgumentParser::end() const noexcept
	{
		return ConstIterator(values.end(), values.end());
	}
}
#endif
