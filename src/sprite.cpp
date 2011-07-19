#include "sprite.h"
#include "badarg.h"
#include "window.h"
#include "fileexception.h"

#include "sdl.h"

using namespace std;

namespace engine{
	Sprite::Sprite(Image* image){
		this->image = image;
		x = 0;
		y = 0;
		w = image->getWidth();
		h = image->getHeight();
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

	void Sprite::repaint() const{
		draw();
	}

	void Sprite::draw() const{
		//x, y, image->getSurface(), Window::init()->screen);
		SDL_Rect offset;
		offset.x = x;
		offset.y = y;
		SDL_BlitSurface(image->getSurface(), NULL, Window::init()->screen, &offset);
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
