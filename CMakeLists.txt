cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "" OFF)
option(WITHOUT_CONSOLE_ARGUMENT_PARSER "Include ConsoleArgumentParser" OFF)
option(WITHOUT_CSV_PARSER "Include CSVParser" OFF)
option(WITHOUT_TIMERS "Include Timers" OFF)
option(WITHOUT_PATTERN_PARSER "Include PatternParser" OFF)

if (${BUILD_SHARED_LIBS})
	add_definitions(-DUTILITY_LIBRARY_DLL)
endif ()

if(${WITHOUT_CONSOLE_ARGUMENT_PARSER})
	add_definitions(-D__WITHOUT_CONSOLE_ARGUMENT_PARSER__)
endif ()

if(${WITHOUT_CSV_PARSER})
	add_definitions(-D__WITHOUT_CSV_PARSER__)
endif ()

if (${WITHOUT_TIMERS})
	add_definitions(-D__WITHOUT_TIMERS__)
endif ()

if (${WITHOUT_PATTERN_PARSER})
	add_definitions(-D__WITHOUT_PATTERN_PARSER__)
endif()

project(UtilityLibrary VERSION 0.11.0)

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

if (DEFINED ENV{MARCH} AND NOT "$ENV{MARCH}" STREQUAL "")
	target_compile_options(${PROJECT_NAME} PRIVATE -march=$ENV{MARCH})
endif()

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
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION dll
)

install(DIRECTORY include DESTINATION .)
