#ifndef RESOURCE_HANDLER_H
#define RESOURCE_HANDLER_H

#include <map>
#include <string>
#include <vector>
#include "parser.h"
#include "image.h"
#include "font.h"
#include "sdl.h"

namespace engine{
	class ResourceParser;
	class Resource;

	class ResourceHandler{
		typedef std::map<std::string, Resource*> Resources;
		typedef Resources::iterator ResourceIterator;
		Resources resources;

		void cleanUp();
		/**
		 * A Resource member function pointer to handle resource file parsing.
		 *
		 * @param buffer
		 * @return A map with name to Resource pointer.
		 */
		//typedef const Resources& (*Parser)(const std::string& buffer);

		static ResourceHandler* self;
		ResourceHandler();
		~ResourceHandler();
	public:
		/**
		 * Get the instance of the ResourceHandler and create it if needed.
		 */
		static ResourceHandler* init();

		/**
		 * Delete the instance and clean up all the resources.
		 */
		static void destroy();
		
		/**
		 * Get resource by name. For every get, please do a release to keep the
		 * resources clean.
		 *
		 * @return A pointer to the requested resource or NULL if it wasn't
		 *	loaded
		 */
		Resource* getResource(const std::string& name);
		Image* getImage(const std::string& name);
		Font* getFont(const std::string& name);

		/**
		 * Get the name of a resource.
		 */
		const std::string& getName(const Resource* resource) const;

		/**
		 * Check if a certain key exists in the map of
		 * resources.
		 */
		bool hasKey(const std::string& key) const;

		/**
		 * Loads all the resources from a resource file into memory.
		 * 
		 * @param filename Path to the resource file relative to DATADIR
		 * @param parse Pointer to the parser object to use while parsing the
		 * file. If NULL, default ResourceParser is used.
		 * @return The resource data loaded from the file
		 */
		void loadResourceFile(const std::string& filename, ResourceParser* parse = NULL);

		/**
		 * Unloads the specified resource by name.
		 */
		bool release(const std::string& name);
	};

	class ResourceParser : public Parser{
		typedef std::map<std::string, Resource*> Resources;
		typedef Resources::iterator ResourceIterator;

		void parseImage(std::ifstream& file, int& linenr, std::string name, bool hadBrace);
		void parseFont(std::ifstream& file, int& linenr, std::string name, bool hadBrace);
		std::string ignoreComments(std::ifstream& file, int& linenr);
		Resources storage;
		std::string filename;

	public:
		ResourceParser();
		~ResourceParser();
		Resources getData();
		void read(const std::string& filename);
		void write(const std::string& filename) const;
		bool isVariable(const std::string& line, const std::string& searchItem, std::string& value);
		bool isCategory(const std::string& line, const std::string& searchItem, std::vector<std::string>& argv);
	};
}

#endif
