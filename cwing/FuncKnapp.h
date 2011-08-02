#ifndef FUNCKNAPP_H
#define FUNCKNAPP_H

#include "Knapp.h"

namespace cwing{

typedef void (*Func)(std::string, void *);

class FuncKnapp : public Knapp {
public:
	static FuncKnapp* getInstance(int x, int y, std::string t, 
		Func f, void *some);
protected:
	FuncKnapp(int x, int y, std::string t, Func f, void *some);
	void perform();
private:
	Func fpek;
	void *something;
};

} // cwing
#endif
