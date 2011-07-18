#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "event.h"
namespace engine{
	class MouseEvent : public Event {
	 private:
		 int x, y, button;
		 bool pressed, moved;
	 public:
		 MouseEvent(int x, int y, int button, bool pressed, bool moved, int timeSinceLastFrame);
		 int getX() const;
		 int getY() const;
		 
		 /**
		  * Returns SDL Mouse button identifiers. 
		  * When motion is activated without a button pressed, this function returns 0.
		  */
		 int getButton() const;
		 bool isPressed() const;
		 bool hasMoved() const;
	};
}

#endif