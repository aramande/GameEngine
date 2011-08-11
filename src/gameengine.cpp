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
		action = &dummy;
		storage = new std::vector<Sprite*>();
		container = new std::vector<Component*>();
		fpsLimit = 30;
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

	void GameEngine::removeAllSprites() {
		for (unsigned int i = 0; i < storage->size(); i++) {
			delete storage->at(i);
			storage->erase(storage->begin() + i);
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
				Logger::init()->print("Removing component");
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
		std::stack<Sprite*> deathrow = std::stack<Sprite*>();
		
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
						break;
					case SDL_MOUSEBUTTONDOWN:
						click = curEvent.button;
						mouseEvent = new MouseEvent(click.x, click.y, 
							click.button, true, false, timeSinceLastFrame->get_ticks());
						EventHandler::perform(click.button, mouseEvent);
						EventHandler::perform(mouseEvent);
						for (std::vector<Component*>::iterator it = container->begin(); it != container->end(); it++){
							(*it)->perform(mouseEvent);
						}
						break;
				}
			}
			if(quit) break;
			
			SDL_FillRect(mainScreen, &mainScreen->clip_rect, 
				SDL_MapRGB(mainScreen->format, 0,0,0));
			
			for (std::vector<Sprite*>::iterator sprite = storage->begin(); 
				sprite != storage->end();sprite++){
				if ((*sprite)->isDead())
					continue;
				(*sprite)->tick();
				for (std::vector<Sprite*>::iterator otherSprite = storage->begin(); 
					otherSprite != storage->end();otherSprite++) {
					if ((*sprite)->collidesWith(NULL)){
						(*sprite)->collide(NULL);
					}
					if ((*sprite)->collidesWith(*otherSprite) && !(*sprite)->isDead() && !(*otherSprite)->isDead()) {
						(*sprite)->collide((*otherSprite));
   						(*otherSprite)->collide((*sprite));
						
						std::string msg = "Collision detected at ";
						msg += toStr((*sprite)->getX()) + " " + toStr((*sprite)->getY());
						msg += " (at frame " + toStr(globalFrame) + ")";
						Logger::init()->print(msg);
						
						if ((*sprite)->isDead()) {
							deathrow.push(*(sprite));
						}
						if ((*otherSprite)->isDead()) {
							deathrow.push(*(otherSprite));
						}
					}
				}
				(*sprite)->draw();
			}
			
			Sprite* deadSprite;
			while(!deathrow.empty()){
				deadSprite = deathrow.top();
				delSprite(deadSprite);
				deathrow.pop();
			}
			
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
		Logger::init()->print("Good bye");
		quit = true;
		Window::kill();
	}
}
