cmake_minimum_required(VERSION 3.27)

project(UtilityLibraryTests)

add_executable(
	${PROJECT_NAME} 
	Main.cpp
	src/Utility.cpp
	TestCases/TestConsoleArgumentParser.cpp
	TestCases/TestCSVParser.cpp
	TestCases/TestStrings.cpp
	TestCases/TestFiles.cpp
	TestCases/TestTimers.cpp
)

set(CXX_VERSION "20" CACHE STRING "C++ version")
option(NO_CONSOLE_ARGUMENT_PARSER "Remove ConsoleArgumentParser" OFF)
option(NO_CSV_PARSER "Remove CSVParser" OFF)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD ${CXX_VERSION})

target_include_directories(${PROJECT_NAME} PRIVATE include ../include gtest/include)

target_link_libraries(${PROJECT_NAME} PRIVATE "${TEST_LIBRARY_PATH}/UtilityLibrary.lib" ${CMAKE_SOURCE_DIR}/gtest/lib/gtest.lib ${CMAKE_SOURCE_DIR}/gtest/lib/gtest_main.lib)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CONFIGURATION}/")
file(COPY_FILE "${CMAKE_SOURCE_DIR}/data/test.csv" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/test.csv")

if(EXISTS "${TEST_LIBRARY_PATH}/UtilityLibrary.dll")
	add_definitions(-DUTILITY_LIBRARY_DLL)
	file(COPY_FILE "${TEST_LIBRARY_PATH}/UtilityLibrary.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/UtilityLibrary.dll")
endif()

if(${NO_CONSOLE_ARGUMENT_PARSER})
	add_definitions(-DNO_CONSOLE_ARGUMENT_PARSER)
endif()

if(${NO_CSV_PARSER})
	add_definitions(-DNO_CSV_PARSER)
endif()
