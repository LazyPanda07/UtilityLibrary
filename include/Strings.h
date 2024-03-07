#pragma once

#include <string>
#include <vector>

#include "Defines.h"

namespace utility
{
	namespace strings
	{
		/**
		 * @brief Replace all 'oldValue' substrings with 'newValue'
		 * @param source 
		 * @param oldValue 
		 * @param newValue 
		 * @return New string after replacing
		*/
		UTILITY_LIBRARY_API_FUNCTION std::string replaceAll(const std::string& source, std::string_view oldValue, std::string_view newValue);

		/**
		 * @brief Replace all 'oldValue' substrings with 'newValue'
		 * @param source 
		 * @param oldValue 
		 * @param newValue 
		 * @return Modified source string
		*/
		UTILITY_LIBRARY_API_FUNCTION std::string& replaceAllByRef(std::string& source, std::string_view oldValue, std::string_view newValue);

		/**
		 * @brief Split source with delimiter into vector
		 * @param source 
		 * @param delimiter 
		 * @return 
		*/
#ifdef __LINUX__
		UTILITY_LIBRARY_API_FUNCTION std::vector<std::string> split(const std::string& source, std::string_view delimiter);
#else
		UTILITY_LIBRARY_API std::vector<std::string> split(const std::string& source, std::string_view delimiter);
#endif
		
	}
}
