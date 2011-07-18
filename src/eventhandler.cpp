#include "eventhandler.h"
#include "keyevent.h"
#include "mouseevent.h"
namespace engine{
	std::map<SDLKey, EventHandler::Func> EventHandler::keyActions = std::map<SDLKey, Func>();
	std::map<int, EventHandler::Func> EventHandler::mouseActions = std::map<int, Func>();
	void EventHandler::addAction(SDLKey key, Func action){
		keyActions.insert(std::pair<SDLKey, Func>(key, action));
	}
	
	void EventHandler::addAction(int key, Func action){
		mouseActions.insert(std::pair<int, Func>(key, action));
	}

	EventHandler::Func EventHandler::getAction(SDLKey key){
		if(keyActions.count(key) == 0){
			return *dummy;
		}
		return keyActions[key];
	}

	EventHandler::Func EventHandler::getAction(int key){
		if(mouseActions.count(key) == 0){
			return *dummy;
		}
		return mouseActions[key];
	}
	
	void EventHandler::performAction(SDLKey key, Event* event){
		(*getAction(key))(event);
	}
		
	void EventHandler::performAction(int key, Event* event){
		(*getAction(key))(event);
	}
}