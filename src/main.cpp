#include <cxxtest/ErrorPrinter.h>
#include <iostream>
#include <gameengine.h>

using namespace engine;
using namespace std;
void shutdown(engine::Event* event);

class Player : public Sprite{
public:
	Player() : Sprite(Resource::loadImage("testimage.png")){

	}

	void tick(){
		translate(1, 1);

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
	GameEngine* game = GameEngine::init(screen);
	EventHandler::addAction(SDLK_ESCAPE, &shutdown);
	//EventHandler::addAction(SDL_BUTTON_LEFT, &shutdown);
	game->addComponent(new Button(50, 100, Resource::loadImage("button.png"), &shutdown));
	game->addSprite(new Player());
	game->addSprite(new Enemy());
	game->run();
	return 0;
}

void shutdown(engine::Event* event){
	engine::GameEngine::doQuit();
}