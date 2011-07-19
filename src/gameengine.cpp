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
		screen = main;
		storage = new std::vector<Sprite*>();
		fpsLimit = 10;
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
					EventHandler::performAction(curEvent.key.keysym.sym, new KeyEvent(curEvent.key.keysym.sym, 
						curEvent.key.keysym.mod, true, timeSinceLastFrame->get_ticks()));
					break;
				case SDL_MOUSEBUTTONDOWN:
					EventHandler::performAction(curEvent.button.button, new MouseEvent(curEvent.button.x, curEvent.button.y, 
						curEvent.button.button, true, false, timeSinceLastFrame->get_ticks()));
					break;
				}
			}
			SDL_FillRect(Window::init()->screen, &Window::init()->screen->clip_rect, SDL_MapRGB(Window::init()->screen->format, 0,0,0));
			for (std::vector<Sprite*>::iterator it = storage->begin(); it != storage->end(); it++){
				(*it)->tick();
				(*it)->draw();
			}
			SDL_Flip(Window::init()->screen);
			++frame;
			timeSinceLastFrame->start();
			if (fpsClock->get_ticks() < (1000 / fpsLimit)){
				Logger::init()->print(Logger::toStr(fpsClock->get_ticks()) + " has an avg " + Logger::toStr(frame/(fpsClock->get_ticks()/1000.0)));
				frame = 0;
				SDL_Delay((1000 / fpsLimit) - fpsClock->get_ticks());
			}
		}
	}

	void GameEngine::doQuit(){
		quit = true;
	}
}