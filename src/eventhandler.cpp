#include "eventhandler.h"
#include "keyevent.h"
#include "mouseevent.h"
namespace engine{
	std::map<SDLKey, EventListener*> EventHandler::keyActions = std::map<SDLKey, EventListener*>();
	std::map<int, EventListener*> EventHandler::mouseActions = std::map<int, EventListener*>();
	std::vector<EventListener*> EventHandler::globalActions = std::vector<EventListener*>();
	
	void EventHandler::addAction(SDLKey key, EventListener* action){
		keyActions[key] = action;
	}
	
	void EventHandler::addAction(int key, EventListener* action){
		mouseActions[key] = action;
	}
	
	void EventHandler::addAction(EventListener* action){
		globalActions.push_back(action);
	}

	void EventHandler::removeAction(SDLKey key){
		if(keyActions.find(key) == keyActions.end())
			 throw bad_arg("Could not find keyboard action");
		keyActions.erase(key);
	}
	
	void EventHandler::removeAction(int key){
		if(mouseActions.find(key) == mouseActions.end())
			 throw bad_arg("Could not find mouse action");
		mouseActions.erase(key);
	}
	
	void EventHandler::removeAction(EventListener* action){
		std::vector<EventListener*>::iterator actions = globalActions.begin();
		while(*actions != action)
			if(actions == globalActions.end()) 
				throw bad_arg("Could not find global action");
		globalActions.erase(actions);
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
	
	void EventHandler::perform(const SDLKey key, const Event* event){
		(*getAction(key))(event);
	}
		
	void EventHandler::perform(const int key, const Event* event){
		(*getAction(key))(event);
	}
	void EventHandler::perform(const Event* event){
		std::vector<EventListener*>::iterator actions = globalActions.begin();
		while(actions != globalActions.end())
			(**(actions++))(event);
	}
}