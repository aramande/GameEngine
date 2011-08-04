#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "sdl.h"

namespace engine{
	class Image{
		SDL_Surface* image; 
		int w, h;
		std::string filename;
		Image(const Image& other){}
		Image operator=(const Image& other){}
	protected:
		Image(std::string filename);
	public:
		virtual ~Image();
		int getWidth() const;
		int getHeight() const;
		Image* copy() const;
		std::string getFilename() const;
		SDL_Surface* getSurface() const;
		friend class Resource;
	};
}

#endif