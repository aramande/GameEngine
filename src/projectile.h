#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameengine.h"

class Projectile : public engine::Sprite {
public:
	Projectile(engine::Image* image, const engine::Sprite* origin, bool top, int xvel = 0, int yvel = 0);
};


#endif