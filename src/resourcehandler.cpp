#include <fstream>
#include <iostream>
#include "resourcehandler.h"
#include "fileexception.h"
#include "resource.h"
#include "cconfig.h"
#include "logger.h"
#include "badarg.h"

namespace engine{

	ResourceHandler* ResourceHandler::self = NULL;

	ResourceHandler::ResourceHandler(){
	}

	ResourceHandler::~ResourceHandler(){
	}

	ResourceHandler* ResourceHandler::init(){
		if(self == NULL)
			self = new ResourceHandler();
		return self;
	}

	bool ResourceHandler::hasKey(const std::string& key) const{
		return resources.find(key) != resources.end();
	}

	/**
	 * Unloads all resources and deletes the resource handler instance
	 */
	void ResourceHandler::destroy(){
		if(self != NULL){
			logger->print("Destroying resource handler");
			self->cleanUp();
			delete self;
			self = NULL;
		}
	}

	void ResourceHandler::cleanUp(){
		for(ResourceIterator it = resources.begin(); it != resources.end(); ++it){
			if(it->second->getRefCount() != 0)
				logger->printf("Warning: Resource %s had %d references left at deletion time, please look into it", it->first.c_str(), it->second->getRefCount());
			delete it->second;
		}
		resources.clear();
	}

	Resource* ResourceHandler::getResource(const std::string& name){
		logger->printf("Retrieving resource: %s", name.c_str());
		if(!hasKey(name)){
			logger->printf("Warning: Couldn't find a resource by name %s", name.c_str());
			return NULL;
		}

		Resource* result = resources[name];
		++*result;
		return result;
	}
	Image* ResourceHandler::getImage(const std::string& name){
		Image* result = dynamic_cast<Image*>(getResource(name));
		logger->printf("Getting image: %s -> %p", name.c_str(), result);
		return result;
	}
	Font* ResourceHandler::getFont(const std::string& name){
		Font* result = dynamic_cast<Font*>(getResource(name));
		logger->printf("Getting font: %s -> %p", name.c_str(), result);
		return result;
	}

	const std::string& ResourceHandler::getName(const Resource* resource) const{
		return resource->getName();
	}

	void ResourceHandler::loadResourceFile(const std::string& filename, ResourceParser* parse) {
		logger->printf("Loading new resourcefile: %s to %p", filename.c_str(), &resources);
		Resources result;
		if(parse == NULL){
			parse = new ResourceParser();
		}
		logger->print("Parsing file...");
		parse->read(filename);
		result = parse->getData();
		resources.insert(result.begin(), result.end());
		logger->print("... Done!");
	}

	bool ResourceHandler::release(const std::string& name){
		if(hasKey(name))
			return resources[name]->release();
		else
			throw bad_arg("Couldn't find a resource by name '" + name + "', did you already unload it perhaps?");
		return false;
	}

	/////////////////////////////////////////////////////////
	// ResourceParser:
	ResourceParser::ResourceParser(){}

	ResourceParser::~ResourceParser(){}

	bool ResourceParser::isVariable(const std::string& line, const std::string& searchItem, std::string& value){
		if(!startsWith(line, searchItem))
			return false;
		//logger->printf("Variable starts with %s", searchItem.c_str());
		size_t equalLocation = line.find('=');
		if(equalLocation == std::string::npos)
			return false;
		//logger->printf("Variable contains =");

		value = std::string(line.begin()+equalLocation+1, line.end());
		value = trimRight(value, " ;");
		value = trimLeft(value, " \t");
		logger->printf("Read '%s' got variable value '%s'", line.c_str(), value.c_str());
		return true;
	}

	bool ResourceParser::isCategory(const std::string& line, const std::string& searchItem, std::vector<std::string>& argv){
		if(!startsWith(line, searchItem))
			return false;
		argv = split(line, ' ');
		std::string last = argv[argv.size()-1];
		
		// Parse opening brace at end of line
		if(endsWith(last, "{")){
			argv[argv.size()-1] = last.substr(0, last.length()-1);
			argv.push_back("{");
		}

		// Remove category name from argv
		argv.erase(argv.begin());

		return true;
	}


	ResourceParser::Resources ResourceParser::getData(){
		return storage;
	}

	void ResourceParser::read(const std::string& filename){
		std::ifstream file(((std::string)DATA_DIR+"/"+filename).c_str());
		Resource* result;
		std::vector<std::string> argv;
		std::string value;
		std::string currentLine = "";
		char* buffer = new char[512];
		int linenr = 0;

		if(!file.good())
			throw file_exception("Couldn't read '" + (std::string)DATA_DIR + "/" + filename + "'");

		this->filename = filename;
		currentLine = ignoreComments(file, linenr);

		// First valid line must be the version number of the file format
		if(!isVariable(currentLine, "version", value))
			throw file_exception(filename + ":" + toStr(linenr) + ": Couldn't find version information variable");
		if(value != "1")
			throw file_exception(filename + ":" + toStr(linenr) + ": Incompatible version number");

		while(!file.eof()){
			file.getline(buffer, 512);
			currentLine = buffer;
			++linenr;

			if(consistsOf(currentLine, "") ||
			   startsWith(currentLine, "//"))
				; // Do nothing
			else if(isCategory(currentLine, "image", argv)){
				if(argv.size() == 0 || argv.size() > 2)
					throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: " + toStr(argv.size()) + " is an illegal amount of arguments");
				parseImage(file, linenr, argv[0], argv[1] == "{");
			}
			else if(isCategory(currentLine, "font", argv)){
				if(argv.size() == 0 || argv.size() > 2)
					throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: " + toStr(argv.size()) + " is an illegal amount of arguments");
				parseFont(file, linenr, argv[0], argv[1] == "{");
			}
			// Later usage
			//else if(isCategory(currentLine, "font", args));
			//else if(isCategory(currentLine, "sprite", args));
			else{
				throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: Unknown category");
			}
		}

		delete[] buffer;
		file.close();
	}

	void ResourceParser::parseImage(std::ifstream& file, int& linenr, std::string name, bool hadBrace){
		logger->print(filename + ":"+toStr(linenr)+": Parsing image '" + name + "'"); 
		std::string currentLine = "";
		char* buffer = new char[512];
		std::string value;
		
		if(ResourceHandler::init()->hasKey(name)){
			logger->print(filename + ":"+toStr(linenr)+": Warning: The resource name '" + name + "' is already loaded, ignoring.");
			while(!file.eof()){
				file.getline(buffer, 512);
				currentLine = buffer;
				++linenr;
				if(consistsOf(currentLine, "}")) 
					return; // Do nothing
			}
		}

		currentLine = ignoreComments(file, linenr);
		
		if(!hadBrace){
			if(contains(currentLine, "{")){
				if(!consistsOf(currentLine, "{"))
					throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: Tokens around the brace");
				else{
					// Found bracket, increase line reader
					file.getline(buffer, 512);
					currentLine = buffer;
					++linenr;
				}
			}
			else{
				throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: No opening brace found");
			}
		}


		Image* image = new Image(name);
		while(!file.eof()){
			if(consistsOf(currentLine, "") ||
			   startsWith(currentLine, "//"))
				; // Do nothing
			else if(isVariable(currentLine, "filename", value)){
				image->setFile((std::string)DATA_DIR + "/", value);
			}
			else if(isVariable(currentLine, "alpha", value)){
				image->setAlpha(value == "true");
			}
			else if(isVariable(currentLine, "pixel", value)){
				image->setPixel(value == "true");
			}
			else if(contains(currentLine, "}")){
				if(!consistsOf(currentLine, "}"))
					throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: Tokens around the brace");
				image->finalize();
				storage[name] = image;
				break;
			}
			else
				logger->print(filename + ":"+toStr(linenr)+": Warning: Didn't understand, are you sure you did this right?");
			file.getline(buffer, 512);
			currentLine = buffer;
			++linenr;
		}
	}

	void ResourceParser::parseFont(std::ifstream& file, int& linenr, std::string name, bool hadBrace){
		logger->print(filename + ":"+toStr(linenr)+": Parsing font '" + name + "'"); 
		std::string currentLine = "";
		char* buffer = new char[512];
		std::string value;
		
		if(ResourceHandler::init()->hasKey(name)){
			logger->print(filename + ":"+toStr(linenr)+": Warning: The resource name '" + name + "' is already loaded, ignoring.");
			while(!file.eof()){
				file.getline(buffer, 512);
				currentLine = buffer;
				++linenr;
				if(consistsOf(currentLine, "}")) 
					return; // Do nothing
			}
		}
		currentLine = ignoreComments(file, linenr);
		
		if(!hadBrace){
			if(contains(currentLine, "{")){
				if(!consistsOf(currentLine, "{"))
					throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: Tokens around the brace");
				else{
					// Found bracket, increase line reader
					file.getline(buffer, 512);
					currentLine = buffer;
					++linenr;
				}
			}
			else{
				throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: No opening brace found");
			}
		}

		Font* font = new Font(name);
		while(!file.eof()){
			if(consistsOf(currentLine, "") ||
			   startsWith(currentLine, "//"))
				; // Do nothing
			else if(isVariable(currentLine, "filename", value)){
				font->setFile((std::string)DATA_DIR + "/", value);
			}
			else if(isVariable(currentLine, "size", value)){
				logger->printf("%d", atoi(value.c_str()));
				font->setSize(atoi(value.c_str()));
			}
			else if(contains(currentLine, "}")){
				if(!consistsOf(currentLine, "}"))
					throw file_exception(filename + ":"+toStr(linenr)+": Syntax error: Tokens around the brace");
				font->finalize();
				storage[name] = font;
				break;
			}
			else
				logger->print(filename + ":"+toStr(linenr)+": Warning: Didn't understand, are you sure you did this right?");
			file.getline(buffer, 512);
			currentLine = buffer;
			++linenr;
			value = "";
		}
	}

	std::string ResourceParser::ignoreComments(std::ifstream& file, int& linenr){
		char* buffer = new char[512];
		std::string currentLine = "";
		while(!file.eof()){
			file.getline(buffer, 512);
			currentLine = buffer;
			++linenr;
			if(!consistsOf(currentLine, "") &&
			   !startsWith(currentLine, "//"))
				break;
		}
		return currentLine;
	}

	void ResourceParser::write(const std::string& filename) const{

	}

}
