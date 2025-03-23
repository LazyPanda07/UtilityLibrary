#pragma once

#include <fstream>
#include <vector>
#include <filesystem>

#include "Concepts.h"
#include "Defines.h"

namespace utility::files
{
	/**
	 * @brief Read entire file
	 * @param pathToFile Path to existing file
	 * @param mode Open mode
	 * @return
	 * @exception std::runtime_error
	*/
	UTILITY_LIBRARY_API_FUNCTION std::string readFile(const std::filesystem::path& pathToFile, std::ios::openmode mode = std::ios::in);

	/**
	 * @brief Read entire binary file
	 * @param pathToFile Path to existing file
	 * @return
	 * @exception std::runtime_error
	*/
	UTILITY_LIBRARY_API_FUNCTION std::string readBinaryFile(const std::filesystem::path& pathToFile);

	/**
	 * @brief Read entire file
	 * @param file Input file stream
	 * @return
	 * @exception std::runtime_error
	*/
	UTILITY_LIBRARY_API_FUNCTION std::string readFileFromStream(std::ifstream& file);

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
	template<template<typename, typename...> typename Container, typename T, typename... Args> requires (std::ranges::range<Container<T, Args...>>&& concepts::StringConvertible<T>)
		std::filesystem::path generatePathContainer(const Container<T, Args...>& paths);
}

#include "Files.inl"
