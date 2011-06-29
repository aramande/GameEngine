#ifndef BADARG_H
#define BADARG_H

#include <string>

namespace engine{
	/**
	 * Breaking the code formatting standard to follow the c++ exception naming
	 * convention with underscored lowercase names.
	 */
	class bad_arg : public std::exception{
		std::string message;
	 public:
		bad_arg() throw(){
			this->message = "Error, bad argument received";
		}
		bad_arg(std::string message) throw(){
			this->message = message;
		}
		~bad_arg() throw(){}

		const char* what() const throw(){
			return message.c_str();
		}
	};
}
#endif
