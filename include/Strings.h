#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Defines.h"

namespace utility::strings
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
	UTILITY_LIBRARY_API_FUNCTION std::vector<std::string> split(std::string_view source, std::string_view delimiter);
#else
	UTILITY_LIBRARY_API std::vector<std::string> split(std::string_view source, std::string_view delimiter);
#endif

	/**
	 * @brief std::string_view hash for std::unordered_map std::string key
	 */
	struct UTILITY_LIBRARY_API StringViewHash
	{
		using is_transparent = void;

		size_t operator ()(std::string_view value) const;
	};

	/**
	 * @brief std::string_view equal operator for std::unordered_map std::string key
	 */
	struct UTILITY_LIBRARY_API StringViewEqual
	{
		using is_transparent = void;

		bool operator ()(std::string_view left, std::string_view right) const;
	};

	/**
	 * @brief Simplify std::unordered_map with std::string key
	 * @tparam T std::unordered_map value
	 */
	template<typename T>
	using string_based_unordered_map = std::unordered_map<std::string, T, StringViewHash, StringViewEqual>;
}
