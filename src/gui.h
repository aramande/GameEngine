#ifndef GUI_H
#define GUI_H

#include "component.h"
#include <map>
#include <string>

namespace engine{
	class Gui
	{
	private:
		std::map<std::string, Component*> comps;
		static int index;
		std::string toStr(int number);
	public:
		Gui();
		virtual ~Gui();
		
		/**
		 * Adds a component to the gui with a randomly generated name.
		 *
		 * @param component The component to be added
		 *
		 * @see Component::getName()
		 */
		void addComp(Component* component);

		/**
		 * Adds a component to the game with an easy to access name.
		 * 
		 * @param name The name given to the component, has to be unique.
		 * @param component The component to be added
		 *
		 * @throws badarg If name already exists.
		 *
		 * @see Component::getName()
		 * 
		 */
		void setComp(std::string name, Component* component);

		/**
		 * Removes a component by name from the gui, does not delete the pointer.
		 *
		 * @param name The name of the component to be removed
		 */
		void removeComp(std::string name);

		/**
		 * Retrieve a component by name from the gui.
		 *
		 * @param name The name of the component to be removed
		 */
		Component* getComp(std::string name);
	};
}
#endif

