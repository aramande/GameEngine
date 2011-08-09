#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "resource.h"
#include "component.h"

namespace engine{
	class Label : public Component{
		int x, y;
		TTF_Font* font;
		SDL_Color color;
		SDL_Surface* text;
		std::string str;
		void render();
	public:
		Label(int x, int y, std::string str);
		~Label();
		void setFont(TTF_Font* font);
		void setColor(const SDL_Color color);
		void setText(std::string str);
		std::string getText() const;
		void draw() const;
	};
}

#endif