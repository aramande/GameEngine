#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <map>
#include <vector>
#include "sdl.h"
#include "event.h"
#include "eventlistener.h"
namespace engine{
	class EventHandler {
		static std::map<SDLKey, EventListener*> keyActions;
		static std::map<int, std::map<const Rectangle*, EventListener*> > mouseActions;
		static std::vector<EventListener*> globalActions;
		
		static void dummy(const Event* event){}
	 public:
		/**
		 * Register a keyboard event callback function.
		 */
		static void addAction(const SDLKey key, EventListener* action);
		
		/**
		 * Register a mouse event callback function.
		 */
		static void addAction(const int key, const Rectangle* area, EventListener* action);

		/**
		 * Register a global event callback function.
		 * Warning, the callback function will be called at every event.
		 */
		static void addAction(EventListener* action);
		
		/**
		 * Remove a keyboard event callback function.
		 */
		static void removeAction(SDLKey key);
		
		/**
		 * Remove a mouse event callback function.
		 */
		static void removeAction(int key, const Rectangle* area);
		
		/**
		 * Remove a global event callback function.
		 */
		static void removeAction(EventListener* action);
		
		static EventListener* getAction(const SDLKey key);
		static EventListener* getAction(const int key, const Rectangle* area);
		static EventListener* getAction(const int key, int x, int y);
		
		/**
		 * Runs a single keyboard event callback functions.
		 */
		static void perform(const SDLKey key, const Event* event);
		
		/**
		 * Runs a single mouse event callback functions.
		 */
		static void perform(const int key, const Event* event);
		
		/**
		 * Runs all global event callback functions.
		 */
		static void perform(const Event* event);
	};
}

#endif
