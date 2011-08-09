#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "event.h"
#include "sdl.h"
namespace engine{
	class KeyEvent : public Event {
	 private:
		 SDLKey key;
		 SDLMod mod;
		 Uint16 unicode;
		 bool pressed;
	 public:
		 KeyEvent(SDLKey key, SDLMod mod, Uint16 unicode, bool pressed, int timeSinceLastFrame);
		 SDLKey getKey() const;
		 SDLMod getModifier() const;
		 Uint16 getUnicode() const;
		 bool isPressed() const;
	};
}

#endif