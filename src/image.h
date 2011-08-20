#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "sdl.h"

namespace engine{
	class Image{
		SDL_Surface* image; 
		bool alpha;
		int w, h;
		std::string filename;

		/**
		 * Taken from f17:9, gets color information about a single pixel in the image
		 */
		Uint32 getPixel(SDL_Surface* surf, int x, int y) const;
		Image(const Image& other){}
		Image operator=(const Image& other){}
	protected:
		Image(std::string path, std::string filename, bool alpha, bool pixel);
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
