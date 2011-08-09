#include <iostream>
#include "input.h"
#include "keyevent.h"
#include "eventhandler.h"
#include "eventlistener.h"

namespace engine{
	Input::Input(int x, int y, int len) : x(x), y(y), length(len-1), text(NULL), str(""), Component(x, y, 12*length, 16){
		SDL_EnableUNICODE(SDL_ENABLE); 
		parser = new ClassListener<Input>(this, &Input::parseInput);
		EventHandler::addAction(parser);
		font = Resource::loadFont("FreeUniversal-Regular.ttf", 14);
		SDL_Color temp = {255, 255, 255};
		color = temp;
	}

	Input::~Input(){
		SDL_FreeSurface(text);
		SDL_EnableUNICODE(SDL_DISABLE);
		EventHandler::removeAction(parser);
		delete parser;
		Resource::unloadFont("FreeUniversal-Regular.ttf", 14);
	}

	void Input::render(){
		if(text != NULL)
			SDL_FreeSurface(text);
		if(str.length() > 0)
			text = TTF_RenderText_Solid(font, str.c_str(),  color);
		else
			text = NULL;
	}

	void Input::setFont(TTF_Font* font){
		if(font == NULL) throw bad_arg("Font cannot be null");
		this->font = font;
		render();
	}

	void Input::setColor(const SDL_Color color){
		this->color = color;
		render();
	}

	std::string Input::getText() const{
		return str;
	}

	void Input::parseInput(const Event* event){
		const KeyEvent* keyevent = dynamic_cast<const KeyEvent*>(event);
		if(keyevent == NULL)
			return;

		std::string temp = str;
		if(keyevent->isPressed()){
			if(str.length() <= length){
				if(keyevent->getUnicode() == (Uint16)' ')
					str += " ";
			
				else if((keyevent->getUnicode() >= (Uint16)'0') && (keyevent->getUnicode() <= (Uint16)'9'))
					str += (char)keyevent->getUnicode();

				else if((keyevent->getUnicode() >= (Uint16)'a') && (keyevent->getUnicode() <= (Uint16)'z'))
					str += (char)keyevent->getUnicode();
			
				else if((keyevent->getUnicode() >= (Uint16)'A') && (keyevent->getUnicode() <= (Uint16)'Z'))
					str += (char)keyevent->getUnicode();
			}
			if((keyevent->getKey() == SDLK_BACKSPACE) && (str.length() != 0))
				str.erase( str.length() - 1 ); 
		}
		if(str != temp){ 
			render();
		}
	}

	void Input::draw() const{
		SDL_Rect target = rect->getSDL_Rect();
		SDL_BlitSurface(text, NULL, mainScreen, &target);
	}
}