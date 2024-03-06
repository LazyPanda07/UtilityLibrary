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

			ifstream file(pathToFile, mode);

			return readFileFromStream(file);
		}

		string readBinaryFile(const filesystem::path& pathToFile)
		{
			return readFile(pathToFile, ios::binary);
		}

		string readFileFromStream(ifstream& file)
		{
			if (!file.good())
			{
				throw runtime_error("Input file stream error");
			}

			if (!file.is_open())
			{
				throw runtime_error("Input file stream is closed");
			}

			return (ostringstream() << file.rdbuf()).str();
		}
	}
}
