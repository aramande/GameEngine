#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <map>
#include "image.h"

namespace engine{
	class Resource{
		static std::map<std::string, Image*> loadedImages;
	public:
		/**
		 * Loads an image from the harddrive into memory. 
		 * If the image was already loaded, you will receive 
		 * a pointer to the already loaded image.
		 */
		static Image* loadImage(std::string filename);

		/**
		 * It's recommended to use this if the image will 
		 * never be used again during the execution,
		 * as it saves a small bit of memory.
		 */
		static void unloadImage(std::string filename);
	};
}

#endif