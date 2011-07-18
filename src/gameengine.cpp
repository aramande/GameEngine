#include <iostream>
#include "gameengine.h"
#include "keyevent.h"
#include "mouseevent.h"
#include "eventhandler.h"
#include "badarg.h"
#include "event.h"
#include "sdl.h"

void shutdown(engine::Event* event){
	/*engine::KeyEvent* test = dynamic_cast<engine::KeyEvent*>(event);
	if(test != NULL){
		std::cout << test->getKey() << std::endl;
	}
	else{
		engine::MouseEvent* test2 = dynamic_cast<engine::MouseEvent*>(event);
		if(test2 != NULL){
			std::cout << test2->getX() << " " << test2->getY() << " Done" << std::endl;
		}
		else{
			std::cout << "Nothing registered" << std::endl;
		}
	}*/
	SDL_Quit();
	engine::GameEngine::doQuit();
}

namespace engine{
	bool GameEngine::quit = false;
	GameEngine* GameEngine::instance = NULL;

	GameEngine::GameEngine(Window* main){
		if(main == NULL)
			throw bad_arg("Main window cannot be null");
		screen = main;
		fpsClock = new Timer();
	}

	GameEngine* GameEngine::init(Window* main){
		if(instance == NULL)
			instance = new GameEngine(main);
		return instance;
	}

	void GameEngine::run(){
		Timer* timeSinceLastFrame = new Timer();
		fpsClock->start();
		SDL_Event curEvent;
		quit = false;
		EventHandler::addAction(SDLK_ESCAPE, &shutdown);
		EventHandler::addAction(SDL_BUTTON_LEFT, &shutdown);
		while(!quit) {
			timeSinceLastFrame->start();
			while(SDL_PollEvent(&curEvent)) {
				if (curEvent.type == SDL_QUIT)
					quit = true;
				switch (curEvent.type){
				case SDL_KEYDOWN:
					EventHandler::performAction(curEvent.key.keysym.sym, new KeyEvent(curEvent.key.keysym.sym, 
						curEvent.key.keysym.mod, true, timeSinceLastFrame->get_ticks()));
					break;
				case SDL_MOUSEBUTTONDOWN:
					EventHandler::performAction(curEvent.button.button, new MouseEvent(curEvent.button.x, curEvent.button.y, curEvent.button.button
						, true, false, timeSinceLastFrame->get_ticks()));
					break;
				}
			}
			if (fpsClock->get_ticks() < 1000 / fpsLimit)
				SDL_Delay((1000/fpsLimit) - fpsClock->get_ticks());
		}
	}

	void GameEngine::doQuit(){
		quit = true;
	}
}