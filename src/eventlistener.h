#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "event.h"
#include "sprite.h"
#include "component.h"
namespace engine{
	class EventListener{
	public:
		virtual void operator()(Event*) = 0;
	};

	template<class C>
	class ClassListener : public EventListener {
		typedef void(C::*CFunc)(Event*);
		C* object;
		CFunc action;
	public:
		void operator()(Event* event){
			(object->*action)(event);
		}
		void setFunction(C* component,  CFunc code){
			object = component;
			action = code;
		}
	};

	class FunctionListener : public EventListener {
		typedef void(*Func)(Event*);
		Func action;
	public:
		void setFunction(Func code);
		void operator()(Event*);
	};
}
#endif