#include <numeric>

namespace utility
{
	namespace files
	{
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
			return std::accumulate
			(
				paths.begin(), paths.end(), std::string(),
				[](const T& first, const T& second)
				{
#ifdef __LINUX__
					static constexpr char separator = '/';
#else
					static constexpr char separator = '\\';
#endif // __LINUX__

					return first == "" ? second : first + separator + second;
				}
			);
		}
	}
}
