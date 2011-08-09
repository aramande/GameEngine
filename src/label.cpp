#include <iostream>
#include "label.h"
#include "keyevent.h"
#include "eventhandler.h"
#include "eventlistener.h"

namespace engine{
	Label::Label(int x, int y, std::string str) : x(x), y(y), str(str), Component(x, y, 16*str.length(), 20){
		SDL_Color temp = {255,255,255};
		color = temp;
		font = Resource::loadFont("FreeUniversal-Regular.ttf", 14);
		text = NULL;
		render();
	}

	Label::~Label(){
		SDL_FreeSurface(text);
	}

	void Label::render(){
		if(text != NULL)
			SDL_FreeSurface(text);
		if(str.length() > 0)
			text = TTF_RenderText_Solid(font, str.c_str(),  color);
		else
			text = NULL;
	}

	void Label::setFont(TTF_Font* font){
		if(font == NULL) throw bad_arg("Font cannot be null");
		this->font = font;
		render();
	}

	void Label::setColor(const SDL_Color color){
		this->color = color;
		render();
	}

	void Label::setText(std::string str){
		this->str = str;
		rect->w = 12*str.length();
		render();
	}

	std::string Label::getText() const{
		return str;
	}

	void Label::draw() const{
		SDL_Rect target = rect->getSDL_Rect();
		SDL_BlitSurface(text, NULL, mainScreen, &target);
	}
}