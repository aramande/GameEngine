#include <iostream>
#include "eventhandler.h"
#include "gameengine.h"
#include "mouseevent.h"
#include "keyevent.h"
#include "badarg.h"
#include "logger.h"
#include "event.h"
#include "sdl.h"

namespace engine{
	bool GameEngine::quit = false;
	GameEngine* GameEngine::instance = NULL;

	GameEngine::GameEngine(Window* main){
		if(main == NULL)
			throw bad_arg("Main window cannot be null");
		window = main;
		storage = new std::vector<Sprite*>();
		container = new std::vector<Component*>();
		fpsLimit = 60;
		fpsClock = new Timer();
	}

	GameEngine::~GameEngine(){
		storage->clear();
		delete storage;
		delete fpsClock;
	}

	GameEngine* GameEngine::init(Window* main){
		if(instance == NULL)
			instance = new GameEngine(main);
		return instance;
	}

	void GameEngine::setFPS(int fps){
		if(fps < 1)
			throw bad_arg("Negative FPS");
		fpsLimit = fps;
	}

	void GameEngine::addSprite(Sprite* sprite){
		if(sprite == NULL)
			throw bad_arg("Don't add null to the sprite list");
		Logger::init()->print("Adding sprite");
		storage->push_back(sprite);
	}

	void GameEngine::delSprite(Sprite* s) {
		for (unsigned int i = 0; i < storage->size(); i++) {
			if (storage->at(i) == s) {
				delete storage->at(i);
				Logger::init()->print("Removing sprite");
				storage->erase(storage->begin() + i);
			}
		}
	}

	void GameEngine::addComponent(Component* c) {
		if(c == NULL)
			throw bad_arg("Don't add null to the component list");
		Logger::init()->print("Adding component");
		container->push_back(c);
	}

	void GameEngine::delComponent(Component* c) {
		for (unsigned int i = 0; i < container->size(); i++) {
			if(container->at(i) == c) {
				Logger::init()->print("Removing componen.");
				delete container->at(i);
				container->erase(container->begin() + i);
			}
		}
	}

	void GameEngine::run(){
		Timer* timeSinceLastFrame = new Timer();
		SDL_Event curEvent;
		quit = false;
		int frame = 0;
		timeSinceLastFrame->start();
		while(!quit) {
			fpsClock->start();
			while(SDL_PollEvent(&curEvent)) {
				if (curEvent.type == SDL_QUIT)
					quit = true;
				switch (curEvent.type){
				case SDL_KEYDOWN:
					SDL_keysym keySymbol = curEvent.key.keysym;
					EventHandler::perform(keySymbol.sym, new KeyEvent(keySymbol.sym, 
						keySymbol.mod, true, timeSinceLastFrame->get_ticks()));
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_MouseButtonEvent click = curEvent.button;
					MouseEvent* mouseEvent = new MouseEvent(click.x, click.y, 
						click.button, true, false, timeSinceLastFrame->get_ticks());
					EventHandler::perform(click.button, mouseEvent);
					for (std::vector<Component*>::iterator it = container->begin(); it != container->end(); it++){
						(*it)->perform(mouseEvent);
					}
					break;
				}
			}
			if(quit) break;
			SDL_FillRect(mainScreen, &mainScreen->clip_rect, SDL_MapRGB(mainScreen->format, 0,0,0));
			for (std::vector<Sprite*>::iterator it = storage->begin(); it != storage->end(); it++){
				(*it)->tick();
				(*it)->draw();
			}
			for (std::vector<Component*>::iterator it = container->begin(); it != container->end(); it++){
				(*it)->draw();
			}
			SDL_Flip(mainScreen);
			++frame;
			timeSinceLastFrame->start();
			int ticks = fpsClock->get_ticks();
			if (ticks < (1000 / fpsLimit)){
				frame = 0;
				SDL_Delay((1000 / fpsLimit) - ticks);
			}
		}
	}

	void GameEngine::doQuit(){
		quit = true;
		Window::kill();
	}
}