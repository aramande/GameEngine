#ifndef KNAPP_H
#define KNAPP_H

#include <string>
#include <SDL.h>
#include "Komponent.h"

namespace cwing{
	class Knapp : public Komponent{
	public:
		static Knapp* getInstance(int x, int y, std::string t);
		void draw() const;
		void mouseDown(int x, int y);
		void mouseUp(int x, int y);
		virtual void perform();
		std::string getText() const;
		~Knapp();
	protected:
		Knapp(int x, int y, std::string t);
	private:
		SDL_Surface *upIcon, *downIcon;
		std::string text;
		SDL_Color b;
		SDL_Surface* txt;
		SDL_Rect tRect;
		bool isUp;
	};

} 
#endif