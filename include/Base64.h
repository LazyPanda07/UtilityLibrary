#pragma once

#include <span>
#include <string>

#include <Defines.h>

namespace utility
{
	namespace conversion
	{
		/**
		 * @brief Encode bytes into base64
		 * @param data Bytes
		 * @return String encoded in base64
		 */
		UTILITY_LIBRARY_API_FUNCTION std::string encodeBase64(std::span<uint8_t> data);

		/**
		 * @brief Encode string into base64
		 * @param data String data
		 * @return String encoded in base64
		 */
		UTILITY_LIBRARY_API_FUNCTION std::string encodeBase64(std::string_view data);

		/**
		 * @brief Decode base64 bytes into string
		 * @param data Base64 bytes
		 * @return Decoded string
		 */
		UTILITY_LIBRARY_API_FUNCTION std::string decodeBase64(std::span<uint8_t> data);

		/**
		 * @brief Decode base64 string into string
		 * @param data Base64 string
		 * @return Decoded string
		 */
		UTILITY_LIBRARY_API_FUNCTION std::string decodeBase64(std::string_view data);
	}
}
