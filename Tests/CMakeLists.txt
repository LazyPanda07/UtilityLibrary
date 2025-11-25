cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD "20" CACHE STRING "C++ version")
set(DLL ${CMAKE_SOURCE_DIR}/../UtilityLibrary)
set(GTEST_VERSION 1.17.0)

option(WITHOUT_CONSOLE_ARGUMENT_PARSER "Remove ConsoleArgumentParser" OFF)
option(WITHOUT_CSV_PARSER "Remove CSVParser" OFF)
option(WITHOUT_TIMERS "Remove Timers" OFF)
option(WITHOUT_PATTERN_PARSER "Remove PatternParser" OFF)

if (UNIX)
	set(DLL ${DLL}/lib/libUtilityLibrary.so)
	set(
		LIBS
		pthread
		uuid
	)

	add_definitions(-D__LINUX__)
else ()
	set(DLL ${DLL}/dll/UtilityLibrary.dll)
	set(LIBS rpcrt4)
endif (UNIX)

if(EXISTS ${DLL})
	add_definitions(-DUTILITY_LIBRARY_DLL)

	install(FILES ${DLL} DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()

project(Tests)

include(FetchContent)

FetchContent_Declare(
	gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v${GTEST_VERSION}
)

FetchContent_MakeAvailable(gtest)

add_executable(
	${PROJECT_NAME} 
	Main.cpp
	src/Utility.cpp
	TestCases/TestConsoleArgumentParser.cpp
	TestCases/TestCSVParser.cpp
	TestCases/TestStrings.cpp
	TestCases/TestFiles.cpp
	TestCases/TestTimers.cpp
	TestCases/TestUUID.cpp
	TestCases/TestPatternParser.cpp
)

target_include_directories(
	${PROJECT_NAME} PRIVATE 
	include 
	${CMAKE_SOURCE_DIR}/../include
)

target_link_directories(
	${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/../UtilityLibrary/lib
)

target_link_libraries(
	${PROJECT_NAME} PRIVATE 
	UtilityLibrary
	${LIBS}
	gtest
	gtest_main
)

if(${WITHOUT_CONSOLE_ARGUMENT_PARSER})
	add_definitions(-D__WITHOUT_CONSOLE_ARGUMENT_PARSER__)
endif()

if(${WITHOUT_CSV_PARSER})
	add_definitions(-D__WITHOUT_CSV_PARSER__)
endif()

if (${WITHOUT_TIMERS})
	add_definitions(-D__WITHOUT_TIMERS__)
endif()

if (${WITHOUT_PATTERN_PARSER})
	add_definitions(-D__WITHOUT_PATTERN_PARSER__)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES data/test.csv DESTINATION ${CMAKE_BINARY_DIR}/bin)
