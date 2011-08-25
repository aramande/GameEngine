#include <iostream>
#include <algorithm>
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
		logger->setToCommand(false);
		logger->setLogFile("debug.log");
		logger->print("Initializing gameengine");
		ResourceHandler::init()->loadResourceFile("enginedefault.res");
		window = main;
		action = &dummy;
		storage = new std::vector<Sprite*>();
		container = new std::vector<Component*>();
		fpsLimit = 30;
		fpsClock = new Timer();
	}

	GameEngine::~GameEngine(){
		storage->clear();
		container->clear();
		delete storage;
		delete fpsClock;
		delete container;
	}

	GameEngine* GameEngine::init(Window* main){
		if(instance == NULL)
			instance = new GameEngine(main);
		return instance;
	}

	bool deadSprite(Sprite* sprite){
		if(sprite->isDead()){
			delete sprite;
			return true;
		}
		return false;
	} 

	bool removeAll(Sprite* sprite){ 
		// No idea why this generates a segfault
		delete sprite; 
		return true;
   	}

	void GameEngine::setFPS(int fps){
		if(fps < 1)
			throw bad_arg("Negative FPS");
		fpsLimit = fps;
	}

	void GameEngine::addSprite(Sprite* sprite){
		if(sprite == NULL)
			throw bad_arg("Don't add null to the sprite list");
		logger->print("Adding sprite");
		storage->push_back(sprite);
	}

	void GameEngine::removeSprite(Sprite* s) {
		for (unsigned int i = 0; i < storage->size(); i++) {
			if (storage->at(i) == s) {
				logger->print("Removing sprite");
				delete storage->at(i);
				storage->erase(storage->begin() + i);
				return;
			}
		}
	}

	void GameEngine::removeAllSprites() {
		/*while (!storage->empty()) {
			delete storage->back();
		  	storage->pop_back();
		}*/
		storage->erase(remove_if(storage->begin(), storage->end(), removeAll), storage->end());
	}

	void GameEngine::addComponent(Component* c) {
		if(c == NULL)
			throw bad_arg("Don't add null to the component list");
		logger->print("Adding component");
		container->push_back(c);
	}

	void GameEngine::removeComponent(Component* c) {
		for (unsigned int i = 0; i < container->size(); i++) {
			if(container->at(i) == c) {
				logger->print("Removing component");
				delete container->at(i);
				container->erase(container->begin() + i);
			}
		}
	}

	void GameEngine::setAction(Func action){
		if(action == NULL)
			return;
		this->action = action;
	}

	void GameEngine::perform(int timeSinceLastFrame){
		(*action)(timeSinceLastFrame);
	}

	void GameEngine::run(){
		Timer* timeSinceLastFrame = new Timer();
		SDL_Event curEvent;
		quit = false;
		int frame = 0;
		int globalFrame = 0; //temp

		timeSinceLastFrame->start();
		KeyEvent* keyEvent;
		MouseEvent* mouseEvent;
		while(!quit) {
			fpsClock->start();
			perform(timeSinceLastFrame->get_ticks());
			while(SDL_PollEvent(&curEvent)) {
				if (curEvent.type == SDL_QUIT)
					quit = true;
				SDL_keysym keySymbol;
				SDL_MouseButtonEvent click;
				switch (curEvent.type){
					case SDL_KEYDOWN:
						keySymbol = curEvent.key.keysym;
						keyEvent = new KeyEvent(keySymbol.sym, 
												keySymbol.mod, keySymbol.unicode, true, timeSinceLastFrame->get_ticks());
						EventHandler::perform(keyEvent);
						EventHandler::perform(keySymbol.sym, keyEvent);
						delete keyEvent;
						break;
					case SDL_KEYUP:
						keySymbol = curEvent.key.keysym;
						keyEvent = new KeyEvent(keySymbol.sym, 
												keySymbol.mod, keySymbol.unicode, false, timeSinceLastFrame->get_ticks());
						EventHandler::perform(keyEvent);
						EventHandler::perform(keySymbol.sym, keyEvent);
						delete keyEvent;
						break;
					case SDL_MOUSEBUTTONDOWN:
						click = curEvent.button;
						mouseEvent = new MouseEvent(click.x, click.y, 
													click.button, true, false, timeSinceLastFrame->get_ticks());
						EventHandler::perform(click.button, mouseEvent);
						EventHandler::perform(mouseEvent);
						delete mouseEvent;
						break;
				}
			}
			if(quit) break;

			SDL_FillRect(mainScreen, &mainScreen->clip_rect, 
						 SDL_MapRGB(mainScreen->format, 0,0,0));

			for (std::vector<Sprite*>::iterator sprite = storage->begin(); 
				 sprite != storage->end(); ++sprite){
				if(!(*sprite)->isDead()){
					(*sprite)->tick();

					// Check wall collision
					if ((*sprite)->collidesWith(NULL)){
						(*sprite)->collide(NULL);
					}

					for (std::vector<Sprite*>::iterator otherSprite = storage->begin(); 
						 otherSprite != storage->end(); ++otherSprite) {
						if((*sprite) == (*otherSprite)){
							continue;
						}
						if(!(*sprite)->isDead() && !(*otherSprite)->isDead()){
							if ((*sprite)->collidesWith(*otherSprite)) {
								(*sprite)->collide((*otherSprite));
								(*otherSprite)->collide((*sprite));

								logger->printf("Collision detected at %d,%d (at frame %d)", 
									(*sprite)->getX(), (*sprite)->getY(), globalFrame);
							}
						}
					}
				}
				(*sprite)->draw();
			}
			//Remove all dead sprites
			storage->erase(std::remove_if(storage->begin(), storage->end(), deadSprite), storage->end());

			for (std::vector<Component*>::iterator component = container->begin(); 
				 component != container->end(); component++){
				(*component)->draw();
			}

			SDL_Flip(mainScreen);

			++frame;
			++globalFrame; //temp
			timeSinceLastFrame->start();
			int ticks = fpsClock->get_ticks();
			if (ticks < (1000 / fpsLimit)){
				frame = 0;
				SDL_Delay((1000 / fpsLimit) - ticks);
			}
		}
	}

	void GameEngine::doQuit(){
		ResourceHandler::init()->destroy();
		logger->print("Good bye");
		quit = true;
		Window::kill();
	}
}
