#include <gtest/gtest.h>

#include <vector>
#include <queue>

#include "Files.h"
#include "Utility.h"

using namespace std;

TEST(Files, ReadFile)
{
    string data = utility::testing::createRandomFile("test.txt");

    ASSERT_TRUE(data == utility::files::readFile("test.txt"));

    data = utility::testing::createRandomBinaryFile("test.bin");

    ASSERT_TRUE(data == utility::files::readBinaryFile("test.bin"));
}

TEST(Files, GeneratePath)
{
    vector<string> vectorPaths = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    list<string> listPaths = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    deque<string> dequeuePaths = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    filesystem::path reference = filesystem::path() / "/usr" / "stranger" / "home" / "Downloads";
   
    ASSERT_TRUE(utility::files::generatePath("/usr", "stranger", "home", "Downloads") == reference);

    ASSERT_TRUE(utility::files::generatePathContainer(vectorPaths) == reference);
    ASSERT_TRUE(utility::files::generatePathContainer(listPaths) == reference);
    ASSERT_TRUE(utility::files::generatePathContainer(dequeuePaths) == reference);
}
