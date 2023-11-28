#include <gtest/gtest.h>

#include "Strings.h"

using namespace std;

TEST(TestStrings, Replace)
{
    string data = "aaabbbcccaaabbbccc";

    ASSERT_TRUE(utility::strings::replaceAll(data, "aaa", "x") == "xbbbccc");
    ASSERT_TRUE(utility::strings::replaceAll(data, "bbb", "x") == "aaaxccc");
    ASSERT_TRUE(utility::strings::replaceAll(data, "ccc", "x") == "aaabbbx");
    
    utility::strings::replaceAllByRef(data, "aaa", "x");
    utility::strings::replaceAllByRef(data, "bbb", "y");
    utility::strings::replaceAllByRef(data, "ccc", "z");

    ASSERT_TRUE(data == "xyz");
}
