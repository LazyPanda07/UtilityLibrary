#include <gtest/gtest.h>

#include "ConsoleArgumentParser.h"
#include "Arguments.h"

using namespace std;

#ifndef NO_CONSOLE_ARGUMENT_PARSER
TEST(ConsoleArgumentParser, GetWarnings)
{
    static constexpr size_t warnings = 4;
    utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);

    for (size_t i = 0; i < warnings; i++)
    {
        parser.get<int>("--test");   
    }

    ASSERT_TRUE(parser.getWarnings().size() == warnings);
    ASSERT_TRUE(parser.getWarnings().empty());

    for (size_t i = 0; i < warnings; i++)
    {
        parser.get<int>("--test");   
    }

    ASSERT_TRUE(parser.getWarnings(false).size() == parser.getWarnings(false).size());
}

TEST(ConsoleArgumentParser, Get)
{
    utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);

    ASSERT_TRUE(parser.get<uint8_t>("--int"));
    ASSERT_TRUE(parser.get<uint16_t>("--int"));
    ASSERT_TRUE(parser.get<uint32_t>("--int"));
    ASSERT_TRUE(parser.get<uint64_t>("--int"));

    ASSERT_TRUE(parser.get<int8_t>("--int"));
    ASSERT_TRUE(parser.get<int16_t>("--int"));
    ASSERT_TRUE(parser.get<int32_t>("--int"));
    ASSERT_TRUE(parser.get<int64_t>("--int"));

    ASSERT_TRUE(parser.get<float>("--float"));
    ASSERT_TRUE(parser.get<double>("--float"));

    ASSERT_TRUE(parser.get<string>("--string") == "data");

    ASSERT_TRUE(parser.get<bool>("--bool"));

    ASSERT_FALSE(parser.get<bool>("--qwe"));
}

TEST(ConsoleArgumentParser, GetValues)
{
    utility::parsers::ConsoleArgumentParser parser(globalArgc, globalArgv);

    ASSERT_TRUE(parser.getValues<int32_t>("--values").size() == 6);
}
#endif // !NO_CONSOLE_ARGUMENT_PARSER
