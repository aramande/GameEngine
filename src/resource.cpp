#include <string>
#include "badarg.h"
#include "logger.h"
#include "cconfig.h"
#include "resource.h"
#include "fileexception.h"

namespace engine{
	std::map<std::string, Image*> Resource::loadedImages = std::map<std::string, Image*>();
	std::map<std::string, TTF_Font*> Resource::loadedFonts = std::map<std::string, TTF_Font*>();
	std::map<std::string, int> Resource::count = std::map<std::string, int>();
	
	Image* Resource::loadImage(std::string filename, bool alpha, bool pixel){
		Image* result = NULL;

		// If image already exists
		if(loadedImages.find(filename) != loadedImages.end()){
			result = loadedImages[filename];
			count[filename]++;
		}
		else{
			result = new Image((std::string)DATA_DIR + "/img/", filename, alpha, pixel);
			loadedImages[filename] = result;
			count[filename] = 1;
		}
		return result;
	}

	void Resource::unloadImage(std::string filename){
		if(loadedImages.find(filename) != loadedImages.end()){
			if(--(count[filename])==0){
				logger->printf("Unloading %s from resources", filename.c_str());
				delete loadedImages[filename];
				loadedImages.erase(filename);
			}
		}
	}
	
	void Resource::unloadImage(Image* img) {
		if(img == NULL)
			throw bad_arg("Trying to unload a null image pointer");
		logger->printf("Unloading image: %p", img);
		unloadImage(img->getFilename());
	}

	
	TTF_Font* Resource::loadFont(std::string filename, int size){
		TTF_Font* result;
		std::string id = filename+toStr(size);
		// If font already loaded
		if(loadedFonts.find(id) != loadedFonts.end()){
			result = loadedFonts[id];
			count[id]++;
		}
		else{
			result = TTF_OpenFont(((std::string)DATA_DIR + "/fonts/" + filename).c_str(), size);
			if(result == NULL){
				throw file_exception("Could not load font: " + (std::string)DATA_DIR + "/fonts/" + filename);
			}
			loadedFonts[id] = result;
			count[id] = 1;
		}
		return result;
		
	}

	void Resource::unloadFont(std::string filename, int size){
		if(loadedFonts.find(filename) != loadedFonts.end()){
			if(--(count[filename])==0){
				free(loadedFonts[filename]);
				loadedFonts.erase(filename);
			}
		}
	}
}
