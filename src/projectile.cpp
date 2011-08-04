#include "projectile.h"

using namespace engine;

Projectile::Projectile(Image* image, Sprite* origin, bool top, int xvel, int yvel)
	: Sprite(image, (origin->getWidth()/2) + origin->getX(), 
	top ? origin->getY() - (image->getHeight() + 1) 
	: origin->getY() + origin->getHeight() + image->getHeight(), xvel, yvel) {
}