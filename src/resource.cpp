#include <string>
#include "resource.h"
#include "logger.h"
#include "cconfig.h"
#include "fileexception.h"

namespace engine{
	std::map<std::string, Image*> Resource::loadedImages = std::map<std::string, Image*>();
	std::map<Image*, std::string> Resource::imageNames = std::map<Image*, std::string>();
	std::map<std::string, int> Resource::imageCount = std::map<std::string, int>();
	std::map<std::string, TTF_Font*> Resource::loadedFonts = std::map<std::string, TTF_Font*>();
	std::map<std::string, int> Resource::fontCount = std::map<std::string, int>();
	
	Image* Resource::loadImage(std::string filename){
		Image* result = NULL;

		// If image already exists
		if(loadedImages.find(filename) != loadedImages.end()){
			result = loadedImages[filename];
			imageCount[filename]++;
		}
		else{
			result = new Image((std::string)DATA_DIR + "/img/" + filename);
			loadedImages[filename] = result;
			imageNames[result] = filename;
			imageCount[filename] = 0;
		}
		return result;
	}

	void Resource::unloadImage(std::string filename){
		if(loadedImages.find(filename) != loadedImages.end()){
			if(imageCount[filename]==0){
				imageNames.erase(loadedImages[filename]);
				delete loadedImages[filename];
				loadedImages.erase(filename);
			}
		}
	}
	
	void Resource::unloadImage(Image* img) {
		if(imageNames.find(img) != imageNames.end()){
			if(imageCount[imageNames[img]] == 0) {
				delete loadedImages[imageNames[img]];
				loadedImages.erase(imageNames[img]);
				imageNames.erase(img);
			}
		}		
	}

	
	TTF_Font* Resource::loadFont(std::string filename, int size){
		TTF_Font* result;
		std::string id = filename+Logger::toStr(size);
		// If font already loaded
		if(loadedFonts.find(id) != loadedFonts.end()){
			result = loadedFonts[id];
			fontCount[id]++;
		}
		else{
			result = TTF_OpenFont(((std::string)DATA_DIR + "/fonts/" + filename).c_str(), size);
			if(result == NULL){
				throw file_exception("Could not load font: " + (std::string)DATA_DIR + "/fonts/" + filename);
			}
			loadedFonts[id] = result;
			fontCount[id] = 0;
		}
		return result;
		
	}

	void Resource::unloadFont(std::string filename, int size){
		if(loadedFonts.find(filename) != loadedFonts.end()){
			if(fontCount[filename]==0){
				free(loadedFonts[filename]);
				loadedFonts.erase(filename);
			}
		}
	}
}