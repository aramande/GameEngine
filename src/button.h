#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <string>
#include "image.h"
#include "event.h"
#include "badarg.h"
#include "window.h"
#include "resource.h"
#include "rectangle.h"
#include "component.h"
#include "mouseevent.h"
#include "eventlistener.h"
#include "fileexception.h"

namespace engine {
	class Button : public Component {
		std::string text;
		EventListener* action;
		Rectangle* rect;
		Rectangle* textRect;
		Image* image;
		SDL_Surface* textImg;

		void dummy(const Event* event){}
	protected:
	public:
		Button(int x, int y, Image* buttonImg, std::string text, EventListener* action = NULL);
		~Button();

		/**
		 * Set what should happen when the button is pressed down.
		 * Will callback `code` whenever the button receives a 
		 * pressed mouse event within it's coordinates
		 *
		 * @param code A function that takes a single Event argument.
		 */
		void perform(Event* event);
		void setAction(EventListener* f);
		void setText(std::string t, TTF_Font* font);
		std::string getText() const;
		const Rectangle* Button::getRectangle() const;
		void draw() const;
	};
}

#endif