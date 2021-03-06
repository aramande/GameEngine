#include <iostream>
#include "label.h"
#include "keyevent.h"
#include "eventhandler.h"
#include "eventlistener.h"

namespace engine{
	Label::Label(int x, int y, std::string str) : x(x), y(y), str(str), Component(x, y, 16*str.length(), 20){
		SDL_Color temp = {255,255,255};
		color = temp;
		font = ResourceHandler::init()->getFont("defaultfont");
		text = NULL;
		render();
	}

	Label::~Label(){
		if(text != NULL)
			SDL_FreeSurface(text);
		text = NULL;
		ResourceHandler::init()->release("defaultfont");
	}

	void Label::render(){
		if(text != NULL)
			SDL_FreeSurface(text);
		if(str.length() > 0)
			text = TTF_RenderText_Solid(font->getTTF(), str.c_str(),  color);
		else
			text = NULL;
	}

	void Label::setFont(Font* font){
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
		SDL_BlitSurface(text, NULL, mainScreen, rect);
	}
}
