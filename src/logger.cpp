#include <iostream>
#include <sstream>
#include "logger.h"
namespace engine{
	Logger* Logger::log = NULL;

	Logger::Logger(std::string s){
		file = std::ofstream(s);
	}

	Logger::~Logger(){
		file.close();
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

	std::string Logger::toStr(int value){
		std::stringstream temp(std::stringstream::out);
		temp << value;
		temp.flush();
		return temp.str();
	}

	std::string Logger::toStr(double value){
		std::stringstream temp(std::stringstream::out);
		temp << value;
		temp.flush();
		return temp.str();
	}

	void Logger::print(const char* message){
		file << message << '\n';
		file.flush();
	}

	void Logger::print(std::string& message){
		file << message.c_str() << '\n';
		file.flush();
	}

	void Logger::operator<<(std::string& message){
		print(message);
	}
}