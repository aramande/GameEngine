#ifndef CWINGERROR_H
#define CWINGERROR_H

#include <string>

namespace cwing{

	struct CwingError{
		std::string message;
		CwingError(std::string m):message(m){}
	};

}//cwing
#endif