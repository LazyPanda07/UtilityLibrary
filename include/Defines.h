#pragma once

#include <string_view>

#ifdef UTILITY_LIBRARY_DLL
#define UTILITY_LIBRARY_FUNCTION_API extern "C" __declspec(dllexport)
#define UTILITY_LIBRARY_API __declspec(dllexport)

#pragma warning(disable: 4190)
#pragma warning(disable: 4251)
#else
#define UTILITY_LIBRARY_FUNCTION_API
#define UTILITY_LIBRARY_API
#endif // UTILITY_LIBRARY_DLL

/**
 * @brief Current version of UtilityLibrary
*/
static constexpr std::string_view utilityLibraryVersion = "0.2.0";
