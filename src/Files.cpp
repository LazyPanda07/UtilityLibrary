#include "Files.h"

#include <format>
#include <sstream>

namespace utility::files
{
	std::string readFile(const std::filesystem::path& pathToFile, std::ios::openmode mode)
	{
		if (!std::filesystem::exists(pathToFile))
		{
			throw std::runtime_error(format("File {} doesn't exist", pathToFile.string()));
		}

		std::ifstream file(pathToFile, mode);

		return readFileFromStream(file);
	}

	std::string readBinaryFile(const std::filesystem::path& pathToFile)
	{
		return readFile(pathToFile, std::ios::binary);
	}

	std::string readFileFromStream(std::ifstream& file)
	{
		if (!file.good())
		{
			throw std::runtime_error("Input file stream error");
		}

		if (!file.is_open())
		{
			throw std::runtime_error("Input file stream is closed");
		}

		return (std::ostringstream() << file.rdbuf()).str();
	}
}
