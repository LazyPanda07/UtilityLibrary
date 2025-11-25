#pragma once

#ifndef __WITHOUT_PATTERN_PARSER__

#include <array>
#include <tuple>
#include <string_view>

namespace utility::parsers
{
	/**
	 * @brief Must be specialized for each parsed type
	 * @tparam T 
	 */
	template<typename T>
	struct Converter
	{
		constexpr void convert(std::string_view data, T& result)
		{
			static_assert(false, "Wrong type");
		}
	};

	/**
	 * @brief Parse values from predefined pattern string. For each parsed value Converter must be specialized
	 * @tparam ...Args 
	 */
	template<typename... Args>
	class PatternParser
	{
	private:
		std::array<size_t, sizeof...(Args)> offsets;
		std::array<char, sizeof...(Args)> nextCharacter;

	private:
		template<size_t Index>
		constexpr auto& getValue(Args&... args) const;

		template<size_t Index = 0>
		constexpr void parseValue(std::string_view data, size_t offset, Args&... args) const;

	public:
		/**
		 * @brief Create parser from format string
		 * @param format Format string with {} for each value
		 */
		constexpr PatternParser(std::string_view format);

		/**
		 * @brief Get values from specific string
		 * @param data Result values
		 * @param ...args 
		 */
		void parse(std::string_view data, Args&... args) const;
	};
}

#include "PatternParser.inl"
#endif
