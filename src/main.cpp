#include <cxxtest/ErrorPrinter.h>
#include <iostream>

int main(int argc, char **argv){
	std::cout << "Doing stuff\n";
	CxxTest::ErrorPrinter().run();
	while(true);
	return 0;
}
