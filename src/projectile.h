#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameengine.h"

class Projectile : public engine::Sprite {
	int xVelocity;
	int yVelocity;
protected:
public:
	Projectile(engine::Image* image, int x, int y, int xvel, int yvel);
	Projectile(engine::Image* image, engine::Sprite* origin, bool top, int xvel, int yvel);
};


#endif