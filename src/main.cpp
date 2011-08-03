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
					translate(0,-5);
					break;
				case SDLK_a:
					translate(-5,0);
					break;
				case SDLK_s:
					translate(0,5);
					break;
				case SDLK_d:
					translate(5,0);
					break;
			}
		}
	}

	void shoot(Event* event){
		if(!isDead())
			game->addSprite(new Projectile(Resource::loadImage("projectile.png"), this, false, 0, 2));
	}

	void tick(){
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
	game->addComponent(new Button(50, 100, Resource::loadImage("button.png"), &shutdown, "Quit"));
	Player* player = new Player();
	
	FunctionListener* shutdownListener = new FunctionListener();
	shutdownListener->setFunction(&shutdown);
	EventHandler::addAction(SDLK_ESCAPE, shutdownListener);

	ClassListener<Player>* moveListener = new ClassListener<Player>();
	moveListener->setFunction(player, &Player::movement);
	EventHandler::addAction(SDLK_w, moveListener);
	EventHandler::addAction(SDLK_a, moveListener);
	EventHandler::addAction(SDLK_s, moveListener);
	EventHandler::addAction(SDLK_d, moveListener);
	
	ClassListener<Player>* shootListener = new ClassListener<Player>();
	shootListener->setFunction(player, &Player::shoot);
	EventHandler::addAction(SDLK_SPACE, shootListener);
	
	player->onCollision(&collisionDeath);
	Sprite* enemy = new Enemy();
	enemy->onCollision(&collisionDeath);
	Projectile* p = new Projectile(Resource::loadImage("projectile.png"),
		player, false, 1, 8);

	game->addSprite(player);
	game->addSprite(enemy);
	game->addSprite(p);
	game->run();
	return 0;
}

void shutdown(engine::Event* event){
	engine::GameEngine::doQuit();
}

void collisionDeath(engine::Sprite* self, const engine::Sprite* other){
	self->kill();
}