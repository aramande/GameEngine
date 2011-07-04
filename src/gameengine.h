#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <vector>
#include "sprite.h"
#include "gui.h"

namespace engine {
	class GameEngine {
		std::map<int, std::vector<Sprite*> > *fridge;
		Gui *hud; 
		
		/** 
		 * Runs through sprites, checking every vector that contains more than one value if they collide.
		 * Incase of collision, onCollision is called on both sprites.
		 */
		void collide();
		GameEngine(); // init the game engine here
	public:
		GameEngine *init();
		/**
		 * Add a sprite into the fridge at the right hash value. If another sprite has already created a vector, put it at the end of it.
		 */
		void addSprite(Sprite *s);
		
		/**
		 * Runs the main loop and calls all necessary functions to draw sprites on the screen.
		 */
		void run() const;
	};
}

#endif