#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <stack>
#include <vector>
#include "badarg.h"
#include "button.h"
#include "component.h"
#include "event.h"
#include "eventhandler.h"
#include "fileexception.h"
#include "gui.h"
#include "image.h"
#include "input.h"
#include "keyevent.h"
#include "label.h"
#include "mouseevent.h"
#include "projectile.h"
#include "rectangle.h"
#include "resource.h"
#include "sdl.h"
#include "sdlerror.h"
#include "sprite.h"
#include "timer.h"
#include "window.h"

namespace engine {
	class GameEngine {
		typedef void (*Func)(int);
		std::vector<Sprite*>* storage;
		std::vector<Component*>* container;
		Func action;
		//Gui* hud; 
		Window* window;
		Timer* fpsClock;
		int fpsLimit;
		static bool quit;
		static GameEngine* instance;
		
		/** 
		 * Runs through sprites, checking every vector that contains more than one value if they collide.
		 * Incase of collision, onCollision is called on both sprites.
		 */
		void collide();
		static void dummy(int timeSinceLastFrame){}
		GameEngine(Window* mainScreen); // init the game engine here
	public:
		static GameEngine* init(Window* mainScreen);
		~GameEngine();
		
		void addSprite(Sprite* s);
		void delSprite(Sprite* s);
		void addComponent(Component* c);
		void delComponent(Component* c);
		void setAction(Func action);
		void perform(int timeSinceLastFrame);

		void setFPS(int fps);
		
		/**
		 * Calls all update functions and draws sprites and gui on the mainScreen.
		 */
		void run();
		static void doQuit();
	};
}

#endif