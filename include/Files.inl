#include <numeric>

namespace utility
{
	namespace files
	{
#if _HAS_CXX20
		 template<concepts::StringViewConvertible Path, concepts::StringViewConvertible... Args>
		 inline std::filesystem::path generatePath(Path&& path, Args&&... args)
		 {
		 	if constexpr (sizeof...(args))
		 	{
		 		return std::filesystem::path(static_cast<std::string_view>(path)) / generatePath(std::forward<Args>(args)...);
		 	}
		 	else
		 	{
		 		return std::filesystem::path(static_cast<std::string_view>(path));
		 	}
		 }

		template<template<typename, typename...> typename Container, typename T, typename... Args> requires (std::ranges::range<Container<T, Args...>> && concepts::StringConvertible<T>)
		inline std::filesystem::path generatePathContainer(const Container<T, Args...>& paths)
		{
			return std::accumulate(paths.begin(), paths.end(), std::string(), [](const T& first, const T& second) { return first == "" ? second : first + '\\' + second; });
		}
#elif _HAS_CXX17
		template<typename Path, typename... Args>
		inline std::filesystem::path generatePath(Path&& path, Args&&... args)
		{
			static_assert(std::is_convertible_v<Path, std::string_view>, "Path must be convertible to std::string_view");

			if constexpr (sizeof...(args))
			{
				return std::filesystem::path(static_cast<std::string_view>(path)) / generatePath(std::forward<Args>(args)...);
			}
			else
			{
				return std::filesystem::path(static_cast<std::string_view>(path));
			}
		}

		template<template<typename, typename...> typename Container, typename T, typename... Args>
		inline std::filesystem::path generatePathContainer(const Container<T, Args...>& paths)
		{
			static_assert(std::is_convertible_v<T, std::string>, "T must be convertible to std::string");

			return std::accumulate(paths.begin(), paths.end(), std::string(), [](const T& first, const T& second) { return first == "" ? second : first + '\\' + second; });
		}
#endif // _HAS_CXX20
	}
}
