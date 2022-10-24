#pragma once

#include <string>

namespace utility
{
	namespace strings
	{
		/// @brief Replace all 'oldValue' substrings with 'newValue'
		/// @param source 
		/// @param oldValue 
		/// @param newValue 
		/// @return New string after replacing
		std::string replaceAll(const std::string& source, std::string_view oldValue, std::string_view newValue);

		/// @brief Replace all 'oldValue' substrings with 'newValue'
		/// @param source 
		/// @param oldValue 
		/// @param newValue 
		/// @return Modified source string
		std::string& replaceAllRef(std::string& source, std::string_view oldValue, std::string_view newValue);
	}
}
