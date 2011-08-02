#include "Label.h"
#include "MemKnapp.h"
#include "Session.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace cwing;
using namespace std;

class Valued{
private:
	int value;
	CLabel* lab;
public:
	Valued(CLabel* la):value(0), lab(la){}
	void oka(string str){
		value++;
		ostringstream oss;
		oss << value;
		lab->setText(oss.str());
	}

	void minska(string str){
		value--;
		ostringstream oss;
		oss << value;
		lab->setText(oss.str());
	}
}; // Valued

int main(int argc, char **argv){
	Session ses;

	CLabel* lab = CLabel::getInstance(20,20,"0");
	ses.add(lab);
	Valued val(lab);

	Knapp* k1 = MemKnapp<Valued>::getInstance(20, 100, "Öka",&val,&Valued::oka);
	ses.add(k1);
	Knapp* k2 = MemKnapp<Valued>::getInstance(200, 100, "Minska",&val,&Valued::minska);
	ses.add(k2);

	ses.run();
	return 0;
}
/*
class MinKnapp : public cwing::Knapp{
public:
	MinKnapp(int x, int y, string t):Knapp(x,y,t){}
	void perform(){
		if (getText() == "Öka")
			value++;
		else
			value--;
		cout << value << endl;
	}
};

*/
