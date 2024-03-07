#pragma once

#include <filesystem>
#include <string>

namespace utility
{
    namespace testing
    {
        std::string createRandomFile(const std::filesystem::path& pathToFile, size_t size = 1024);

        std::string createRandomBinaryFile(const std::filesystem::path& pathToFile, size_t size = 1024);
    }
}
