#include <vector>
#include <string>
#include "component.h"

namespace engine {

	typedef int FPoint; //temporary
	class Button : public Component {
		std::string text;
		std::vector<FPoint> codes;
		
	protected:
		Button(int x, int y) : Component(x, y){}
		
	public:
		virtual void buttonDown(FPoint code); // insert function pointers here
		virtual void buttonUp(FPoint code);
		
	};
}