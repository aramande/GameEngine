#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "sdl.h"

namespace engine{
	class Image{
		SDL_Surface *image; 
		int w, h;
		Image(std::string filename);
	public:
		virtual ~Image();
		int getWidth();
		int getHeight();
		friend class Resource;
	};
}

#endif