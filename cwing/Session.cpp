#include "Session.h"
#include "Globals.h"
#include "CwingError.h"

#define FPS 60

namespace cwing{

	Session::Session(){
		bgColor = SDL_MapRGB(sys.screen->format, 255,255,255);
	}


	Session::~Session(){
		for(unsigned int i=0; i < comps.size(); i++)
			delete comps[i];
	}

	void Session::add(Komponent* ny){
		for(unsigned int i=0; i < comps.size(); i++)
			if (ny->getRect().overlaps(comps[i]->getRect()))
				throw CwingError("Överlappar!");

		comps.push_back(ny);
	}
	void Session::run(){

		bool quit = false;
		int tickInterval = 1000 / FPS;
		Uint32 nextTick;

		while (!quit) {
			nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event eve;
			while (SDL_PollEvent(&eve)){
				switch(eve.type){
				case SDL_KEYDOWN:
					if (eve.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
					break;
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					forAll(&Komponent::mouseDown,eve);
					break;
				case SDL_MOUSEBUTTONUP:
					forAll(&Komponent::mouseUp, eve);
					break;
				} // switch
			} // while poll

			SDL_FillRect(sys.screen, NULL, bgColor);
			for(unsigned int i=0; i < comps.size(); i++)
				comps[i]->draw();
			SDL_Flip(sys.screen);

			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		} // while

	} // run

	void Session::forAll(void (Komponent::*mf)(int,int), const SDL_Event& e ){
		for(unsigned int i=0; i<comps.size(); i++)
			(comps[i]->*mf)(e.button.x, e.button.y);
	}
} //cwing