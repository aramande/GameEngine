#include "Label.h"
#include "Globals.h"
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

namespace cwing{

	CLabel* CLabel::getInstance(int x, int y, std::string t){
		return new CLabel(x,y,t);
	}

	CLabel::CLabel(int x, int y, string t):Komponent(x,y,300,30),text(t){
	}

	CLabel::~CLabel(){
	}

	string CLabel::getText() const{
		return text;
	}
	void CLabel::setText(string t){
		text = t;
	}

	void CLabel::draw() const{
		SDL_Color b = {0,0,0};
		SDL_Surface* t = TTF_RenderText_Solid(sys.font,text.c_str(),b);
		Rectangle r = getRect().centeredRect(t->w, t->h);
		SDL_BlitSurface(t,NULL,sys.screen, &r);
		SDL_FreeSurface(t);
	}

} // cwing