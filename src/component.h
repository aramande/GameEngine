#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace engine {
	class Component {
		int x, y, w, h;
		std::string name;

		Component(const Component &other){}
		const Component &operator=(const Component &other){}
		
		/**
		 * May only be used by Gui.
		 */
		void setName(std::string name);
	protected:
		Component(int x, int y, int w, int h);

	public:
		virtual ~Component();

		std::string getName();

		/**
		 * Update the component, component logic goes here.
		 */
		virtual void update();

		/**
		 * Draw the component onto the screen.
		 */
		virtual void draw() const;
		
		friend class Gui;
	};
}
#endif