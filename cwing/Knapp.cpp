#include "Knapp.h"
#include "Globals.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

namespace cwing{

	Knapp::Knapp(int x, int y, string t):Komponent(x,y,80,50),text(t){
		upIcon = IMG_Load("c:/images/upIcon.PNG");
		downIcon = IMG_Load("c:/images/downIcon.PNG");
		SDL_Color black = {0,0,0};
		b = black;
		SDL_Surface *tmp = TTF_RenderText_Solid(sys.font,text.c_str(),b);
		txt = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);
		tRect = getRect().centeredRect(txt->w, txt->h);
		isUp = true;
	}


	Knapp::~Knapp(){
		SDL_FreeSurface(upIcon);
		SDL_FreeSurface(downIcon);
		SDL_FreeSurface(txt);
	}

	Knapp* Knapp::getInstance(int x, int y, std::string t){
		return new Knapp(x,y,t);
	}

	void Knapp::draw() const{
		SDL_Rect tmp = getRect();
		SDL_Rect tmp2 = {0,0,tmp.w,tmp.h};
		if (isUp)
			SDL_BlitSurface(upIcon, &tmp2, sys.screen, &tmp);
		else
			SDL_BlitSurface(downIcon, &tmp2, sys.screen, &tmp);
		tmp = tRect;
		SDL_BlitSurface(txt, NULL, sys.screen, &tmp);
	}

	void Knapp::mouseDown(int x, int y){
		if (getRect().contains(x,y)){
			isUp = false;
		}
	}

	void Knapp::mouseUp(int x, int y){
		if (!isUp && getRect().contains(x,y))
			perform();
		isUp = true;
	}

	string Knapp::getText() const{
		return text;
	}

	void Knapp::perform(){
	}


} // namespace cwing
