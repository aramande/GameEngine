#include "sprite.h"
#include "badarg.h"
#include "window.h"
#include "fileexception.h"

#include "sdl.h"

using namespace std;

namespace engine{
	Sprite::Sprite(Image* image, int x, int y){
		this->image = image;
		rect = new Rectangle(x, y, image->getWidth(), image->getHeight());
	}
	Sprite::~Sprite() {
		Resource::unloadImage(image);
		image = NULL;
	}
	int Sprite::getX(){
		return rect->x;
	}

	int Sprite::getY(){
		return rect->y;
	}

	int Sprite::getWidth(){
		return rect->w;
	}

	int Sprite::getHeight(){
		return rect->h;
	}

	Rectangle* Sprite::getRectangle() const{
		return rect;
	}

	void Sprite::tick(){

	}

	void Sprite::repaint() const{
		draw();
	}

	void Sprite::draw() const{
		SDL_BlitSurface(image->getSurface(), NULL, mainScreen, &rect->getSDL_Rect());
	}

	void Sprite::translate(int x, int y){
		rect->x += x;
		rect->y += y;
	}

	void Sprite::moveTo(int x, int y){
		rect->x = x;
		rect->y = y;
	}

	void Sprite::resize(int w, int h){
		if(w < 0 || h < 0) 
			throw bad_arg("Can't have a negative area");
		rect->w = w;
		rect->h = h;
	}

	bool Sprite::collidesWith(const Sprite* other) const{
		return rect->overlaps(*(other->getRectangle()));
	}
	
	void Sprite::onCollision(Func action){
		this->action = action;
	}

	void Sprite::collide(Sprite* other) {
		(*action)(other);
	}
}
