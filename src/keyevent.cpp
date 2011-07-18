#include "keyevent.h"
namespace engine{
	KeyEvent::KeyEvent(SDLKey key, SDLMod mod, bool pressed, int timeSinceLastFrame) : 
		key(key), mod(mod), pressed(pressed), Event(timeSinceLastFrame){}

	SDLKey KeyEvent::getKey() const{
		return key;
	}

	SDLMod KeyEvent::getModifier() const{
		return mod;
	}

	bool KeyEvent::isPressed() const{
		return pressed;
	}
}