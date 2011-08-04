#include <cxxtest/ErrorPrinter.h>
#include <iostream>
#include <gameengine.h>
#include "projectile.h"

using namespace engine;
using namespace std;
void shutdown(engine::Event* event);
void collisionDeath(engine::Sprite* self, const engine::Sprite* other);
GameEngine* game;

class Player : public Sprite{
public:
	Player() : Sprite(Resource::loadImage("player.png")){

	}
	
	void movement(Event* event){
		KeyEvent* keyEvent = dynamic_cast<KeyEvent*>(event);
		if(!isDead() && keyEvent != NULL){
			switch(keyEvent->getKey()){
				case SDLK_w:
					if (keyEvent->isPressed())
						setYVelocity(yVelocity-5);
					else
						setYVelocity(yVelocity+5);
					break;
				case SDLK_a:
					if (keyEvent->isPressed())
						setXVelocity(xVelocity-5);
					else
						setXVelocity(xVelocity+5);
					break;
				case SDLK_s:
					if (keyEvent->isPressed())
						setYVelocity(yVelocity+5);
					else
						setYVelocity(yVelocity-5);
					break;
				case SDLK_d:
					if (keyEvent->isPressed())
						setXVelocity(xVelocity+5);
					else					
						setXVelocity(xVelocity-5);
					break;
			}
		}
	}

	void shoot(Event* event){
		if(!isDead())
			game->addSprite(new Projectile(Resource::loadImage("projectile.png"), this, true, 0, -3));
	}

	void tick(){
		Sprite::tick();
	}
};

class Enemy : public Sprite{
public:
	Enemy() : Sprite(Resource::loadImage("testimage.png"), 300, 200){

	}

	void tick(){
		translate(-1, -1);
	}
};

int main(int argc, char **argv){
	Window* screen = Window::init(640, 480, 32);
	game = GameEngine::init(screen);
	
	FunctionListener* shutdownListener = new FunctionListener(&shutdown);
	game->addComponent(new Button(50, 100, Resource::loadImage("button.png"), "Quit", shutdownListener));
	Player* player = new Player();

	EventHandler::addAction(SDLK_ESCAPE, shutdownListener);
	
	ClassListener<Player>* moveListener = new ClassListener<Player>(player, &Player::movement);
	EventHandler::addAction(SDLK_w, moveListener);
	EventHandler::addAction(SDLK_a, moveListener);
	EventHandler::addAction(SDLK_s, moveListener);
	EventHandler::addAction(SDLK_d, moveListener);
	
	ClassListener<Player>* shootListener = new ClassListener<Player>(player, &Player::shoot);
	EventHandler::addAction(SDLK_SPACE, shootListener);
	
	player->onCollision(&collisionDeath);
	Sprite* enemy = new Enemy();
	enemy->onCollision(&collisionDeath);

	game->addSprite(player);
	game->addSprite(enemy);
	game->run();

	return 0;
}

void shutdown(engine::Event* event){
	engine::GameEngine::doQuit();
}

void collisionDeath(engine::Sprite* self, const engine::Sprite* other){
	self->kill();
}