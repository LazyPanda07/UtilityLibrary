#pragma once

#include <fstream>
#include <vector>

#if _HAS_CXX17
#include <filesystem>
#endif // _HAS_CXX17

#include "Concepts.h"
#include "Defines.h"

namespace utility
{
	namespace files
	{
		/**
		 * @brief Read entire file
		 * @param pathToFile Path to existing file
		 * @param mode Open mode
		 * @return 
		 * @exception std::runtime_error
		*/
		UTILITY_LIBRARY_API std::string readFile(const std::filesystem::path& pathToFile, std::ios::openmode mode = std::ios::in);

		/**
		 * @brief Read entire binary file
		 * @param pathToFile Path to existing file
		 * @return 
		 * @exception std::runtime_error
		*/
		UTILITY_LIBRARY_API std::string readBinaryFile(const std::filesystem::path& pathToFile);

		/**
		 * @brief Read entire file
		 * @param file Input file stream
		 * @return 
		 * @exception std::runtime_error
		*/
		UTILITY_LIBRARY_API std::string readFile(std::ifstream& file);

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
		std::filesystem::path generatePathContainer(const Container<T, Args...>& paths);
#else
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
		std::filesystem::path generatePathContainer(const Container<T, Args...>& paths);
#endif // _HAS_CXX20
	}
}

#include "Files.inl"
