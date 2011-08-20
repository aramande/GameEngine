#include <string>
#include "image.h"
#include "fileexception.h"
#include "cconfig.h"
#include "resource.h"

using namespace std;
namespace engine{
	Image::Image(string path, string filename, bool alpha, bool pixel){
		SDL_Surface* loadedImage = IMG_Load((path+filename).c_str()); 
		if(loadedImage != NULL){ 
			if(alpha)
				if(pixel){
					image = SDL_DisplayFormat(loadedImage); 
					Uint8 red = 0, green = 0, blue = 0;
					SDL_GetRGB(getPixel(image, 0, 0), image->format, &red, &green, &blue);
					Uint32 colorkey = SDL_MapRGB(image->format, red, green, blue);
					SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
				}
				else
					image = SDL_DisplayFormatAlpha(loadedImage); 
			else
				image = SDL_DisplayFormat(loadedImage); 
			SDL_FreeSurface(loadedImage); 
		}
		else{
			throw file_exception("Could not load image: "+filename);
		}
		this->filename = filename;
		w = image->clip_rect.w;
		h = image->clip_rect.h;
	}

	Uint32 Image::getPixel(SDL_Surface* surf, int x, int y) const{
		SDL_LockSurface(surf);
		int bpp = surf->format->BytesPerPixel;
		char* p =(char*)surf->pixels + y*surf->pitch + x*bpp;
		Uint32 pixel;
		switch(bpp){
			case 1: pixel = *p; break;
			case 2: pixel =  *(Uint16*)p; break;
			case 3: 
				pixel = p[0] | p[1] << 8 | p[2] << 16; 
				break;
			case 4: pixel = *(Uint32*)p; break;
		}
		SDL_UnlockSurface(surf);
		return pixel;
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
		return Resource::loadImage(filename, alpha);
	}

	std::string Image::getFilename() const{
		return filename;
	}

	SDL_Surface* Image::getSurface() const{
		return image;
	}
}
