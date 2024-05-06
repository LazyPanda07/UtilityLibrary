#pragma once

#include <span>

#include <Defines.h>

namespace utility
{
	namespace conversion
	{
		UTILITY_LIBRARY_API_FUNCTION std::string encodeBase64(std::span<uint8_t> data);

		UTILITY_LIBRARY_API_FUNCTION std::string encodeBase64(std::string_view data);

		UTILITY_LIBRARY_API_FUNCTION std::string decodeBase64(std::span<uint8_t> data);

		UTILITY_LIBRARY_API_FUNCTION std::string decodeBase64(std::string_view data);
	}
}
