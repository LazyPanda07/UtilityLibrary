#include "Strings.h"

#include <functional>
#include <algorithm>

using namespace std;

namespace utility
{
	namespace strings
	{
		string replaceAll(const string& source, string_view oldValue, string_view newValue)
		{
			string result(source);

			return replaceAllByRef(result, oldValue, newValue);
		}

		string& replaceAllByRef(string& source, string_view oldValue, string_view newValue)
		{
			boyer_moore_horspool_searcher searcher(oldValue.begin(), oldValue.end());

			while (true)
			{
				string::iterator it = search(source.begin(), source.end(), searcher);

				if (it == source.end())
				{
					break;
				}

				source.replace(it, it + oldValue.size(), newValue);
			}

			return source;
		}

		vector<string> split(const string& source, string_view delimiter)
		{
			boyer_moore_horspool_searcher searcher(delimiter.begin(), delimiter.end());
			string::const_iterator right = source.begin();
			vector<string> result;

			while (true)
			{
				string::const_iterator left = right;
				right = search(right, source.end(), searcher);

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
	}
}
