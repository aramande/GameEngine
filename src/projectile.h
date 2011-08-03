#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameengine.h"

class Projectile : public engine::Sprite {
	Projectile(Image* image, Sprite, int xvel, int yvel);
	int velocity;
protected:
public:
	void tick();

	int getXVelocity();
	int getYVelocity();

	void setXVelocity();
	void setYVelocity();

	void setVelocity(int xvel, int yvel);

};


#endif