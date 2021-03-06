#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "resource.h"
#include "component.h"
#include "eventlistener.h"

namespace engine{
	class Input : public Component{
		int x, y;
		unsigned int length;
		TTF_Font* font;
		SDL_Color color;
		SDL_Surface* text;
		std::string str;
		ClassListener<Input>* parser;
		void render();
	public:
		Input(int x, int y, int length = 16);
		~Input();
		void setFont(TTF_Font* font);
		void setColor(const SDL_Color color);
		std::string getText() const;
		void parseInput(const Event* event);
		void draw() const;
	};
}

#endif