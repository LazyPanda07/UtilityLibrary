#pragma once

#ifdef UTILITY_LIBRARY_DLL
#define UTILITY_LIBRARY_API extern "C" __declspec(dllexport)

#pragma warning(disable: 4190)
#else
#define UTILITY_LIBRARY_API
#endif // UTILITY_LIBRARY_DLL
