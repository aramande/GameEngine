#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include <string>

namespace engine{
	/**
	 * Breaking the code formatting standard to follow the c++ exception naming
	 * convention with underscored lowercase names.
	 */
	class file_exception : public std::exception{
		std::string message;
	 public:
		file_exception() throw(){
			this->message = "Error, file not loaded";
		}
		file_exception(std::string message) throw(){
			this->message = message;
		}
		~file_exception() throw(){}

		const char* what() const throw(){
			return message.c_str();
		}
	};
}
#endif
