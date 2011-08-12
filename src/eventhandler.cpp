#include <string>
#include "eventhandler.h"
#include "keyevent.h"
#include "mouseevent.h"
namespace engine{
	std::map<SDLKey, EventListener*> EventHandler::keyActions = std::map<SDLKey, EventListener*>();
	std::map<int, std::map<const Rectangle*, EventListener*> > EventHandler::mouseActions = 
		std::map<int, std::map<const Rectangle*, EventListener*> >();
	std::vector<EventListener*> EventHandler::globalActions = std::vector<EventListener*>();
	
	void EventHandler::addAction(SDLKey key, EventListener* action){
		keyActions[key] = action;
	}
	
	void EventHandler::addAction(const int key, const Rectangle* area, EventListener* action){
		if(!mouseActions[key].count(area))
			mouseActions[key] = std::map<const Rectangle*, EventListener*>();
		mouseActions[key][area] = action;
		Logger::init()->print("Adding a mouse event listener: " + toStr(mouseActions[key][area]) + " to " + toStr(area));
	}
	
	void EventHandler::addAction(EventListener* action){
		globalActions.push_back(action);
	}

	void EventHandler::removeAction(SDLKey key){
		if(keyActions.find(key) == keyActions.end())
			 throw bad_arg("Could not find keyboard action");
		delete keyActions[key];
		keyActions.erase(key);
	}
	
	void EventHandler::removeAction(int key, const Rectangle* area){
		if(mouseActions.find(key) == mouseActions.end())
			 throw bad_arg("Could not find mouse action");
		if(mouseActions[key].find(area) == mouseActions[key].end())
			 throw bad_arg("Could not find mouse action for the area");
		delete mouseActions[key][area];
		mouseActions[key].erase(area);
	}
	
	void EventHandler::removeAction(EventListener* action){
		std::vector<EventListener*>::iterator actions = globalActions.begin();
		while(*actions != action)
			if(actions == globalActions.end()) 
				throw bad_arg("Could not find global action");
		globalActions.erase(actions);
	}

	EventListener* EventHandler::getAction(const SDLKey key){
		if(keyActions.find(key) == keyActions.end())
			return NULL;
		
		return keyActions[key];
	}

	EventListener* EventHandler::getAction(const int key, const Rectangle* area){
		if(mouseActions.find(key) == mouseActions.end())
			return NULL;
		if(mouseActions[key].find(area) == mouseActions[key].end())
			return NULL;

		return mouseActions[key][area];
	}

	EventListener* EventHandler::getAction(const int key, int x, int y){
		if(mouseActions.find(key) == mouseActions.end())
			return NULL;
		
		std::map<const Rectangle*, EventListener*>::iterator it;
		std::map<const Rectangle*, EventListener*> current = mouseActions[key];

		for(it=current.begin(); it != current.end(); it++){
			const Rectangle* component = it->first;
			Logger::init()->print("Rect pointer: " + toStr(component));
			if(component->contains(x, y)){
				Logger::init()->print("Found action at " + toStr(x) + ", " + toStr(y));
				return it->second;
			}
		}
		return NULL;
	}
	
	void EventHandler::perform(const SDLKey key, const Event* event){
		if(dynamic_cast<const KeyEvent*>(event)){
			EventListener* action = getAction(key);
			if(action)
				(*action)(event);
		}
	}
		
	void EventHandler::perform(const int key, const Event* event){
		if(const MouseEvent* mouseEvent = dynamic_cast<const MouseEvent*>(event)){
			EventListener* action = getAction(key, mouseEvent->getX(), mouseEvent->getY());
			if(action)
				(*action)(event);
		}
	}
	void EventHandler::perform(const Event* event){
		std::vector<EventListener*>::iterator actions = globalActions.begin();
		while(actions != globalActions.end())
			(**(actions++))(event);
	}
}
