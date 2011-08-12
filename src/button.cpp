#include "button.h"
#include "eventhandler.h"

namespace engine{
	Button::Button(int x, int y, Image* img, std::string text, EventListener* action) : Component(x, y, img->getWidth(), img->getHeight()){
		if(img == NULL) throw bad_arg("Image cannot be null");
		//this->action = action;
		this->image = img;
		this->rect = new Rectangle(x, y, image->getWidth(), image->getHeight());	
		EventHandler::addAction(SDL_BUTTON_LEFT, rect, action);
		setText(text, Resource::loadFont("FreeUniversal-Bold.ttf", 14));
	}

	Button::~Button(){
		EventHandler::removeAction(SDL_BUTTON_LEFT, rect);
		delete textRect;
		textRect = NULL;
		delete rect;
		rect = NULL;
		delete image;
		image = NULL;
		SDL_FreeSurface(textImg);
		textImg = NULL;
	}

	/**
	 * @deprecated since commit 39026b30e7
	 */
	void Button::perform(Event* event){
		MouseEvent* mev = dynamic_cast<MouseEvent*>(event);
		if (mev == NULL)
			return;
		if (action == NULL)
			return;

		if (rect->contains(mev->getX(), mev->getY()))
			(*action)(mev);
	}

	void Button::setAction(EventListener* action){
		EventHandler::removeAction(SDL_BUTTON_LEFT, rect);
		EventHandler::addAction(SDL_BUTTON_LEFT, rect, action);
	}
	void Button::setText(std::string t, TTF_Font* font){
		if(font == NULL){
			throw bad_arg("Font cannot be null");
		}
		text = t;
		SDL_Color black = {0,0,0};
		SDL_Surface *tmp = TTF_RenderText_Solid(font,text.c_str(),black);
		if(tmp != NULL){ 
			textImg = SDL_DisplayFormat(tmp);
			SDL_FreeSurface(tmp);
		}
		else{
			throw file_exception("Could not render font");
		}
		textRect = rect->centeredRect(textImg->w, textImg->h);
	}
	std::string Button::getText() const{
		return text;
	}
	const Rectangle* Button::getRectangle() const{
		return rect;
	}

	void Button::draw() const{
		SDL_Rect source = {0,0,rect->w,rect->h};
		if (true)
			SDL_BlitSurface(image->getSurface(), &source, mainScreen, rect);
		else
			SDL_BlitSurface(NULL, &source, mainScreen, rect);
		SDL_BlitSurface(textImg, NULL, mainScreen, textRect);
	}
}
