#include <string>
#include "image.h"
#include "fileexception.h"
#include "cconfig.h"
#include "resource.h"

using namespace std;
namespace engine{
	Image::Image(string filename){
		SDL_Surface* loadedImage = IMG_Load(filename.c_str()); 
		if(loadedImage != NULL){ 
			image = SDL_DisplayFormatAlpha(loadedImage); 
			SDL_FreeSurface(loadedImage); 
		}
		else{
			throw file_exception("Could not load image: "+filename);
		}
		this->filename = filename;
		w = image->clip_rect.w;
		h = image->clip_rect.h;
	}

	Image::~Image(){
		SDL_FreeSurface(image);
	}
	
	int Image::getWidth() const{
		return w;
	}
	
	int Image::getHeight() const{
		return h;
	}

	Image* Image::copy() const{
		return Resource::loadImage(filename);
	}

	std::string Image::getFilename() const{
		return filename;
	}

	SDL_Surface* Image::getSurface() const{
		return image;
	}
}