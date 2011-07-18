#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <string>
#include "image.h"
#include "event.h"
#include "component.h"

namespace engine {
	//typedef int Event; // temporary
	//typedef int Image;

	typedef void (*FPoint)(Event); 
	class Button : public Component {
		std::string text;
		std::vector<FPoint> codes;
	protected:
	public:
		Button(int x, int y, int w, int h);
		Button(int x, int y, Image buttonImg);

		/**
		 * Set what should happen when the button is pressed down.
		 * Will callback `code` whenever the button receives a 
		 * pressed mouse event within it's coordinates
		 *
		 * @param code A function that takes a single Event argument.
		 */
		void buttonDown(FPoint code);

		/**
		 * Set what should happen when the button is pressed down.
		 * Will callback `code` whenever the button receives a released mouse event.
		 *
		 * @param code A function that takes a single Event argument.
		 */
		void buttonUp(FPoint code);
		
	};
}

#endif