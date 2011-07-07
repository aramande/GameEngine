#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <vector>
#include "sprite.h"
#include "window.h"
#include "gui.h"

namespace engine {
	class GameEngine {
		std::vector<std::vector<Sprite*> >* storage;
		Gui* hud; 
		Window* screen;
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
		
		/**
		 * Calls all update functions and draws sprites and gui on the screen.
		 */
		void run() const;
	};
}

#endif