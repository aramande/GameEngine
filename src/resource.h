#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <map>
#include "image.h"
#include "sdl.h"

namespace engine{
	class Resource{
		static std::map<std::string, Image*> loadedImages;
		static std::map<std::string, int> imageCount;
		static std::map<std::string, TTF_Font*> loadedFonts;
		static std::map<std::string, int> fontCount;
		
	public:
		/**
		 * Loads an image from the harddrive into memory. 
		 * If the image was already loaded, you will receive 
		 * a pointer to the already loaded image.
		 *
		 * @param alpha if true, the alpha channel of the image is parsed, only matters the first time the image is loaded.
		 */
		static Image* loadImage(std::string filename, bool alpha = true);

		/**
		 * It's recommended to use this if the image will 
		 * never be used again during the execution,
		 * as it saves a small bit of memory.
		 */
		static void unloadImage(std::string filename);
		static void unloadImage(const Image* img);
		/**
		 * Loads a font from the harddrive into memory. 
		 * If the font was already loaded, you will receive 
		 * a pointer to the already loaded image.
		 */

		static TTF_Font* loadFont(std::string filename, int size = 18);

		/**
		 * It's recommended to use this if the image will 
		 * never be used again during the execution,
		 * as it saves a small bit of memory.
		 */
		static void unloadFont(std::string filename, int size);

	};
}

#endif