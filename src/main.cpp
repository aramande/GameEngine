#include <cxxtest/ErrorPrinter.h>
#include <iostream>
#include <window.h>
#include <gameengine.h>

using namespace engine;
int main(int argc, char **argv){
	Window* screen = new Window(640, 480, 32);
	GameEngine* game = GameEngine::init(screen);
	// game.run();
	return 0;
}
