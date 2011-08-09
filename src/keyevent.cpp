#include "keyevent.h"
namespace engine{
	KeyEvent::KeyEvent(SDLKey key, SDLMod mod, Uint16 unicode, bool pressed, int timeSinceLastFrame) : 
		key(key), mod(mod), unicode(unicode), pressed(pressed), Event(timeSinceLastFrame){}

	SDLKey KeyEvent::getKey() const{
		return key;
	}

	SDLMod KeyEvent::getModifier() const{
		return mod;
	}

	Uint16 KeyEvent::getUnicode() const{
		return unicode;
	}

	bool KeyEvent::isPressed() const{
		return pressed;
	}
}