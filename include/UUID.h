#pragma once

#include <string>

#include "Defines.h"

namespace utility::uuid
{
	/**
	 * @brief Generate UUID in format xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
	 * @return 
	 */
	UTILITY_LIBRARY_API_FUNCTION std::string generateUUID();
}
