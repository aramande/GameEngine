#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <string>
#include "component.h"

namespace engine {
	typedef int Event; // temporary
	typedef void (*FPoint)(Event); 
	class Button : public Component {
		std::string text;
		std::vector<FPoint> codes;
	protected:
	public:
		Button(int x, int y, int w, int h);
		void buttonDown(FPoint code);
		void buttonUp(FPoint code);
		
	};
}

#endif