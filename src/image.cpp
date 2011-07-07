#include <string>
#include "image.h"
#include "fileexception.h"

using namespace std;
namespace engine{
	Image::Image(string filename){
		SDL_Surface* loadedImage = IMG_Load(filename.c_str()); 
		if(loadedImage != NULL){ 
			image = SDL_DisplayFormat(loadedImage); 
			SDL_FreeSurface(loadedImage); 
		}
		else{
			throw file_exception("Could not load image: "+filename);
		}
		w = image->clip_rect.w;
		h = image->clip_rect.h;
	}

	Image::~Image(){
		SDL_FreeSurface(image);
	}
	
	int Image::getWidth(){
		return w;
	}
	
	int Image::getHeight(){
		return h;
	}
}