#ifndef KOMPONENT_H
#define KOMPONENT_H

#include "Rectangle.h"

namespace cwing{

	class Komponent{
	public:
		virtual ~Komponent();
		const Rectangle& getRect() const;
		virtual void draw() const = 0; 
		virtual void mouseDown(int x, int y);
		virtual void mouseUp(int x, int y);

	protected:		
		Komponent(int x, int y, int w, int h);
	private:
		Rectangle rect;

		Komponent(const Komponent& other);
		const Komponent& operator=(const Komponent& other);
	};

} // cwing
#endif