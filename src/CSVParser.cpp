#include "CSVParser.h"

#ifndef __WITHOUT_CSV_PARSER__
#include <format>
#include <sstream>

#include "Files.h"
#include "Strings.h"

namespace utility::parsers
{
	void CSVParser::parse(const std::string& data, std::string_view delimiter)
	{
		std::istringstream os(data);
		std::string line;

		std::getline(os, line);

		if (line.empty())
		{
			throw std::runtime_error("No columns");
		}

		for (const std::string& columnName : strings::split(line, delimiter))
		{
			csvData.emplace_back(columnName, std::vector<std::string>());
		}

		while (std::getline(os, line))
		{
			if (line.empty())
			{
				continue;
			}

			std::vector<std::string> columns = strings::split(line, delimiter);

			for (size_t i = 0; i < csvData.size(); i++)
			{
				csvData[i].second.emplace_back(std::move(columns.at(i)));
			}
		}
	}

	CSVParser CSVParser::fromString(const std::string& csvData, std::string_view delimiter)
	{
		CSVParser result;

		result.parse(csvData, delimiter);

		return result;
	}

	CSVParser::CSVParser(const std::filesystem::path& pathToCSVFile, std::string_view delimiter)
	{
		this->parse(files::readFile(pathToCSVFile), delimiter);
	}

	CSVParser::CSVParser(std::ifstream& csvFile, std::string_view delimiter)
	{
		this->parse(files::readFileFromStream(csvFile), delimiter);
	}

	size_t CSVParser::size() const
	{
		return csvData.back().second.size();
	}
	
	std::vector<std::string> CSVParser::getColumnNames() const
	{
		std::vector<std::string> result;

		for (const auto& [columnName, _] : csvData)
		{
			result.push_back(columnName);
		}

		return result;
	}

	const std::vector<std::string>& CSVParser::operator[](const std::string& columnName) const
	{
		auto it = std::ranges::find_if(csvData, [&columnName](const std::pair<std::string, std::vector<std::string>>& data) { return data.first == columnName; });

		if (it == csvData.end())
		{
			throw std::runtime_error(format("Wrong column name: {}", columnName));
		}

		return it->second;
	}

	std::vector<std::string> CSVParser::operator[](size_t index) const
	{
		std::vector<std::string> result;

		for (const auto& [_, csv] : csvData)
		{
			result.emplace_back(csv.at(index));
		}

		return result;
	}
}
#endif
