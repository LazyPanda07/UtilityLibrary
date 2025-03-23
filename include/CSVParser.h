#pragma once

#ifndef NO_CSV_PARSER
#include <filesystem>
#include <fstream>
#include <vector>

#include "Defines.h"

namespace utility::parsers
{
	/**
	 * @brief CSV files parser
	*/
	class UTILITY_LIBRARY_API CSVParser
	{
	private:
		std::vector<std::pair<std::string, std::vector<std::string>>> csvData;

	private:
		void parse(const std::string& data, std::string_view delimiter);

	private:
		CSVParser() = default;

	public:
		/**
		 * @brief Create CSVParser from csv file data
		 * @param csvData
		 * @param delimiter
		 * @return
		 * @exception std::runtime_error
		*/
		static CSVParser fromString(const std::string& csvData, std::string_view delimiter = ",");

	public:
		/**
		 * @brief
		 * @param pathToCSVFile
		 * @param delimiter
		 * @exception std::runtime_error
		*/
		CSVParser(const std::filesystem::path& pathToCSVFile, std::string_view delimiter = ",");

		/**
		 * @brief
		 * @param csvFile
		 * @param delimiter
		 * @exception std::runtime_error
		*/
		CSVParser(std::ifstream& csvFile, std::string_view delimiter = ",");

		/**
		 * @brief Amount of rows
		 * @return
		*/
		size_t size() const;

		/**
		 * @brief Get column names
		 * @return
		*/
		std::vector<std::string> getColumnNames() const;

		/**
		 * @brief Column getter
		 * @param columnName
		 * @return
		*/
		const std::vector<std::string>& operator[](const std::string& columnName) const;

		/**
		 * @brief Row getter
		 * @param index
		 * @return
		*/
		std::vector<std::string> operator[](size_t index) const;

		~CSVParser() = default;
	};
}
#endif // NO_CSV_PARSER
