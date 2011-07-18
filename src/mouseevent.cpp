#include <iostream>
#include "mouseevent.h"
namespace engine{
	MouseEvent::MouseEvent(int x, int y, int button, bool pressed, bool moved, int timeSinceLastFrame) : 
		x(x), y(y), button(button), pressed(pressed), moved(moved), Event(timeSinceLastFrame){}

	int MouseEvent::getX() const{
		return x;
	}

	int MouseEvent::getY() const{
		return y;
	}

	int MouseEvent::getButton() const{
		return button;
	}

	bool MouseEvent::isPressed() const{
		return pressed;
	}

	bool MouseEvent::hasMoved() const{
		return moved;
	}
}