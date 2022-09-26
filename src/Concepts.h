#pragma once

#include <string>

#if _HAS_CXX20
#include <concepts>
#include <ranges>
#endif // _HAS_CXX20

#if _HAS_CXX20
namespace utility
{
	namespace concepts
	{
		template<typename T>
		concept StringConvertible = requires(T&& value)
		{
			static_cast<std::string>(value);
		};
	}
}
#endif // _HAS_CXX20
