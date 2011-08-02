#include "button.h"
namespace engine{
	Button::Button(int x, int y, Image* img, Func action) : Component(x, y, img->getWidth(), img->getHeight()){
		this->image = img;
		this->rect = new Rectangle(x, y, image->getWidth(), image->getHeight());	
		this->action = action;
		setText("asd", Resource::loadFont("tahomabd.ttf", 14));
	}

	void Button::perform(Event* event){
		MouseEvent* mev = dynamic_cast<MouseEvent*>(event);
		if (mev == NULL)
			return;
			
		if (rect->contains(mev->getX(), mev->getY()))
			(*action)(event);
	}
	void Button::setAction(Func f){
		action = f;
	}
	void Button::setText(std::string t, TTF_Font* font){
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
		textRect = &(getRectangle()->centeredRect(textImg->w, textImg->h));
	}
	std::string Button::getText() const{
		return text;
	}
	Rectangle* Button::getRectangle() const{
		return rect;
	}

	void Button::draw() const{
		SDL_Rect* tmp = getRectangle();
		SDL_Rect tmp2 = {0,0,tmp->w,tmp->h};
		if (true)
			SDL_BlitSurface(image->getSurface(), &tmp2, Window::init()->screen, tmp);
		else
			SDL_BlitSurface(NULL, &tmp2, Window::init()->screen, tmp);
		tmp = textRect;
		SDL_BlitSurface(textImg, NULL, Window::init()->screen, tmp);
	}
}