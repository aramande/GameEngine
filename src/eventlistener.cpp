#include "eventlistener.h"

namespace engine{
	void FunctionListener::operator()(Event* event){
		(*action)(event);
	}
	void FunctionListener::setFunction(Func code){
		action = code;
	}
}