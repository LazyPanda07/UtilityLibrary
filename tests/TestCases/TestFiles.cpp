#include <gtest/gtest.h>

#include "Files.h"

using namespace std;

TEST(Files, GeneratePath)
{
    vector<string> path = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    filesystem::path reference = filesystem::path() / "/usr" / "stranger" / "home" / "Downloads";

    ASSERT_TRUE(utility::files::generatePath("/usr", "stranger", "home", "Downloads") == reference);

    ASSERT_TRUE(utility::files::generatePath(path) == reference);
}
