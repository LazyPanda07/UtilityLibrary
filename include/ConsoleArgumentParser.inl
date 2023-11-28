#ifndef NO_CONSOLE_ARGUMENT_PARSER
namespace utility
{
	namespace parsers
	{
		template<typename T>
		T ConsoleArgumentParser::getIntegral(std::string_view integralValue, const T& defaultValue, std::errc* errorCode) const
		{
			T value = defaultValue;

			auto [_, error] = std::from_chars(integralValue.data(), integralValue.data() + integralValue.size(), value);

			if (errorCode)
			{
				*errorCode = error;
			}
			else
			{
				if (error != std::errc())
				{
					warnings.push_back("Convert error code: " + std::to_string(static_cast<int>(error)));
				}
			}

			return value;
		}

		template<typename T>
		T ConsoleArgumentParser::get(std::string_view argumentName, const T& defaultValue, std::errc* errorCode) const
		{
			std::optional<std::string_view> result = this->findValue(argumentName);

			if constexpr (std::is_same_v<int8_t, T> || std::is_same_v<uint8_t, T>)
			{
				if (!result)
				{
					return defaultValue;
				}

				return static_cast<T>(this->getIntegral<char>(*result, defaultValue, errorCode));
			}
			else if constexpr (std::is_integral_v<T>)
			{
				if (!result)
				{
					return defaultValue;
				}

				return this->getIntegral<T>(*result, defaultValue, errorCode);
			}
			else if constexpr (std::is_convertible_v<std::string, T>)
			{
				return result ? std::string(result->data()) : defaultValue;
			}
			else
			{
				[]<bool flag = false>()
				{
					static_assert(flag, "Wrong type");
				}();
			}
		}

		template<typename T>
		std::vector<T> ConsoleArgumentParser::getValues(std::string_view argumentName) const
		{
			std::vector<T> result;

			if constexpr (!std::is_integral_v<T> && !std::is_convertible_v<std::string, T>)
			{
				[]<bool flag = false>()
				{
					static_assert(flag, "Wrong type");
				}();
			}

			for (auto it = values.begin(); it != values.end(); ++it)
			{
				if (*it == argumentName)
				{
					++it;

					if (it == values.end())
					{
						break;
					}

					if constexpr (std::is_integral_v<T>)
					{
						result.push_back(this->getIntegral<T>(*it));
					}
					else if constexpr (std::is_convertible_v<std::string, T>)
					{
						result.emplace_back(std::string(it->data()));
					}
				}
			}

			return result;
		}
	}
}
#endif // !NO_CONSOLE_ARGUMENT_PARSER
