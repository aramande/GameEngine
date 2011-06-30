cmake_minimum_required (VERSION 2.6)

add_library(gameengine 
	button.cpp
	component.cpp
	gameengine.cpp
	gui.cpp
	sprite.cpp
	window.cpp)

set(test_headers
	spritetest.h)

find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)

if(SDL_FOUND)
	include_directories(${SDL_INCLUDE_DIR})
	target_link_libraries(gameengine ${SDL_LIBRARY})
endif()

if(SDLIMAGE_FOUND)
	include_directories(${SDLIMAGE_INCLUDE_DIR})
	target_link_libraries(gameengine ${SDLIMAGE_LIBRARY})
endif()

if(SDLTTF_FOUND)
	include_directories(${SDLTTF_INCLUDE_DIR})
	target_link_libraries(gameengine ${SDLTTF_LIBRARY})
endif()

set(CXXTEST_USE_PYTHON true)
find_package(CxxTest)

if(CXXTEST_FOUND)
	include_directories(${CXXTEST_INCLUDE_DIR})
	enable_testing()
	CXXTEST_ADD_TEST(enginetest tests.cpp ${test_headers})
	target_link_libraries(enginetest gameengine)
endif()
