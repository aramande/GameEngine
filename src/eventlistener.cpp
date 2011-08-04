#include "eventlistener.h"

namespace engine{
	FunctionListener::FunctionListener(const Func code){
		setFunction(code);
	}
	void FunctionListener::operator()(Event* event){
		(*action)(event);
	}

	void FunctionListener::setFunction(const Func code){
		if(code == NULL)
			throw bad_arg("Function pointer cannot be null");
		action = code;
	}
}