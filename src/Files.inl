#include <numeric>

namespace utility
{
	namespace files
	{
#if _HAS_CXX20
		 template<concepts::StringConvertible Path, concepts::StringConvertible... Args>
		 inline std::filesystem::path generatePath(Path&& path, Args&&... args)
		 {
		 	if constexpr (sizeof...(args))
		 	{
		 		return std::filesystem::path(static_cast<std::string>(path)) / generatePath(std::forward<Args>(args)...);
		 	}
		 	else
		 	{
		 		return std::filesystem::path(static_cast<std::string>(path));
		 	}
		 }

		template<template<typename, typename...> typename Container, typename T, typename... Args> requires (std::ranges::range<Container<T, Args...>> && concepts::StringConvertible<T>)
		inline std::filesystem::path generatePath(const Container<T, Args...>& paths)
		{
			return std::accumulate(paths.begin(), paths.end(), std::string(), [](const T& first, const T& second) { return first == "" ? second : first + '\\' + second; });
		}
#endif _HAS_CXX20
	}
}
