#ifndef MY_SDL_H
#define MY_SDL_H

#if defined(_WIN32)
	#include <sdl.h>
	#include <sdl_image.h>
	#include <sdl_ttf.h>
#elif defined(_WIN64)
	#include <sdl.h>
	#include <sdl_image.h>
	#include <sdl_ttf.h>
#else
	#include <sdl/sdl.h>
	#include <sdl/sdl_image.h>
	#include <sdl/sdl_ttf.h>
#endif

#endif