#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <map>
#include "sdl.h"
#include "event.h"
#include "eventlistener.h"
namespace engine{
	class EventHandler {
		static std::map<SDLKey, EventListener*> keyActions;
		static std::map<int, EventListener*> mouseActions;
		
		static void dummy(Event* event){}
	 public:
		static void addAction(SDLKey key, EventListener* action);
		static void addAction(int key, EventListener* action);
		static EventListener* getAction(SDLKey key);
		static EventListener* getAction(int key);
		static void perform(SDLKey key, Event* event);
		static void perform(int key, Event* event);
	};
}

#endif
