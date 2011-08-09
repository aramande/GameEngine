#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "event.h"
#include "window.h"
#include "rectangle.h"

namespace engine {
	class Component {
		std::string name;

		Component(const Component &other){}
		const Component &operator=(const Component &other){}
		
		/**
		 * May only be used by Gui.
		 */
		void setName(std::string name);
	protected:
		typedef void (*Func)(Event*); 
		Component(int x, int y, int w, int h);
		Rectangle* rect;

	public:
		virtual ~Component();

		std::string getName();

		/**
		 * Update the component, component logic goes here.
		 */
		virtual void update();
		
		virtual void perform(Event* event){}

		/**
		 * Draw the component onto the mainScreen.
		 */
		virtual void draw() const;
		
		friend class Gui;
	};
}
#endif