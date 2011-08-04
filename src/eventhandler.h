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
		static void addAction(const SDLKey key, EventListener* action);
		static void addAction(const int key, EventListener* action);
		static EventListener* getAction(const SDLKey key);
		static EventListener* getAction(const int key);
		static void perform(const SDLKey key, Event* event);
		static void perform(const int key, Event* event);
	};
}

#endif
