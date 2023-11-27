#pragma once

#include <fstream>
#include <vector>

#if _HAS_CXX17
#include <filesystem>
#endif // _HAS_CXX17

#include "Concepts.h"

namespace utility
{
	namespace files
	{
#if _HAS_CXX20
		/**
		 * @brief Generate path from parameters
		 * @tparam Path 
		 * @tparam ...Args 
		 * @param path 
		 * @param ...args 
		 * @return 
		*/
		template<concepts::StringViewConvertible Path, concepts::StringViewConvertible... Args>
		std::filesystem::path generatePath(Path&& path, Args&&... args);

		/**
		 * @brief Generate path from parameters
		 * @tparam T 
		 * @tparam ...Args 
		 * @param paths 
		 * @return 
		*/
		template<template<typename, typename...> typename Container, typename T, typename... Args> requires (std::ranges::range<Container<T, Args...>> && concepts::StringConvertible<T>)
		std::filesystem::path generatePath(const Container<T, Args...>& paths);
#elif _HAS_CXX17
		/**
		 * @brief Generate path from parameters
		 * @tparam Path 
		 * @tparam ...Args 
		 * @param path 
		 * @param ...args 
		 * @return 
		*/
		template<typename Path, typename... Args>
		std::filesystem::path generatePath(Path&& path, Args&&... args);

		/**
		 * @brief Generate path from parameters
		 * @tparam T 
		 * @tparam ...Args 
		 * @param paths 
		 * @return 
		*/
		template<template<typename, typename...> typename Container, typename T, typename... Args>
		std::filesystem::path generatePath(const Container<T, Args...>& paths);
#endif // _HAS_CXX20
	}
}

#include "Files.inl"
