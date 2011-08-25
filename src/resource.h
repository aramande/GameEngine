#ifndef RESOURCE_H
#define RESOURCE_H

#include <typeinfo>
#include <string>
#include <map>
#include "sdl.h"

namespace engine{
	class Resource{
		friend class ResourceParser;
		friend class ResourceHandler;
		unsigned int refCount;
		std::string name;

		Resource(const Resource&){}
		Resource& operator=(const Resource&){}
	protected:
		/**
		 * Increase the reference counter. This is used to indicate a new user of
		 * the resource.
		 */
		void operator++();
		/**
		 * Decrease the reference counter. This is called when a user releases a
		 * resource. When the counter reaches zero the resource is marked as
		 * inactive and cannot handle any more requests until a new user is registered.
		 */
		void operator--();

		void setName(std::string name);
	public:
		Resource();
		virtual ~Resource(){}

		/**
		 * Release the reference to this resource if you no longer intend to use
		 * it.
		 *
		 * @return true if image was completely released, false if other
		 * references still exist
		 */
		virtual bool release();

		/**
		 * Get the name of this resource, decided by ResourceHandler through the
		 * information in the resource file.
		 */
		const std::string& getName() const;

		/**
		 * @return Current number of users of this resource.
		 */
		unsigned int getRefCount();

	};
}
/*	class Resource{
	static std::map<std::string, Image*> loadedImages;
	static std::map<std::string, TTF_Font*> loadedFonts;
	static std::map<std::string, int> count;

	public:
		 * Loads an image from the harddrive into memory. 
		 * If the image was already loaded, you will receive 
		 * a pointer to the already loaded image.
		 *
		 * @param alpha if true(default), the alpha channel of the image is parsed, only matters the first time the image is loaded
		 * @param pixel set this to true to parse the top left pixel color as transparency, doing this with a transparent top left pixel may break everything, use with caution
		static Image* loadImage(std::string filename, bool alpha = true, bool pixel = false);

		 * It's recommended to use this if the image will 
		 * never be used again during the execution,
		 * as it saves a small bit of memory.
		static void unloadImage(std::string filename);
		static void unloadImage(Image* img);

		 * Loads a font from the harddrive into memory. 
		 * If the font was already loaded, you will receive 
		 * a pointer to the already loaded image.

		static TTF_Font* loadFont(std::string filename, int size = 18);

		 * It's recommended to use this if the image will 
		 * never be used again during the execution,
		 * as it saves a small bit of memory.
		static void unloadFont(std::string filename, int size);

	};*/

#endif
