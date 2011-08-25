#include "font.h"
#include "logger.h"
#include "fileexception.h"

namespace engine{
	Font::Font(std::string name){
		size = 18;
		path = "";
		filename = "";
		final = false;
	}

	Font::~Font(){
		if(final){
			free(font);
			font = NULL;
		}
	}

	void Font::setSize(int size){
		if(final) return;
		logger->printf("Font size is set to %d", size);
		this->size = size;
	}
	void Font::setFile(std::string path, std::string filename){
		if(final) return;
		this->path = path;
		this->filename = filename;
	}
	void Font::finalize(){
		if(final) return;
		final = true;
		font = TTF_OpenFont((path + filename).c_str(), size);
		if(font == NULL){
			throw file_exception("Could not load font: " + path + filename);
		}
	}

	std::string Font::getFilename() const{
		return filename;
	}

	TTF_Font* Font::getTTF() const{
		return font;
	}
}
