#include "Base64.h"

#include <array>

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
			std::string result(std::ceil(data.size() / 3.0) * 4, '\0');

			if (size_t padding = data.size() % 3)
			{
				padding = 3 - padding;

				for (size_t i = 0, j = 0; i < data.size(); i += 3, j += 4)
				{
					bool isLast = i + 3 > data.size();
					uint8_t first = data[i];
					uint8_t second;
					uint8_t third;

					if (isLast)
					{
						switch (padding)
						{
						case 1:
							second = data[i + 1];
							third = 0;

							break;

						case 2:
							second = 0;
							third = 0;

							break;
						}
					}
					else
					{
						second = data[i + 1];
						third = data[i + 2];
					}

					int firstIndex = (first & 0b11111100) >> 2;
					int secondIndex = ((first & 0b00000011) << 4) + ((second & 0b11110000) >> 4);
					int thirdIndex = ((second & 0b00001111) << 2) + ((third & 0b11000000) >> 6);
					int fourthIndex = third & 0b00111111;

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
					int secondIndex = ((first & 0b00000011) << 4) + ((second & 0b11110000) >> 4);
					int thirdIndex = ((second & 0b00001111) << 2) + ((third & 0b11000000) >> 6);
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
			std::string result;

			return result;
		}
	}
}
