#include "button.h"
namespace engine{
	Button::Button(int x, int y, Image* img, std::string text, EventListener* action) : Component(x, y, img->getWidth(), img->getHeight()){
		if(img == NULL) throw bad_arg("Image cannot be null");
		if(action == NULL){
			ClassListener<Button>* classAction = new ClassListener<Button>(this, &Button::dummy);
		}
		else
			this->action = action;
		this->image = img;
		this->rect = new Rectangle(x, y, image->getWidth(), image->getHeight());	
		setText(text, Resource::loadFont("FreeUniversal-Bold.ttf", 14));
	}

	Button::~Button(){
		delete textRect;
		textRect = NULL;
		delete rect;
		rect = NULL;
		delete image;
		image = NULL;
		SDL_FreeSurface(textImg);
		delete textImg;
		textImg = NULL;
	}

	void Button::perform(Event* event){
		MouseEvent* mev = dynamic_cast<MouseEvent*>(event);
		if (mev == NULL)
			return;
			
		if (rect->contains(mev->getX(), mev->getY()))
			(*action)(mev);
	}
	void Button::setAction(EventListener* f){
		action = f;
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
		SDL_Rect target = rect->getSDL_Rect();
		SDL_Rect source = {0,0,target.w,target.h};
		if (true)
			SDL_BlitSurface(image->getSurface(), &source, mainScreen, &target);
		else
			SDL_BlitSurface(NULL, &source, mainScreen, &target);
		target = textRect->getSDL_Rect();
		SDL_BlitSurface(textImg, NULL, mainScreen, &target);
	}
}