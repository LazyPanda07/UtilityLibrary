namespace utility::parsers
{
	template<typename T>
	inline T ConsoleArgumentParser::getNumeric(std::string_view integralValue, const T& defaultValue, std::errc* errorCode) const
	{
		T value = defaultValue;

		std::from_chars_result result = std::from_chars(integralValue.data(), integralValue.data() + integralValue.size(), value);

		if (errorCode)
		{
			*errorCode = result.ec;
		}
		else
		{
			if (result.ec != std::errc())
			{
				std::string errorMessage("Convert error code: ");

				errorMessage += std::to_string(static_cast<int>(result.ec));

				warnings.push_back(std::move(errorMessage));
			}
		}

		return value;
	}

	template<typename T>
	inline T ConsoleArgumentParser::get(std::string_view argumentName, const T& defaultValue, std::errc* errorCode) const
	{
		std::optional<std::string_view> result = this->findValue(argumentName);

		if constexpr (std::is_same_v<int8_t, T> || std::is_same_v<uint8_t, T>)
		{
			if (!result)
			{
				return defaultValue;
			}

			return static_cast<T>(this->getNumeric<char>(*result, defaultValue, errorCode));
		}
		else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
		{
			if (!result)
			{
				return defaultValue;
			}

			return this->getNumeric<T>(*result, defaultValue, errorCode);
		}
		else if constexpr (std::is_convertible_v<T, std::string>)
		{
			return result ? std::string(result->data()) : defaultValue;
		}
		else
		{
			[] <bool flag = false>()
			{
				static_assert(flag, "Wrong type");
			}();
		}
	}

	template<typename T>
	inline std::vector<T> ConsoleArgumentParser::getValues(std::string_view argumentName) const
	{
		std::vector<T> result;

		if constexpr (!std::is_integral_v<T> && !std::is_floating_point_v<T> && !std::is_convertible_v<std::string, T>)
		{
			[] <bool flag = false>()
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
					result.push_back(this->getNumeric<T>(*it));
				}
				else if constexpr (std::is_convertible_v<std::string, T>)
				{
					result.emplace_back(std::string(it->data()));
				}
			}
		}

		return result;
	}

	template<>
	inline bool ConsoleArgumentParser::get<bool>(std::string_view argumentName, const bool& defaultValue, std::errc* errorCode) const
	{
		return std::ranges::find(values, argumentName) != values.end() || defaultValue;
	}
}
