#include <vector>
#include <queue>
#include <list>

#include "gtest/gtest.h"

#include "Files.h"
#include "Utility.h"

using namespace std;

TEST(Files, ReadFile)
{
    string data = utility::testing::createRandomFile("test.txt");
    ifstream file("test.txt");

    ASSERT_EQ(data, utility::files::readFile("test.txt"));

    ASSERT_EQ(data, utility::files::readFileFromStream(file));

    data = utility::testing::createRandomBinaryFile("test.bin");

    ASSERT_EQ(data, utility::files::readBinaryFile("test.bin"));
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
   
    ASSERT_EQ(utility::files::generatePath("/usr", "stranger", "home", "Downloads"), reference);

    ASSERT_EQ(utility::files::generatePathContainer(vectorPaths), reference);
    ASSERT_EQ(utility::files::generatePathContainer(listPaths), reference);
    ASSERT_EQ(utility::files::generatePathContainer(dequeuePaths), reference);
}
