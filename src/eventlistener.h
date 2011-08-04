#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "event.h"
#include "sprite.h"
#include "badarg.h"
#include "component.h"
namespace engine{
	class EventListener{
	public:
		virtual ~EventListener(){}
		virtual void operator()(const Event*) = 0;
	};

	template<class C>
	class ClassListener : public EventListener {
		typedef void(C::*CFunc)(const Event*);
		C* object;
		CFunc action;
	public:
		ClassListener(C* const object, const CFunc code){
			setFunction(object, code);
		}
		~ClassListener(){
			// Both object and action are dangerous pointers so we're not deleting them
			object = NULL;
			action = NULL;
		}

		void operator()(const Event* event){
			(object->*action)(event);
		}
		void setFunction(C* const object, const CFunc code){
			if(object == NULL)
				throw bad_arg("Class object cannot be null");
			if(code == NULL)
				throw bad_arg("Function pointer cannot be null");
			this->object = object;
			this->action = code;
		}
	};

	class FunctionListener : public EventListener {
		typedef void(*Func)(const Event*);
		Func action;
	public:
		FunctionListener(const Func code);
		void setFunction(const Func code);
		void operator()(const Event*);
	};
}
#endif