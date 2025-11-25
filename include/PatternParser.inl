namespace utility::parsers
{
	template<typename... Args>
	template<size_t Index>
	inline constexpr auto& PatternParser<Args...>::getValue(Args&... args) const
	{
		return std::get<Index>(std::forward_as_tuple(args...));
	}

	template<typename... Args>
	template<size_t Index>
	inline constexpr void PatternParser<Args...>::parseValue(std::string_view data, size_t offset, Args&... args) const
	{
		auto& value = this->getValue<Index>(args...);
		Converter<std::remove_reference_t<decltype(value)>> converter;
		size_t stringValueIndex = data.find(nextCharacter[Index], offset + offsets[Index]);
		std::string_view stringValue(data.begin() + offset + offsets[Index], (stringValueIndex == std::string_view::npos) ? data.end() : data.begin() + stringValueIndex);

		converter.convert(stringValue, value);

		if constexpr (Index + 1 != sizeof...(Args))
		{
			this->parseValue<Index + 1>(data, offset + stringValue.size(), args...);
		}
	}

	template<typename... Args>
	inline constexpr PatternParser<Args...>::PatternParser(std::string_view format)
	{
		size_t offset = format.find("{}");
		size_t index = 0;

		while (offset != std::string_view::npos)
		{
#ifndef __LINUX__
#pragma warning(push)
#pragma warning(disable: 28020)
#endif
			offsets[index] = offset - 2 * index;
#ifndef __LINUX__
#pragma warning(pop)
#endif
			format.size() > offset + 2 ?
				nextCharacter[index] = format[offset + 2] :
				nextCharacter[index] = '\0';

			offset = format.find("{}", offset + 1);

			index++;
		}
	}

	template<typename... Args>
	inline void PatternParser<Args...>::parse(std::string_view data, Args&... args) const
	{
		static_assert(sizeof...(args) == nextCharacter.size());

		this->parseValue(data, 0, args...);
	}
}
