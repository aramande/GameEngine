#include <iostream>
#include <string.h>
#include <sstream>
#include "logger.h"
namespace engine{
	Logger* Logger::log = NULL;

	Logger::Logger(std::string s){
		file = new std::ofstream(s.c_str());
	}

	Logger::~Logger(){
		file->close();
	}

	Logger* Logger::init(std::string s){
		if(log == NULL)
			log = new Logger(s);
		return log;
	}

	Logger* Logger::init(){
		if(log == NULL)
			log = new Logger("debug.log");
		return log;
	}
	void Logger::print(const char* message){
		//file << message << '\n';
		//file->flush();
		file->write(message, strlen(message));
		file->write("\n", 1);
		file->flush();
	}

	void Logger::print(std::string message){
		//file << message.c_str() << '\n';
		file->write(message.c_str(), message.length());
		//file->flush();
		file->write("\n", 1);
		file->flush();
	}

	void Logger::operator<<(std::string message){
		std::cout<<message.length()<<std::endl;
		print(message);
	}
}
