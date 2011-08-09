#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "resource.h"
#include "rectangle.h"
#include "component.h"

namespace engine{
	class Input : public Component{
		int x, y;
		unsigned int length;
		SDL_Surface* text;
		std::string str;
	public:
		Input(int x, int y, int length = 16);
		~Input();
		void parseInput(const Event* event);
		void draw() const;
	};
}

#endif