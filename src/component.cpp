#include "component.h"

using namespace std;
namespace engine{
	Component::Component(int x, int y, int w, int h){
		rect = new Rectangle(x, y, w, h);

	}
	
	Component::~Component(){
		delete rect;
	}

	string Component::getName(){
		return name;
	}

	void Component::setName(string name){
		this->name = name;
	}

	void Component::update(){

	}
	
	void Component::draw() const{
		
	}

}