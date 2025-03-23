#include <unordered_set>
#include <future>

#include "gtest/gtest.h"

#include "UUID.h"

static constexpr size_t uuidsSize = 300'000;

TEST(UUID, Generate)
{
	std::unordered_set<std::string> uuids;

	for (size_t i = 0; i < uuidsSize; i++)
	{
		std::string uuid = utility::generateUUID();

		ASSERT_FALSE(uuids.contains(uuid));
		ASSERT_EQ(uuids.size(), 36);

		uuids.insert(std::move(uuid));
	}
}

TEST(UUID, GenerateThreading)
{
	std::unordered_set<std::string> first;
	std::unordered_set<std::string> second;
	std::unordered_set<std::string> third;
	std::unordered_set<std::string> fourth;

	auto process = [](std::unordered_set<std::string>& data)
		{
			size_t launchSize = uuidsSize / 4;

			for (size_t i = 0; i < launchSize; i++)
			{
				std::string uuid = utility::generateUUID();

				ASSERT_FALSE(data.contains(uuid));

				data.insert(std::move(uuid));
			}
		};

	std::future<void> firstFuture = std::async(std::launch::async, process, std::ref(first));
	std::future<void> secondFuture = std::async(std::launch::async, process, std::ref(second));
	std::future<void> thirdFuture = std::async(std::launch::async, process, std::ref(third));
	std::future<void> fourthFuture = std::async(std::launch::async, process, std::ref(fourth));

	firstFuture.wait();
	secondFuture.wait();
	thirdFuture.wait();
	fourthFuture.wait();

	std::unordered_set<std::string> result;

	result.insert(first.begin(), first.end());
	result.insert(second.begin(), second.end());
	result.insert(third.begin(), third.end());
	result.insert(fourth.begin(), fourth.end());

	ASSERT_EQ(result.size(), first.size() + second.size() + third.size() + fourth.size());
}
