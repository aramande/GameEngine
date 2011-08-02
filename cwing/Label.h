#ifndef CLABEL_H
#define CLABEL_H

#include "Komponent.h"
#include <string>

namespace cwing{

	class CLabel : public Komponent{
	public:
		~CLabel(void);
		std::string getText() const;
		void setText(std::string t);
		static CLabel* getInstance(int x, int y, std::string t);
		void draw() const;
	private:
		std::string text;

		CLabel(int x, int y, std::string t);
	};
} // cwing

#endif