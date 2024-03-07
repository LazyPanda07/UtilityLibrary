#pragma once

#include <string_view>

#ifdef UTILITY_LIBRARY_DLL
#ifdef __LINUX__
#define UTILITY_LIBRARY_API __attribute__((visibility("default")))
#else
#define UTILITY_LIBRARY_API __declspec(dllexport)

#pragma warning(disable: 4297)
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4190)
#endif

#define UTILITY_LIBRARY_API_FUNCTION extern "C" UTILITY_LIBRARY_API
#else
#define UTILITY_LIBRARY_API
#define UTILITY_LIBRARY_API_FUNCTION
#endif // UTILITY_LIBRARY_DLL

/**
 * @brief Current version of UtilityLibrary
*/
static constexpr std::string_view utilityLibraryVersion = "0.4.0";
