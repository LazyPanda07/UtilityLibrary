namespace utility::parsers
{
	template<typename T>
	inline T ConsoleArgumentParser::ConstIterator::value() const
	{
		std::string_view value = *(begin + 1);

		if constexpr (std::same_as<bool, T>)
		{
			return this->isBool();
		}
		else if constexpr (std::same_as<std::string, T>)
		{
			if (this->isBool())
			{
				return "";
			}

			return std::string(value);
		}
		
		if (this->isBool())
		{
			throw std::runtime_error(std::format("Can't convert bool value to {}", typeid(T).name()));
		}

		if constexpr (std::unsigned_integral<T>)
		{
			return static_cast<T>(std::stoull(value.data()));
		}
		else if constexpr (std::integral<T>)
		{
			return static_cast<T>(std::stoll(value.data()));
		}
		else if constexpr (std::floating_point<T>)
		{
			return static_cast<T>(std::stod(value.data()));
		}
		
		throw std::runtime_error(std::format("Wrong type: {}", typeid(T).name()));
	}

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
		if constexpr (!std::same_as<bool, T>)
		{
			std::optional<std::string_view> result = this->findValue(std::format("--{}", argumentName));

			if constexpr (std::integral<T> || std::floating_point<T>)
			{
				return result ? this->getNumeric<T>(*result, defaultValue, errorCode) : defaultValue;
			}
			else if constexpr (std::same_as<T, std::string>)
			{
				return result ? std::string(*result) : defaultValue;
			}
			else
			{
				[] <bool flag = false>()
				{
					static_assert(flag, "Wrong type");
				}();
			}
		}
		else
		{
			std::vector<std::string_view>::const_iterator it = std::ranges::find(values, std::format("--{}", argumentName));

			return it == values.end() ? defaultValue : true;
		}
	}

	template<typename T>
	inline T ConsoleArgumentParser::getRequired(std::string_view argumentName) const
	{
		if (!this->findValue(std::format("--{}", argumentName)))
		{
			throw std::runtime_error(std::format("Can't find --{}", argumentName));
		}

		return this->get<T>(argumentName);
	}

	template<typename T>
	inline std::vector<T> ConsoleArgumentParser::getValues(std::string argumentName) const
	{
		std::vector<T> result;

		argumentName = std::format("--{}", argumentName);

		if constexpr (!std::integral<T> && !std::floating_point<T> && !std::same_as<T, std::string>)
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

				if constexpr (std::integral<T>)
				{
					result.push_back(this->getNumeric<T>(*it));
				}
				else if constexpr (std::same_as<T, std::string>)
				{
					result.emplace_back(std::string(*it));
				}
			}
		}

		return result;
	}

	template<typename T>
	inline std::vector<T> ConsoleArgumentParser::getValuesRequired(std::string argumentName) const
	{
		std::vector<T> result = this->getValues<T>(argumentName);

		if (result.empty())
		{
			throw std::runtime_error(std::format("Can't find --{}", argumentName));
		}

		return result;
	}
}
