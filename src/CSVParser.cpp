#include "CSVParser.h"

#ifndef NO_CSV_PARSER
#include <format>
#include <sstream>

#include "Files.h"
#include "Strings.h"

using namespace std;

namespace utility
{
	namespace parsers
	{
		void CSVParser::parse(const string& data, string_view delimiter)
		{
			istringstream os(data);
			string line;

			getline(os, line);

			if (line.empty())
			{
				throw runtime_error("No columns");
			}

			for (const string& columnName : strings::split(line, delimiter))
			{
				csvData.emplace_back(columnName, vector<string>());
			}

			while (getline(os, line))
			{
				if (line.empty())
				{
					continue;
				}

				vector<string> columns = strings::split(line, delimiter);

				for (size_t i = 0; i < csvData.size(); i++)
				{
					csvData[i].second.push_back(move(columns.at(i)));
				}
			}
		}

		CSVParser CSVParser::fromString(const string& csvData, string_view delimiter)
		{
			CSVParser result;

			result.parse(csvData, delimiter);

			return result;
		}

		CSVParser::CSVParser(const filesystem::path& pathToCSVFile, string_view delimiter)
		{
			this->parse(files::readFile(pathToCSVFile), delimiter);
		}

		CSVParser::CSVParser(ifstream& csvFile, string_view delimiter)
		{
			this->parse(files::readFileFromStream(csvFile), delimiter);
		}

		size_t CSVParser::size() const
		{
			return csvData.back().second.size();
		}

		vector<string> CSVParser::getColumnNames() const
		{
			vector<string> result;

			for (const auto& [columnName, _] : csvData)
			{
				result.push_back(columnName);
			}

			return result;
		}

		const vector<string>& CSVParser::operator[](const string& columnName) const
		{
			auto it = ranges::find_if(csvData, [&columnName](const pair<string, vector<string>>& data) { return data.first == columnName; });

			if (it == csvData.end())
			{
				throw runtime_error(format("Wrong column name: {}", columnName));
			}

			return it->second;
		}

		vector<string> CSVParser::operator[](size_t index) const
		{
			vector<string> result;

			for (const auto& [_, csv] : csvData)
			{
				result.push_back(csv.at(index));
			}

			return result;
		}
	}
}
#endif
