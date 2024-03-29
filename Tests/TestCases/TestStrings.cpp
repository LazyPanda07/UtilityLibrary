#include "gtest/gtest.h"

#include "Strings.h"

using namespace std;

TEST(Strings, Replace)
{
    string data = "aaabbbcccaaabbbccc";

    ASSERT_EQ(utility::strings::replaceAll(data, "aaa", "x"), "xbbbcccxbbbccc");
    ASSERT_EQ(utility::strings::replaceAll(data, "bbb", "x"), "aaaxcccaaaxccc");
    ASSERT_EQ(utility::strings::replaceAll(data, "ccc", "x"), "aaabbbxaaabbbx");
    
    utility::strings::replaceAllByRef(data, "aaa", "x");
    utility::strings::replaceAllByRef(data, "bbb", "y");
    utility::strings::replaceAllByRef(data, "ccc", "z");

    ASSERT_EQ(data, "xyzxyz");
}

TEST(Strings, Split)
{
    ASSERT_EQ(utility::strings::split("qwe 123 890 xyz", " ").size(), 4);
    ASSERT_EQ(utility::strings::split("qwe<=>123<=>890<=>xyz", "<=>").size(), 4);
}
