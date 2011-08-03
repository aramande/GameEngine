#include "projectile.h"

using namespace engine;

Projectile::Projectile(Image* image, int x, int y, int xvel, int yvel) 
	: Sprite(image, x, y) {
	
	xVelocity = xvel;
	yVelocity = yvel;
}

void Projectile::tick() {
	translate(xVelocity, yVelocity);
}

int Projectile::getXVelocity() {
	return xVelocity;
}
int Projectile::getYVelocity() {
	return yVelocity;
}

void Projectile::setXVelocity(int xvel) {
	xVelocity = xvel;
}
void Projectile::setYVelocity(int yvel) {
	yVelocity = yvel;
}

void Projectile::setVelocity(int xvel, int yvel) {
	xVelocity = xvel;
	yVelocity = yvel;
}