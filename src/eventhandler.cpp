#include "eventhandler.h"
#include "keyevent.h"
#include "mouseevent.h"
namespace engine{
	std::map<SDLKey, EventListener*> EventHandler::keyActions = std::map<SDLKey, EventListener*>();
	std::map<int, EventListener*> EventHandler::mouseActions = std::map<int, EventListener*>();
	
	void EventHandler::addAction(SDLKey key, EventListener* action){
		keyActions[key] = action;
	}
	
	void EventHandler::addAction(int key, EventListener* action){
		mouseActions[key] = action;
	}

	void EventHandler::removeAction(SDLKey key){
		keyActions.erase(key);
	}
	
	void EventHandler::removeAction(int key){
		mouseActions.erase(key);
	}

	EventListener* EventHandler::getAction(const SDLKey key){
		if(keyActions.find(key) == keyActions.end()){
			FunctionListener* dummyListener = new FunctionListener(&dummy);
			return dummyListener;
		}
		return keyActions[key];
	}

	EventListener* EventHandler::getAction(const int key){
		if(mouseActions.find(key) == mouseActions.end()){
			FunctionListener* dummyListener = new FunctionListener(&dummy);
			return dummyListener;
		}
		return mouseActions[key];
	}
	
	void EventHandler::perform(const SDLKey key, Event* event){
		(*getAction(key))(event);
	}
		
	void EventHandler::perform(const int key, Event* event){
		(*getAction(key))(event);
	}
}