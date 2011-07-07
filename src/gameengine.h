#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <vector>
#include "sprite.h"
#include "window.h"
#include "gui.h"

namespace engine {
	class GameEngine {
		std::map<int, std::vector<Sprite*> > *storage;
		Gui* hud; 
		Window* screen;
		static GameEngine *instance;
		
		/** 
		 * Runs through sprites, checking every vector that contains more than one value if they collide.
		 * Incase of collision, onCollision is called on both sprites.
		 */
		void collide();
		GameEngine(Window* screen); // init the game engine here
	public:
		static GameEngine* init(Window* screen);
		/**
		 * Add a sprite into the fridge at the right hash value. If another sprite has already created a vector, put it at the end of it.
		 */
		void addSprite(Sprite* s);
		
		/**
		 * Runs the main loop and calls all necessary functions to draw sprites on the screen.
		 */
		void run() const;
	};
}

#endif