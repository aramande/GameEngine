#include <cxxtest/ErrorPrinter.h>
#include <ctime>
#include <iostream>
#include <gameengine.h>
#include "projectile.h"
#include "highscore.h"

using namespace engine;
using namespace std;
void registerName();
void spawnEnemy(int timeSinceLastFrame);
void shutdown(const engine::Event* event);
void collisionDeath(engine::Sprite* self, const engine::Sprite* other);
void playerEnemyCollision(engine::Sprite* self, const engine::Sprite* other);
void projectileEnemyCollision(engine::Sprite* self, const engine::Sprite* other);
class Player;

GameEngine* game;
Window* screen;
Label* currentScore;
ClassListener<Player>* moveListener;
ClassListener<Player>* shootListener;
int level = 0;
int spawnEnemyCounter = 0;
long score = 0;
bool gameover = false;
bool waiting = false;
bool submitting = false;

class Player : public Sprite{
public:
	Player() : Sprite(Resource::loadImage("player.png")){

	}

	Player(int x, int y) : Sprite(Resource::loadImage("player.png"), x, y){

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
		if(const KeyEvent* keyEvent = dynamic_cast<const KeyEvent*>(event)){
			if(!isDead() && keyEvent->isPressed()){
				Projectile* lazer = new Projectile(Resource::loadImage("projectile.png", false), this, true, 0, -3);
				lazer->onCollision(&projectileEnemyCollision);
				game->addSprite(lazer);
			}
		}
	}

	void tick(){
		Sprite::tick();
	}
};

class Enemy : public Sprite{
 public:
  Enemy(std::string filename, int xPos, int yPos, int ySpeed) : 
	  Sprite(Resource::loadImage(filename, true), xPos, yPos, 0, ySpeed){

  }
};

int main(int argc, char **argv){
	screen = Window::init(640, 480, 32);
	game = GameEngine::init(screen);

	FunctionListener* shutdownListener = new FunctionListener(&shutdown);
	//game->addComponent(new Button(50, 100, Resource::loadImage("button.png"), "Quit", shutdownListener));
	currentScore = new Label(10, 460, "Score: " + toStr(score) + " Level: " + toStr(level));
	game->addComponent(currentScore);
	//registerName();
	Player* player = new Player(screen->getWidth()/2, screen->getHeight()/2);

	EventHandler::addAction(SDLK_ESCAPE, shutdownListener);

	moveListener = new ClassListener<Player>(player, &Player::movement);
	EventHandler::addAction(SDLK_w, moveListener);
	EventHandler::addAction(SDLK_a, moveListener);
	EventHandler::addAction(SDLK_s, moveListener);
	EventHandler::addAction(SDLK_d, moveListener);

	shootListener = new ClassListener<Player>(player, &Player::shoot);
	EventHandler::addAction(SDLK_SPACE, shootListener);
	player->onCollision(&playerEnemyCollision);

	srand(time(NULL));

	game->addSprite(player);
	game->setAction(&spawnEnemy);
	game->run();

	return 0;
}

Label* highscoreLabel;
Input* nameInput;
FunctionListener* submitListener;
Button* submitButton;

void submit(const Event* event){
	const MouseEvent* mev = dynamic_cast<const MouseEvent*>(event);
	if(mev != NULL && mev->isPressed()){	
		Highscore::addScore(nameInput->getText(), score);
		waiting = false;
		submitting = true;
	}
}

void registerName(){
	highscoreLabel = new Label(300, 180, "Type your name please!");
	game->addComponent(highscoreLabel);
	SDL_Color red = {255, 0, 0};
	highscoreLabel->setColor(red);
	highscoreLabel->setFont(Resource::loadFont("FreeUniversal-Bold.ttf"));
	
	nameInput = new Input(300, 200, 10);
	game->addComponent(nameInput);

	submitListener = new FunctionListener(&submit);
	submitButton = new Button(300, 220, Resource::loadImage("button.png", false), "Submit", submitListener);
	game->addComponent(submitButton);
}

void spawnEnemy(int timeSinceLastFrame){
	if(waiting){

	}
	else if(spawnEnemyCounter == (level*10+15)) 
	{
		spawnEnemyCounter = 0;
		++level;
	}
	else if(gameover){
		game->removeAllSprites();
		registerName();
		waiting = true;
		gameover = false;
	}
	else if(submitting){
		game->removeComponent(highscoreLabel);
		game->removeComponent(nameInput);
		game->removeComponent(submitButton);
		delete submitListener;
		
		Highscore scoreboard(game);
		waiting = true;
		submitting = false;
	}
	else{ // Game is running
		if(rand() % 50 <= level){
			int speed = level/10 + 1;
			++spawnEnemyCounter;
			int xpos = (rand() % (screen->getWidth() - 40)) + 20;
			Enemy* enemy;
			if(rand()%2 == 0)
				enemy = new Enemy("squid.png", xpos, -15, speed);
			else
				enemy = new Enemy("enemy.png", xpos, screen->getHeight(), -1);

			enemy->onCollision(&collisionDeath);
			game->addSprite(enemy);
		}
	}
}

void updateScore(){
	currentScore->setText("Score: " + toStr(score) + " Level: " + toStr(level));
}

void shutdown(const engine::Event* event){
	engine::GameEngine::doQuit();
}

void collisionDeath(engine::Sprite* self, const engine::Sprite* other){
	if (dynamic_cast<const Enemy*>(other) == NULL) {
		
		// Retract half points for missed enemies
		if(other == NULL){
			if(!self->isDead()){
				if(!(gameover || submitting || waiting)){
					score -= 5 * level + 5;
					updateScore();
				}
				logger->print("An enemy collided with a wall.");
				self->kill();
			}
		}
		else{
			if(!self->isDead()){
				logger->print("An enemy collided with something.");
				self->kill();
			}
		}
	}
}

void playerEnemyCollision(engine::Sprite* self, const engine::Sprite* other) {
	if (dynamic_cast<const Enemy*>(other) != NULL) {
		//self->kill();
		//Can't kill player here, causes segmentation fault for some reason, is
		//removed by spawnMonster(const Event*);
		gameover = true;
		logger->print("Our hero has died.");
	}
}

void projectileEnemyCollision(engine::Sprite* self, const engine::Sprite* other) {
	if (dynamic_cast<const Enemy*>(other) != NULL) {
		if(!self->isDead() && !(gameover || submitting || waiting)){
			score += 10*level+10;
			updateScore();
		}
		if(!self->isDead()){
			self->kill();
			// Add 10 points per level per killed enemy
			logger->print("A projectile has collided with an enemy.");
		}
	}
	else if (other == NULL){
		if(!self->isDead()){
			self->kill();
			logger->print("A projectile has collided with a wall.");
		}
	}
}
