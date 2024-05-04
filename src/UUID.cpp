#include "UUID.h"

#include <stdexcept>

#ifdef __LINUX__
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

#ifdef __LINUX__
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
