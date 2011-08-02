#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "sdl.h"

namespace engine{
	/**
	 * Taken from the Cwing package and slightly modified
	 */
	struct Rectangle : public SDL_Rect{
		Rectangle();
		Rectangle(int xx, int yy, int ww, int hh);
		bool contains(int xx, int yy) const;
		Rectangle* centeredRect(int width, int height) const;
		bool overlaps(const Rectangle& other) const;
		SDL_Rect getSDL_Rect();
	};
} // engine

#endif