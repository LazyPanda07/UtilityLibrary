#pragma once

#include <string>

#include <concepts>
#include <ranges>

namespace utility::concepts
{
	/**
	 * @brief Provides static_cast<std::string>
	 */
	template<typename T>
	concept StringConvertible = requires(T && value)
	{
		static_cast<std::string>(value);
	};

	/**
	 * @brief Provides static_cast<std::string_view>
	 */
	template<typename T>
	concept StringViewConvertible = requires(T && value)
	{
		static_cast<std::string_view>(value);
	};
}
