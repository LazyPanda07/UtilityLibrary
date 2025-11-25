#include <vector>
#include <queue>
#include <list>

#include "gtest/gtest.h"

#include "Files.h"
#include "Utility.h"

TEST(Files, ReadFile)
{
    std::string data = utility::testing::createRandomFile("test.txt");
    std::ifstream file("test.txt");

    ASSERT_EQ(data, utility::files::readFile("test.txt"));

    ASSERT_EQ(data, utility::files::readFileFromStream(file));

    data = utility::testing::createRandomBinaryFile("test.bin");

    ASSERT_EQ(data, utility::files::readBinaryFile("test.bin"));
}

TEST(Files, GeneratePath)
{
    std::vector<std::string> vectorPaths = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    std::list<std::string> listPaths = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    std::deque<std::string> dequeuePaths = 
    {
        "/usr",
        "stranger",
        "home",
        "Downloads"
    };
    std::filesystem::path reference = std::filesystem::path() / "/usr" / "stranger" / "home" / "Downloads";
   
    ASSERT_EQ(utility::files::generatePath("/usr", "stranger", "home", "Downloads"), reference);

    ASSERT_EQ(utility::files::generatePathContainer(vectorPaths), reference);
    ASSERT_EQ(utility::files::generatePathContainer(listPaths), reference);
    ASSERT_EQ(utility::files::generatePathContainer(dequeuePaths), reference);
}
