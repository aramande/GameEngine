#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <vector>
#include "sprite.h"
#include "timer.h"
#include "window.h"
#include "gui.h"

namespace engine {
	class GameEngine {
		std::vector<std::vector<Sprite*> >* storage;
		Gui* hud; 
		Window* screen;
		Timer* fpsClock;
		int fpsLimit;
		static bool quit;
		static GameEngine* instance;
		
		/** 
		 * Runs through sprites, checking every vector that contains more than one value if they collide.
		 * Incase of collision, onCollision is called on both sprites.
		 */
		void collide();
		GameEngine(Window* screen); // init the game engine here
	public:
		static GameEngine* init(Window* screen);
		
		void addSprite(Sprite* s);
		void delSprite(Sprite* s);

		void setFPS(int fps);
		
		/**
		 * Calls all update functions and draws sprites and gui on the screen.
		 */
		void run();
		static void doQuit();
	};
}

#endif