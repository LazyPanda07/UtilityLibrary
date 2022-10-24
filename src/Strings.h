#pragma once

#include <string>

#include "defines.h"

namespace utility
{
	namespace strings
	{
		/// @brief Replace all 'oldValue' substrings with 'newValue'
		/// @param source 
		/// @param oldValue 
		/// @param newValue 
		/// @return New string after replacing
		UTILITY_LIBRARY_API std::string replaceAll(const std::string& source, std::string_view oldValue, std::string_view newValue);

		/// @brief Replace all 'oldValue' substrings with 'newValue'
		/// @param source 
		/// @param oldValue 
		/// @param newValue 
		/// @return Modified source string
		UTILITY_LIBRARY_API std::string& replaceAllByRef(std::string& source, std::string_view oldValue, std::string_view newValue);
	}
}
