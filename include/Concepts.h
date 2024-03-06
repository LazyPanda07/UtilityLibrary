#pragma once

#include <string>

#include <concepts>
#include <ranges>

namespace utility
{
	namespace concepts
	{
		template<typename T>
		concept StringConvertible = requires(T&& value)
		{
			static_cast<std::string>(value);
		};

		template<typename T>
		concept StringViewConvertible = requires(T&& value)
		{
			static_cast<std::string_view>(value);
		};
	}
}
