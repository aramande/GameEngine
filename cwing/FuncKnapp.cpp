#include "FuncKnapp.h"



cwing::FuncKnapp::FuncKnapp(int x, int y, std::string t, 
		Func f, void *some):
	Knapp(x,y,t), fpek(f), something(some){
}

cwing::FuncKnapp* cwing::FuncKnapp::getInstance(int x, int y, 
		std::string t, Func f, void *some){
	return new cwing::FuncKnapp(x,y,t,f,some);
}

void cwing::FuncKnapp::perform(){
	fpek(getText(), something);
}
