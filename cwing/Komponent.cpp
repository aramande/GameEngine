#include "Komponent.h"

namespace cwing{
	Komponent::Komponent(int x,int y,int w,int h):rect(x,y,w,h) {
	}

	Komponent::~Komponent(){
	}

	const Rectangle& Komponent::getRect() const{
		return rect;
	}

	void Komponent::mouseDown(int x, int y){
	}
	void Komponent::mouseUp(int x, int y){
	}




} //cwing
