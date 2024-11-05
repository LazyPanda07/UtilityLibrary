cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install-dir CACHE STRING "")
option(BUILD_SHARED_LIBS "" OFF)
option(NO_CONSOLE_ARGUMENT_PARSER "Remove ConsoleArgumentParser" OFF)
option(NO_CSV_PARSER "Remove CSVParser" OFF)
option(NO_TIMERS "Remove Timers" OFF)

if (${BUILD_SHARED_LIBS})
	add_definitions(-DUTILITY_LIBRARY_DLL)
endif ()

if(${NO_CONSOLE_ARGUMENT_PARSER})
	add_definitions(-DNO_CONSOLE_ARGUMENT_PARSER)
endif ()

if(${NO_CSV_PARSER})
	add_definitions(-DNO_CSV_PARSER)
endif ()

if (${NO_TIMERS})
	add_definitions(-DNO_TIMERS)
endif ()

project(UtilityLibrary VERSION 0.5.7)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	add_definitions(-D__ANDROID__)

	set(UUID_LIB)
elseif (UNIX)
	add_definitions(-D__LINUX__)

	set(UUID_LIB uuid)
else ()
	set(UUID_LIB rpcrt4)
endif ()

add_library(
	${PROJECT_NAME}
	src/ConsoleArgumentParser.cpp
	src/CSVParser.cpp
	src/Files.cpp
	src/Strings.cpp
	src/Timers.cpp
	src/UUID.cpp
)

target_include_directories(
	${PROJECT_NAME} PUBLIC
	include
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC
	${UUID_LIB}
)

install(
	TARGETS ${PROJECT_NAME} 
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/dll
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
