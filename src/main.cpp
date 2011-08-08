#include <cxxtest/ErrorPrinter.h>
#include <iostream>
#include <gameengine.h>
#include "projectile.h"

using namespace engine;
using namespace std;
void spawnEnemy(int timeSinceLastFrame);
void shutdown(const engine::Event* event);
void collisionDeath(engine::Sprite* self, const engine::Sprite* other);
void playerEnemyCollision(engine::Sprite* self, const engine::Sprite* other);
void projectileEnemyCollision(engine::Sprite* self, const engine::Sprite* other);
class Player;

GameEngine* game;
Window* screen;
ClassListener<Player>* moveListener;
ClassListener<Player>* shootListener;
int level;

class Player : public Sprite{
public:
	Player() : Sprite(Resource::loadImage("player.png")){

	}

	~Player(){
		EventHandler::removeAction(SDLK_w);
		EventHandler::removeAction(SDLK_a);
		EventHandler::removeAction(SDLK_d);
		EventHandler::removeAction(SDLK_s);
		EventHandler::removeAction(SDLK_SPACE);
		delete moveListener;
		moveListener = NULL;
		delete shootListener;
		shootListener = NULL;
	}
	
	void movement(const Event* event){
		const KeyEvent* keyEvent = dynamic_cast<const KeyEvent*>(event);
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

	void shoot(const Event* event){
		if(!isDead()){
			Projectile* lazer = new Projectile(Resource::loadImage("projectile.png", false), this, true, 0, -3);
			lazer->onCollision(&projectileEnemyCollision);
			game->addSprite(lazer);
		}
	}

	void tick(){
		Sprite::tick();
	}
};

class Enemy : public Sprite{
public:
	Enemy(std::string filename, int xPos, int ySpeed) : Sprite(Resource::loadImage(filename, true, true), xPos, -20, 0, ySpeed){

	}
};

int main(int argc, char **argv){
	level = 8;
	screen = Window::init(640, 480, 32);
	game = GameEngine::init(screen);
	
	FunctionListener* shutdownListener = new FunctionListener(&shutdown);
	game->addComponent(new Button(50, 100, Resource::loadImage("button.png"), "Quit", shutdownListener));
	Player* player = new Player();

	EventHandler::addAction(SDLK_ESCAPE, shutdownListener);
	
	moveListener = new ClassListener<Player>(player, &Player::movement);
	EventHandler::addAction(SDLK_w, moveListener);
	EventHandler::addAction(SDLK_a, moveListener);
	EventHandler::addAction(SDLK_s, moveListener);
	EventHandler::addAction(SDLK_d, moveListener);
	
	shootListener = new ClassListener<Player>(player, &Player::shoot);
	EventHandler::addAction(SDLK_SPACE, shootListener);
	player->onCollision(&playerEnemyCollision);
		
	game->addSprite(player);
	game->setAction(&spawnEnemy);
	game->run();

	return 0;
}

void spawnEnemy(int timeSinceLastFrame){
	if(rand() % 50 <= level){
		int speed = 1;
		int xpos = (rand() % (screen->getWidth() - 40)) + 20;
		Enemy* enemy = new Enemy("experiment.bmp", xpos, speed);
		enemy->onCollision(&collisionDeath);
		game->addSprite(enemy);
	}
}

void shutdown(const engine::Event* event){
	engine::GameEngine::doQuit();
}

void collisionDeath(engine::Sprite* self, const engine::Sprite* other){
	if (dynamic_cast<const Enemy*>(other) == NULL) {
		Logger::init()->print("An enemy collided with something.");
		self->kill();
	}
}

void playerEnemyCollision(engine::Sprite* self, const engine::Sprite* other) {
	if (dynamic_cast<const Enemy*>(other) != NULL) {
		self->kill();
		Logger::init()->print("Our hero has died.");
	}
}

void projectileEnemyCollision(engine::Sprite* self, const engine::Sprite* other) {
	if (dynamic_cast<const Enemy*>(other) != NULL) {
		self->kill();
		Logger::init()->print("A projectile has collided with an enemy.");
	}
	else if (other == NULL){
		self->kill();
		Logger::init()->print("A projectile has collided with a wall.");
	}
}
