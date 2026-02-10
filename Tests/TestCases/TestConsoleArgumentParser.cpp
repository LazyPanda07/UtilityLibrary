#include "gtest/gtest.h"

#include "ConsoleArgumentParser.h"
#include "Arguments.h"

#ifndef __WITHOUT_CONSOLE_ARGUMENT_PARSER__
TEST(ConsoleArgumentParser, GetWarnings)
{
	static constexpr size_t warnings = 4;
	utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);

	for (size_t i = 0; i < warnings; i++)
	{
		parser.get<int>("test");
	}

	ASSERT_EQ(parser.getWarnings().size(), warnings);
	ASSERT_TRUE(parser.getWarnings().empty());

	for (size_t i = 0; i < warnings; i++)
	{
		parser.get<int>("test");
	}

	ASSERT_EQ(parser.getWarnings(false).size(), parser.getWarnings(false).size());
}

TEST(ConsoleArgumentParser, Get)
{
	utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);

	ASSERT_EQ(parser.get<uint8_t>("int"), static_cast<uint8_t>(1));
	ASSERT_EQ(parser.get<uint16_t>("int"), 1);
	ASSERT_EQ(parser.get<uint32_t>("int"), 1);
	ASSERT_EQ(parser.get<uint64_t>("int"), 1);

	ASSERT_EQ(parser.get<int8_t>("int"), static_cast<int8_t>(1));
	ASSERT_EQ(parser.get<int16_t>("int"), 1);
	ASSERT_EQ(parser.get<int32_t>("int"), 1);
	ASSERT_EQ(parser.get<int64_t>("int"), 1);

	ASSERT_EQ(parser.get<float>("float"), 5.5f);
	ASSERT_EQ(parser.get<double>("float"), 5.5);

	ASSERT_TRUE(parser.get<std::string>("string") == "data");

	ASSERT_TRUE(parser.get<bool>("bool"));

	ASSERT_FALSE(parser.get<bool>("wrong_parameter"));

	ASSERT_EQ(parser.get<uint8_t>("wrong_parameter", static_cast<uint8_t>(5)), static_cast<uint8_t>(5));
	ASSERT_EQ(parser.get<uint16_t>("wrong_parameter", 5), 5);
	ASSERT_EQ(parser.get<uint32_t>("wrong_parameter", 5), 5);
	ASSERT_EQ(parser.get<uint64_t>("wrong_parameter", 5), 5);

	ASSERT_EQ(parser.get<int8_t>("wrong_parameter", static_cast<int8_t>(5)), static_cast<int8_t>(5));
	ASSERT_EQ(parser.get<int16_t>("wrong_parameter", 5), 5);
	ASSERT_EQ(parser.get<int32_t>("wrong_parameter", 5), 5);
	ASSERT_EQ(parser.get<int64_t>("wrong_parameter", 5), 5);

	ASSERT_EQ(parser.get<float>("wrong_parameter", 5.5f), 5.5f);
	ASSERT_EQ(parser.get<double>("wrong_parameter", 5.5), 5.5);

	ASSERT_EQ(parser.get<std::string>("wrong_parameter", "data"), "data");

	ASSERT_TRUE(parser.get<bool>("wrong_parameter", true));
}

TEST(ConsoleArgumentParser, GetValues)
{
	utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);

	ASSERT_EQ(parser.getValues<int32_t>("values").size(), 6);
}

TEST(ConsoleArgumentParser, ForEach)
{
	constexpr std::string_view testData = "--int=1--string=data--bool=--float=5.5--values=1--values=2--values=3--values=4--values=5--values=6";

	utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);
	std::string result;

	for (const auto& it : parser)
	{
		result += std::format("{}={}", it.key(), it.value());
	}

	ASSERT_EQ(result, testData);
}

TEST(ConsoleArgumentParser, Iterators)
{
	utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);
	auto it = parser.begin();
	auto end = parser.end();

	constexpr bool test = std::unsigned_integral<int64_t>;

	ASSERT_EQ(it.key(), "--int");
	ASSERT_EQ(it.value<int>(), 1);

	++it;

	ASSERT_EQ(it.key(), "--string");
	ASSERT_EQ(it.value<std::string>(), "data");

	++it;

	ASSERT_EQ(it.key(), "--bool");
	ASSERT_EQ(it.value<bool>(), true);

	++it;

	ASSERT_EQ(it.key(), "--float");
	ASSERT_EQ(it.value<double>(), 5.5);

	++it;

	for (size_t i = 0; i < 6; i++, ++it)
	{
		ASSERT_EQ(it.key(), "--values");
		ASSERT_EQ(it.value<int>(), i + 1);
	}

	ASSERT_EQ(it, end);
}
#endif // !WITHOUT_CONSOLE_ARGUMENT_PARSER
