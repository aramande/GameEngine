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
	extern SDL_Surface* mainScreen;
	class Window{
		int width;
		int height;
		int depth;
		int flags;
		static Window* win;
		Window(Window&){}
		Window* operator=(Window&){}
	protected:
		Window(int w, int h, int d);
	public:
		static Window* init(int w = 640, int h = 480, int d = 32);
		static void kill();
		~Window();
		int getWidth() const;
		int getHeight() const;
		int getDepth() const;
		int getFlags() const;
		void setFlags(int flags) const;
		void resize(int w, int h);
		void fullscreen(bool wantFullscreen);
	};
}
#endif
