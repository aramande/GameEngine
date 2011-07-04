#include "sprite.h"
#include "badarg.h"
#include "fileexception.h"

#include "sdl.h"

using namespace std;

namespace engine{
	Sprite::Sprite(string filename){
		SDL_Surface* loadedImage = IMG_Load(filename.c_str()); 
		if(loadedImage != NULL){ 
			image = SDL_DisplayFormat(loadedImage); 
			SDL_FreeSurface(loadedImage); 
		}
		else{
			throw file_exception("Could not load sprite image: "+filename);
		}
		x = 0;
		y = 0;
		w = image->clip_rect.w;
		h = image->clip_rect.h;
	}

	Sprite::~Sprite(){
		SDL_FreeSurface(image);
	}

	int Sprite::getX(){
		return x;
	}

	int Sprite::getY(){
		return y;
	}

	int Sprite::getWidth(){
		return w;
	}

	int Sprite::getHeight(){
		return h;
	}

	void Sprite::tick(){

	}

	void Sprite::draw() const{

	}

	void Sprite::translate(int x, int y){
		this->x += x;
		this->y += y;
	}

	void Sprite::moveTo(int x, int y){
		this->x = x;
		this->y = y;
	}

	void Sprite::resize(int w, int h){
		if(w < 0 || h < 0) 
			throw bad_arg("Can't have a negative area");
		this->w = w;
		this->h = h;
	}

	bool Sprite::collidesWith(const Sprite*) const{
		return false;
	}

	void Sprite::onCollision(Func action){

	}
}
