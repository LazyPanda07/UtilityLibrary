#include "Utility.h"

#include <fstream>
#include <chrono>
#include <random>

using namespace std;

static mt19937 random(time(nullptr));

namespace utility
{
    namespace testing
    {
        string createRandomFile(const filesystem::path& pathToFile, size_t size)
        {
            string result;
            vector<char> alphabet;
            ofstream file(pathToFile);

            for (char c = 'A'; c <= 'Z'; c++)
            {
                alphabet.push_back(c);
            }

            for (char c = 'a'; c <= 'z'; c++)
            {
                alphabet.push_back(c);
            }

            for (size_t i = 0; i < size; i++)
            {
                result += alphabet[random() % alphabet.size()];
            }

            file << result;

            return result;
        }

        string createRandomBinaryFile(const filesystem::path& pathToFile, size_t size)
        {
            string result;
            ofstream file(pathToFile, ios::binary);

            for (size_t i = 0; i < size; i++)
            {
                result += static_cast<char>(random() % 255);
            }
            
            file << result;

            return result;
        }
    }
}
