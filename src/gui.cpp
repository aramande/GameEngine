#include "gui.h"
#include "badarg.h"

#include <sstream>

using namespace std;
namespace engine{
	
	int Gui::index = 0;

	Gui::Gui(){

	}

	Gui::~Gui(){

	}

	void Gui::addComp(Component* component){
		if(component->getName() != "")
			return;
		string name = "comp" + toStr(index);
		setComp(name, component);
		++index;
	}

	void Gui::setComp(string name, Component* component){
		if(comps.find(name) != comps.end() && comps[name] == component)
			return;
		else if(comps.find(name) != comps.end())
			throw bad_arg("Gui: Error, key already exists");
		if(component->getName() != "") // Erase the old entry if it exists.
			delComp(component->getName());

		component->setName(name);
		comps.insert(pair<string, Component*>(name, component));
	}

	void Gui::delComp(string name){
		if(comps.find(name) == comps.end())
			throw bad_arg("Gui: Error, no such key");

		comps.erase(name);
	}

	Component* Gui::getComp(std::string name){
		if(comps.find(name) == comps.end()){
			throw bad_arg("Gui: Error, no such key");
		}
		return comps[name];
	}
	
	string Gui::toStr(int number){
		std::string s;
		std::stringstream out;
		out << number;
		s = out.str();
		return s;
	}
}