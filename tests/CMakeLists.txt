cmake_minimum_required(VERSION 3.27)

project(UtilityLibraryTests)

add_executable(${PROJECT_NAME} Main.cpp TestCases/TestStrings.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME} PRIVATE ../include gtest/include)

target_link_libraries(${PROJECT_NAME} PRIVATE "${TEST_LIBRARY_PATH}/UtilityLibrary.lib" ${CMAKE_SOURCE_DIR}/gtest/lib/gtest.lib ${CMAKE_SOURCE_DIR}/gtest/lib/gtest_main.lib)

if(EXISTS "${TEST_LIBRARY_PATH}/UtilityLibrary.dll")
	add_definitions(-DUTILITY_LIBRARY_DLL)
	file(COPY_FILE "${TEST_LIBRARY_PATH}/UtilityLibrary.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/UtilityLibrary.dll" ONLY_IF_DIFFERENT)
endif()
