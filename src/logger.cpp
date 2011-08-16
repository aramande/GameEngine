#include <iostream>
#include <string.h>
#include <sstream>
#include <stdarg.h>
#include "logger.h"
namespace engine{
	Logger* logger= new Logger();

	Logger::Logger() : toCommand(true){}

	Logger::~Logger(){
		if(file.is_open())
			file.close();
	}

//	Logger* Logger::init(std::string s){
//		if(logger == NULL)
//			logger = new Logger(s);
//		return logger;
//	}

//	Logger* Logger::init(){
//		if(logger == NULL)
//			logger = new Logger("debug.logger");
//		return logger;
//	}
	void Logger::print(const char* message){
		if(file.is_open())
			file << message << std::endl;

		if(toCommand)
			std::cout << message << std::endl;
		file.flush();
	}

	void Logger::print(const std::string& message){
		print(message.c_str());
	}

	void Logger::printf(const char* message, ...){
		const size_t length = 1024;
		char* buffer = new char[length];
		va_list args;

		va_start(args, message);
		vsprintf(buffer, message, args);
		va_end(args);

		print(buffer);
	}
	
	void Logger::setLogFile(const std::string& filename){
		if(file.is_open())
			file.close();
		file.open(filename.c_str(), std::ios_base::trunc);
	}

	void Logger::setToCommand(bool value){
		toCommand = value;
	}

	void Logger::operator<<(std::string message){
		std::cout<<message.length()<<std::endl;
		print(message);
	}
}
