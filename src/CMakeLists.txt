cmake_minimum_required (VERSION 2.6)

add_library(gameengine 
	button.cpp
	component.cpp
	gameengine.cpp
	gui.cpp
	sprite.cpp)

set(test_headers
	spritetest.cpp)

set(CXXTEST_USE_PYTHON true)
find_package(CxxTest)

if(CXXTEST_FOUND)
	include_directories(${CXXTEST_INCLUDE_DIR})
	enable_testing()
	CXXTEST_ADD_TEST(enginetest tests.cpp 
		spritetest.h)
	
endif()
