#include <string>
#include <fstream>

#include <gtest/gtest.h>

#include "CSVParser.h"
#include "Files.h"

using namespace std;

#ifndef NO_CSV_PARSER
TEST(CSVParser, Constructors)
{
    ifstream file("test.csv");

    ASSERT_NO_THROW(utility::parsers::CSVParser("test.csv"));
    ASSERT_NO_THROW(utility::parsers::CSVParser parser(file));
    ASSERT_NO_THROW(utility::parsers::CSVParser::fromString(utility::files::readFile("test.csv")));
}

TEST(CSVParser, Functionality)
{
    utility::parsers::CSVParser parser("test.csv");

    for (const string& columnName : parser.getColumnNames())
    {
        ASSERT_TRUE(parser[columnName].size());

        for (size_t i = 0; i < parser.size(); i++)
        {
            ASSERT_TRUE(parser[i].size());
        }
    }
}
#endif
