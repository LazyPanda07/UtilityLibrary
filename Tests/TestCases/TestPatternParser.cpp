#include <gtest/gtest.h>

#ifndef __WITHOUT_PATTERN_PARSER__

#include "PatternParser.h"

template<>
struct utility::parsers::Converter<int>
{
	void convert(std::string_view data, int& result)
	{
		result = std::stoi(data.data());
	}
};

template<>
struct utility::parsers::Converter<std::string>
{
	void convert(std::string_view data, std::string& result)
	{
		result = data;
	}
};

TEST(PatternParser, Common)
{
	utility::parsers::PatternParser<int, std::string> parser(".NETCoreApp,Version=v{}.0/{}");
	int version = 0;
	std::string platform;

	parser.parse(".NETCoreApp,Version=v8.0/win-x64", version, platform);

	ASSERT_EQ(version, 8);
	ASSERT_EQ(platform, "win-x64");
}

#endif
