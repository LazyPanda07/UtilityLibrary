#include "Files.h"

#include <format>

using namespace std;

namespace utility
{
	namespace files
	{
		string readFile(const filesystem::path& pathToFile, ios::openmode mode)
		{
			if (!filesystem::exists(pathToFile))
			{
				throw runtime_error(format("File {} doesn't exist", pathToFile.string()));
			}

			return (ostringstream() << ifstream(pathToFile, mode).rdbuf()).str();
		}

		string readBinaryFile(const filesystem::path& pathToFile)
		{
			return readFile(pathToFile, ios::binary);
		}
	}
}
