#include <gtest/gtest.h>

#include "Strings.h"

using namespace std;

TEST(Strings, Replace)
{
    string data = "aaabbbcccaaabbbccc";

    ASSERT_TRUE(utility::strings::replaceAll(data, "aaa", "x") == "xbbbcccxbbbccc");
    ASSERT_TRUE(utility::strings::replaceAll(data, "bbb", "x") == "aaaxcccaaaxccc");
    ASSERT_TRUE(utility::strings::replaceAll(data, "ccc", "x") == "aaabbbxaaabbbx");
    
    utility::strings::replaceAllByRef(data, "aaa", "x");
    utility::strings::replaceAllByRef(data, "bbb", "y");
    utility::strings::replaceAllByRef(data, "ccc", "z");

    ASSERT_TRUE(data == "xyzxyz");
}
