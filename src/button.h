#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <string>
#include "image.h"
#include "event.h"
#include "rectangle.h"
#include "component.h"
#include "fileexception.h"
#include "resource.h"
#include "window.h"
#include "mouseevent.h"

namespace engine {
	class Button : public Component {
		std::string text;
		Func action;
		Rectangle* rect;
		Rectangle* textRect;
		Image* image;
		SDL_Surface* textImg;
	protected:
	public:
		Button(int x, int y, Image* buttonImg, Func action, std::string text);
		~Button();

		/**
		 * Set what should happen when the button is pressed down.
		 * Will callback `code` whenever the button receives a 
		 * pressed mouse event within it's coordinates
		 *
		 * @param code A function that takes a single Event argument.
		 */
		void perform(Event* event);
		void setAction(Func f);
		void setText(std::string t, TTF_Font* font);
		std::string getText() const;
		const Rectangle* Button::getRectangle() const;
		void draw() const;
	};
}

#endif