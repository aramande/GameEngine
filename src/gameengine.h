#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <vector>
#include "badarg.h"
#include "button.h"
#include "component.h"
#include "event.h"
#include "eventhandler.h"
#include "fileexception.h"
#include "gui.h"
#include "image.h"
#include "keyevent.h"
#include "mouseevent.h"
#include "rectangle.h"
#include "resource.h"
#include "sdl.h"
#include "sdlerror.h"
#include "sprite.h"
#include "timer.h"
#include "window.h"

namespace engine {
	class GameEngine {
		std::vector<Sprite*>* storage;
		std::vector<Component*>* container;
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
		~GameEngine();
		
		void addSprite(Sprite* s);
		void delSprite(Sprite* s);
		void addComponent(Component* c);
		void delComponent(Component* c);

		void setFPS(int fps);
		
		/**
		 * Calls all update functions and draws sprites and gui on the screen.
		 */
		void run();
		static void doQuit();
	};
}

#endif