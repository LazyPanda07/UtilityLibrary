#include <gtest/gtest.h>

#include "ConsoleArgumentParser.h"

using namespace std;

#ifndef NO_CONSOLE_ARGUMENT_PARSER
TEST(ConsoleArgumentParser, GetWarnings)
{
    utility::parsers::ConsoleArgumentParser parser(__argc, __argv);
}

TEST(ConsoleArgumentParser, Get)
{
    utility::parsers::ConsoleArgumentParser parser(__argc, __argv);

    ASSERT_TRUE(parser.get<uint8_t>("--int"));
    ASSERT_TRUE(parser.get<uint16_t>("--int"));
    ASSERT_TRUE(parser.get<uint32_t>("--int"));
    ASSERT_TRUE(parser.get<uint64_t>("--int"));

    ASSERT_TRUE(parser.get<int8_t>("--int"));
    ASSERT_TRUE(parser.get<int16_t>("--int"));
    ASSERT_TRUE(parser.get<int32_t>("--int"));
    ASSERT_TRUE(parser.get<int64_t>("--int"));

    ASSERT_TRUE(parser.get<string>("--string") == "data");

    ASSERT_TRUE(parser.get<bool>("--bool"));

    ASSERT_FALSE(parser.get<bool>("--qwe"));
}

TEST(ConsoleArgumentParser, GetValues)
{
    utility::parsers::ConsoleArgumentParser parser(__argc, __argv);

    ASSERT_TRUE(parser.getValues<int32_t>("--values").size() == 6);
}
#endif // !NO_CONSOLE_ARGUMENT_PARSER
