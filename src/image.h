#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "sdl.h"
#include "resource.h"

namespace engine{
	class Image : public Resource{
		friend class ResourceParser;
		SDL_Surface* image; 
		bool alpha, pixel, final;
		int w, h;
		std::string path, filename;

		/**
		 * Taken from f17:9, gets color information about a single pixel in the image
		 */
		Uint32 getPixel(SDL_Surface* surf, int x, int y) const;
		void setPixel(bool pixel);
		void setAlpha(bool alpha);
		void setFile(std::string path, std::string filename);
		void finalize();

		Image(const Image& other){}
		Image operator=(const Image& other){}
		~Image();
	protected:
		Image(std::string name);
		//Image(std::string path, std::string filename, bool alpha, bool pixel);
	public:
		int getWidth() const;
		int getHeight() const;
		//Image* copy() const;
		std::string getFilename() const;
		SDL_Surface* getSurface() const;

//		bool release();
		friend class ResourceHandler;
	};
}

#endif
