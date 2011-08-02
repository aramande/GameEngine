#ifndef SESSION_H
#define SESSION_H

#include "Komponent.h"
#include <vector>
#include <SDL.h>

namespace cwing{
	class Session{
	public:
		Session();
		~Session();
		void add(Komponent* comp);
		void run();
	private:
		std::vector<Komponent*> comps;
		Uint32 bgColor;
		void forAll( void (Komponent::*mf)(int,int), const SDL_Event&);
	};

} //cwing
#endif