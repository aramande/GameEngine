#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameengine.h"

class Projectile : public engine::Sprite {
public:
	Projectile(engine::Image* image, engine::Sprite* origin, bool top, int xvel, int yvel);
};


#endif