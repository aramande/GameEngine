#include "sprite.h"
#include "badarg.h"
#include "window.h"
#include "fileexception.h"
#include "sdl.h"

using namespace std;

namespace engine{
	Sprite::Sprite(Image* image, int x, int y, int xvel, int yvel){
		this->image = image;
		rect = new Rectangle(x, y, image->getWidth(), image->getHeight());
		action = &dummy;
		dead = false;
		xVelocity = xvel;
		yVelocity = yvel;
	}
	Sprite::~Sprite() {
		Resource::unloadImage(image);
		image = NULL;
		action = &dummy;
		delete rect;
		rect = NULL;
	}
	int Sprite::getX() const{
		if(rect != NULL)
			return rect->x;
		return 0;
	}

	int Sprite::getY() const{
 		if(rect != NULL)
			return rect->y;
		return 0;
	}

	int Sprite::getWidth() const{
		if(rect != NULL)
			return rect->w;
		return 0;
	}

	int Sprite::getHeight() const{
		if(rect != NULL)
			return rect->h;
		return 0;
	}

	int Sprite::getXVelocity() const{
		return xVelocity;
	}
		
	int Sprite::getYVelocity() const{
		return yVelocity;
	}

	void Sprite::setVelocity(int x, int y) {
		xVelocity = x;
		yVelocity = y;
	}

	void Sprite::setXVelocity(int x) {
		xVelocity = x;
	}

	void Sprite::setYVelocity(int y) {
		yVelocity = y;
	}

	bool Sprite::isDead() const{
		return dead;
	}

	void Sprite::kill() {
		dead = true;
		Logger::init()->print("A sprite has died.");
	}

	Rectangle* Sprite::getRectangle() const{
		return rect;
	}

	void Sprite::tick(){
		if (!dead)
			translate(xVelocity, yVelocity);
	}

	void Sprite::repaint() const{
		draw();
	}

	void Sprite::draw() const{
		SDL_Rect temp = *rect;
		SDL_BlitSurface(image->getSurface(), NULL, mainScreen, &temp);
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
		if (other == this)
			return false;
		if (other == NULL){
			return !rect->overlaps(Rectangle(-1, -1, Window::init()->getWidth()+2, Window::init()->getHeight()+2));
		}
		return rect->overlaps(*(other->getRectangle()));
	}
	
	/**
	 * Expects a void function that takes a Sprite* as argument.
	 * This function will be called every frame where there's a collision detected for this sprite.
	 * If the sprite collides with the wall, the Sprite* will be NULL.
	 */
	void Sprite::onCollision(Func action){
		if(action == NULL) 
			return;
		this->action = action;
	}

	void Sprite::collide(Sprite* other) {
		if (other != this)
			(*action)(this, other);
	}
}
