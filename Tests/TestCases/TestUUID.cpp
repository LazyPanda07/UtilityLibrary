#include <unordered_set>

#include "gtest/gtest.h"

#include "UUID.h"

TEST(UUID, Generate)
{
	static constexpr size_t uuidsSize = 60000000;

	std::unordered_set<std::string> uuids;

	for (size_t i = 0; i < uuidsSize; i++)
	{
		std::string uuid = utility::generateUUID();

		ASSERT_FALSE(uuids.contains(uuid));

		uuids.insert(std::move(uuid));
	}
}
