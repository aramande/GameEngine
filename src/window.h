/**
 * GameEngine - A regular application window
 * 
 * Author: Aramande <aramande@hackular.com>
 * File Created: Thu Jun 30 13:19:08 2011 UTC+2
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "sdl.h"

namespace engine{
	class Window{
		SDL_Surface* screen;
		int width;
		int height;
		int depth;
		int flags;
	public:
		Window(int w, int h, int d);
		~Window();
		void resize(int w, int h);
		void fullscreen(bool wantFullscreen);
	};
}
#endif
