#include <string>
#include "image.h"
#include "fileexception.h"
#include "cconfig.h"
#include "resource.h"

using namespace std;
namespace engine{
	//Image::Image(string path, string filename, bool alpha, bool pixel){
	Image::Image(string name){
		setName(name);
		alpha = false;
		pixel = false;
		path = "";
		filename = "";
		final = false;
	}

	Image::~Image(){
		if(final)
			SDL_FreeSurface(image);
	}

	void Image::finalize(){
		if(final) return;
		if(filename == "")
			throw file_exception("Missing filename for image '" + getName() + "'");
		SDL_Surface* loadedImage = IMG_Load((path+filename).c_str()); 
		final = true;
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
			throw file_exception("Could not load image: "+path+filename);
		}
		//this->filename = filename;
		w = image->clip_rect.w;
		h = image->clip_rect.h;
	}

	void Image::setPixel(bool pixel){
		if(final) return;
		this->pixel = pixel;
	}
	void Image::setAlpha(bool alpha){
		if(final) return;
		this->alpha = alpha;
	}
	void Image::setFile(std::string path, std::string filename){
		if(final) return;
		this->path = path;
		this->filename = filename;
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

	int Image::getWidth() const{
		return w;
	}
	
	int Image::getHeight() const{
		return h;
	}

	//Image* Image::copy() const{
	//	return Resource::loadImage(filename, alpha);
	//}

	std::string Image::getFilename() const{
		return filename;
	}

	SDL_Surface* Image::getSurface() const{
		return image;
	}
}
