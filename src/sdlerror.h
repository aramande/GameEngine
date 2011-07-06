#ifndef SDLERROR_H
#define SDLERROR_H

#include <string>

namespace engine{
	/**
	 * Breaking the code formatting standard to follow the c++ exception naming
	 * convention with underscored lowercase names.
	 */
	class sdl_error : public std::exception{
		std::string message;
	 public:
		sdl_error() throw(){
			this->message = "Error, an SDL library has caused a malfunction";
		}
		sdl_error(std::string message) throw(){
			this->message = message;
		}
		~sdl_error() throw(){}

		const char* what() const throw(){
			return message.c_str();
		}
	};
}
#endif
