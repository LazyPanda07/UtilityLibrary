cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD "20" CACHE STRING "C++ version")
set(DLL ${CMAKE_SOURCE_DIR}/../UtilityLibrary)

option(NO_CONSOLE_ARGUMENT_PARSER "Remove ConsoleArgumentParser" OFF)
option(NO_CSV_PARSER "Remove CSVParser" OFF)
option(NO_TIMERS "Remove Timers" OFF)

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
)

target_include_directories(
	${PROJECT_NAME} PRIVATE 
	include 
	${CMAKE_SOURCE_DIR}/../include
	gtest/include
)

target_link_directories(
	${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/../UtilityLibrary/lib
	gtest/lib
)

target_link_libraries(
	${PROJECT_NAME} PRIVATE 
	UtilityLibrary
	${LIBS}
	gtest
	gtest_main
)

if(${NO_CONSOLE_ARGUMENT_PARSER})
	add_definitions(-DNO_CONSOLE_ARGUMENT_PARSER)
endif ()

if(${NO_CSV_PARSER})
	add_definitions(-DNO_CSV_PARSER)
endif ()

if (${NO_TIMERS})
	add_definitions(-DNO_TIMERS)
endif ()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES data/test.csv DESTINATION ${CMAKE_BINARY_DIR}/bin)
