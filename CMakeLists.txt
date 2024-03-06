cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install-dir CACHE STRING "")
option(BUILD_SHARED_LIBS "" OFF)

if (UNIX)
	add_definitions(-D__LINUX__)
endif (UNIX)

if (${BUILD_SHARED_LIBS})
	add_definitions(-DUTILITY_LIBRARY_DLL)
endif ()

project(UtilityLibrary)

add_library(
	${PROJECT_NAME}
	src/ConsoleArgumentParser.cpp
	src/CSVParser.cpp
	src/Files.cpp
	src/Strings.cpp
	src/Timers.cpp
)

install(
	TARGETS ${PROJECT_NAME} 
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/dll
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
endif ()
