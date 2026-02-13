#pragma once

#ifndef __WITHOUT_CONSOLE_ARGUMENT_PARSER__
#include <vector>
#include <string>
#include <optional>
#include <charconv>
#include <cstdint>
#include <algorithm>
#include <format>

#include "Defines.h"

namespace utility::parsers
{
	/**
	 * @brief Console argument parser
	*/
	class UTILITY_LIBRARY_API ConsoleArgumentParser
	{
	public:
		class UTILITY_LIBRARY_API ConstIterator
		{
		private:
			bool isBool() const;

		private:
			std::vector<std::string_view>::const_iterator begin;
			std::vector<std::string_view>::const_iterator end;

		public:
			ConstIterator(std::vector<std::string_view>::const_iterator begin, std::vector<std::string_view>::const_iterator end);

			std::string_view key() const;

			template<typename T = std::string>
			T value() const;

			ConstIterator operator *() const noexcept;

			ConstIterator& operator ++();

			bool operator !=(const ConstIterator& other) const noexcept;

			bool operator ==(const ConstIterator& other) const noexcept = default;

			~ConstIterator() = default;
		};

	private:
		std::string_view currentExecutable;
		int argc;
		std::vector<std::string_view> values;
		mutable std::vector<std::string> warnings;

	private:
		std::optional<std::string_view> findValue(std::string_view argumentName) const;

		template<typename T>
		T getNumeric(std::string_view integralValue, const T& defaultValue = T(), std::errc* errorCode = nullptr) const;

	public:
		ConsoleArgumentParser(int argc, char** argv);

		/**
		 * @brief All arguments size
		 * @return 
		 */
		int argcSize() const;

		/**
		 * @brief All keys
		 * @return 
		 */
		size_t size() const;

		/**
		 * @brief Returns the path or filename of the current executable.
		 * @return A std::string_view referencing the current executable's path or name. The view's validity is tied to the lifetime and state of the object providing it.
		 */
		std::string_view getCurrentExecutable() const;

		/**
		 * @brief Get warnings from get and getValues
		 * @param clearWarnings Clear previous warnings
		 * @return
		*/
		std::vector<std::string> getWarnings(bool clearWarnings = true) const;

		/**
		 * @brief Get command line value
		 * @tparam T
		 * @param argumentName
		 * @param defaultValue Returned value if can't find argumentName
		 * @param errorCode Conversion error
		 * @return
		*/
		template<typename T>
		T get(std::string_view argumentName, const T& defaultValue = T(), std::errc* errorCode = nullptr) const;

		/**
		 * @brief Get commnad line value
		 * @tparam T 
		 * @param argumentName 
		 * @return If can't find throw std::runtime_error
		 */
		template<typename T>
		T getRequired(std::string_view argumentName) const;

		/**
		 * @brief Get all command line values with same argument name
		 * @tparam T
		 * @param argumentName
		 * @return
		*/
		template<typename T>
		std::vector<T> getValues(std::string argumentName) const;

		/**
		 * @brief Get all command line values with same argument name. If can't find throw std::runtime_error
		 * @tparam T
		 * @param argumentName
		 * @return
		*/
		template<typename T>
		std::vector<T> getValuesRequired(std::string argumentName) const;

		ConstIterator begin() const noexcept;

		ConstIterator end() const noexcept;

		~ConsoleArgumentParser() = default;
	};
}

#include "ConsoleArgumentParser.inl"
#endif
