#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <map>
#include "sdl.h"
#include "event.h"
namespace engine{
	class EventHandler {
		typedef void(*Func)(Event*);
		static std::map<SDLKey, Func> keyActions;
		static std::map<int, Func> mouseActions;
		static void dummy(Event* event){}
	 public:
		static void addAction(SDLKey key, Func action);
		static void addAction(int key, Func action);
		static Func getAction(SDLKey key);
		static Func getAction(int key);
		static void perform(SDLKey key, Event* event);
		static void perform(int key, Event* event);
	};
}

#endif
