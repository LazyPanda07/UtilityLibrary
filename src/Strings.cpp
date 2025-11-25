#include "Strings.h"

#include <functional>
#include <algorithm>

namespace utility::strings
{
	std::string replaceAll(const std::string& source, std::string_view oldValue, std::string_view newValue)
	{
		std::string result(source);

		return replaceAllByRef(result, oldValue, newValue);
	}

	std::string& replaceAllByRef(std::string& source, std::string_view oldValue, std::string_view newValue)
	{
		std::boyer_moore_horspool_searcher searcher(oldValue.begin(), oldValue.end());

		while (true)
		{
			std::string::iterator it = std::search(source.begin(), source.end(), searcher);

			if (it == source.end())
			{
				break;
			}

			source.replace(it, it + oldValue.size(), newValue);
		}

		return source;
	}

	std::vector<std::string> split(std::string_view source, std::string_view delimiter)
	{
		std::boyer_moore_horspool_searcher searcher(delimiter.begin(), delimiter.end());
		std::string_view::const_iterator right = source.begin();
		std::vector<std::string> result;

		while (true)
		{
			std::string_view::const_iterator left = right;
			right = std::search(right, source.end(), searcher);

			if (right == source.end() && left == source.end())
			{
				break;
			}

			result.emplace_back(left, right);

			if (right != source.end())
			{
				right += delimiter.size();
			}
		}

		return result;
	}

	size_t StringViewHash::operator()(std::string_view value) const
	{
		return std::hash<std::string_view>()(value);
	}

	bool StringViewEqual::operator ()(std::string_view left, std::string_view right) const
	{
		return left == right;
	}
}
