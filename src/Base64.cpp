#include "Base64.h"

#include <array>
#include <cmath>
#include <stdexcept>

static constexpr std::array<uint8_t, 64> table =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

namespace utility
{
	namespace conversion
	{
		std::string encodeBase64(std::span<uint8_t> data)
		{
			return encodeBase64(std::string_view(reinterpret_cast<const char*>(data.data()), data.size()));
		}

		std::string encodeBase64(std::string_view data)
		{
			std::string result(static_cast<size_t>(std::ceil(data.size() / 3.0)) * 4, '\0');

			if (size_t padding = data.size() % 3)
			{
				padding = 3 - padding;

				for (size_t i = 0, j = 0; i < data.size(); i += 3, j += 4)
				{
					bool isLast = i + 3 > data.size();
					uint8_t first = data[i];
					uint8_t second = 0;
					uint8_t third = 0;

					if (isLast)
					{
						if (padding == 1)
						{
							second = data[i + 1];
						}
					}
					else
					{
						second = data[i + 1];
						third = data[i + 2];
					}

					size_t firstIndex = (first & 0b11111100) >> 2;
					size_t secondIndex = ((static_cast<size_t>(first & 0b00000011)) << 4) | ((second & 0b11110000) >> 4);
					size_t thirdIndex = ((static_cast<size_t>(second & 0b00001111)) << 2) | ((third & 0b11000000) >> 6);
					size_t fourthIndex = third & 0b00111111;

					result[j] = table[firstIndex];
					result[j + 1] = table[secondIndex];

					if (isLast)
					{
						switch (padding)
						{
						case 1:
							result[j + 2] = table[thirdIndex];
							result[j + 3] = '=';

							break;

						case 2:
							result[j + 2] = '=';
							result[j + 3] = '=';

							break;
						}
					}
					else
					{
						result[j + 2] = table[thirdIndex];
						result[j + 3] = table[fourthIndex];
					}
				}
			}
			else
			{
				for (size_t i = 0, j = 0; i < data.size(); i += 3, j += 4)
				{
					uint8_t first = data[i];
					uint8_t second = data[i + 1];
					uint8_t third = data[i + 2];

					int firstIndex = (first & 0b11111100) >> 2;
					int secondIndex = ((first & 0b00000011) << 4) | ((second & 0b11110000) >> 4);
					int thirdIndex = ((second & 0b00001111) << 2) | ((third & 0b11000000) >> 6);
					int fourthIndex = third & 0b00111111;

					result[j] = table[firstIndex];
					result[j + 1] = table[secondIndex];
					result[j + 2] = table[thirdIndex];
					result[j + 3] = table[fourthIndex];
				}
			}

			return result;
		}

		std::string decodeBase64(std::span<uint8_t> data)
		{
			return decodeBase64(std::string_view(reinterpret_cast<const char*>(data.data()), data.size()));
		}

		std::string decodeBase64(std::string_view data)
		{
			if (data.size() % 4)
			{
				throw std::runtime_error("Not in base64");
			}

			auto getIndex = [](char byte) -> size_t
				{
					if (byte >= 'a')
					{
						return byte - 'a' + 26;
					}
					else if (byte >= 'A')
					{
						return byte - 'A';
					}
					else if (byte >= '0')
					{
						return byte - '0' + 52;
					}
					else
					{
						return byte == '/' ? 63 : 62;
					}
				};


			std::string result(data.size() / 4 * 3, '\0');
			auto decode = [&result, data, getIndex](size_t i, size_t j)
				{
					size_t first = getIndex(data[i]);
					size_t second = getIndex(data[i + 1]);
					size_t third = getIndex(data[i + 2]);
					size_t fourth = getIndex(data[i + 3]);

					result[j] = static_cast<char>((first << 2) | ((second & 0b00110000) >> 4));
					result[j + 1] = static_cast<char>(((second & 0b00001111) << 4) | ((third & 0b00111100) >> 2));
					result[j + 2] = static_cast<char>(((third & 0b00000011) << 6) | (fourth & 0b00111111));
				};

			for (size_t i = 0, j = 0; i < data.size(); i += 4, j += 3)
			{
				decode(i, j);
			}

			while (result.back() == '\0')
			{
				result.pop_back();
			}

			return result;
		}
	}
}
