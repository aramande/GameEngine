cmake_minimum_required (VERSION 2.6)

add_library(gameengine 
	badarg.h
	button.cpp button.h
	cconfig.h cconfig.h.in
	component.cpp component.h
	event.h
	eventhandler.cpp eventhandler.h
	fileexception.h
	gameengine.cpp gameengine.h
	gui.cpp gui.h
	image.cpp image.h
	keyevent.cpp keyevent.h
	logger.cpp logger.h
	mouseevent.cpp mouseevent.h
	rectangle.cpp rectangle.h
	resource.cpp resource.h
	sdl.h 
	sdlerror.h
	sprite.cpp sprite.h
	timer.cpp timer.h
	window.cpp window.h)

set(test_headers
	${CMAKE_CURRENT_SOURCE_DIR}/eventhandlertest.h
	${CMAKE_CURRENT_SOURCE_DIR}/guitest.h
	${CMAKE_CURRENT_SOURCE_DIR}/keyeventtest.h
	${CMAKE_CURRENT_SOURCE_DIR}/mouseevent.h
	${CMAKE_CURRENT_SOURCE_DIR}/resourcetest.h
	${CMAKE_CURRENT_SOURCE_DIR}/spritetest.h)

add_executable(game
	main.cpp
	projectile.cpp projectile.h)



find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

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

include_directories(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(game gameengine)
