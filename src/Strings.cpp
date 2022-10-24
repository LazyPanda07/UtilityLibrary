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

			return replaceAllRef(result, oldValue, newValue);
		}

		string& replaceAllRef(string& source, string_view oldValue, string_view newValue)
		{
			boyer_moore_horspool_searcher oldValueSearcher(oldValue.begin(), oldValue.end());

			while (true)
			{
				string::iterator it = search(source.begin(), source.end(), oldValueSearcher);

				if (it == source.end())
				{
					break;
				}

				source.replace(it, it + oldValue.size(), newValue);
			}

			return source;
		}
	}
}
