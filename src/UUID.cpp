#include "UUID.h"

#include <stdexcept>

#ifdef __ANDROID__
#include <array>
#include <random>
#include <chrono>
#elif __LINUX__
#include <uuid/uuid.h>
#else
#include <Rpc.h>
#endif

namespace utility
{
	std::string generateUUID()
	{
		static constexpr size_t uuidSize = 36;

		std::string result;

		result.reserve(uuidSize);

#ifdef __ANDROID__
		static constexpr size_t alphabetSize = 16;
		static constexpr std::array<char, alphabetSize> alphabet =
		{
			'0', '1', '2', '3',
			'4', '5', '6', '7',
			'8', '9', 'a', 'b',
			'c', 'd', 'e', 'f'
		};
		static std::mt19937_64 random(time(nullptr));

		for (size_t i = 0; i < uuidSize; i++)
		{
			result += alphabet[random() % alphabetSize];
		}
#elif __LINUX__
		uuid_t uuid;

		result.resize(uuidSize);

		uuid_generate(uuid);

		uuid_unparse_lower(uuid, result.data());
#else
		UUID uuid;
		char* uuidString = nullptr;

		RPC_STATUS status = UuidCreate(&uuid);

		if (status != RPC_S_OK)
		{
			throw std::runtime_error("Failed to generate UUID");
		}

		status = UuidToStringA(&uuid, reinterpret_cast<RPC_CSTR*>(&uuidString));

		if (status != RPC_S_OK)
		{
			throw std::runtime_error("Failed to generate UUID");
		}

		result = uuidString;

		RpcStringFreeA(reinterpret_cast<RPC_CSTR*>(&uuidString));
#endif

		return result;
	}
}
