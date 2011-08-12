#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <sstream>
#include <string>

namespace engine{
	class Logger{
		std::ofstream* file;
		static Logger* log;
		Logger(std::string filename);
	public:
		virtual ~Logger();
		/**
		 * Sets the output stream to print logger messages to
		 */
		static Logger* init(std::string filename);
		static Logger* init();

		//static std::string toStr(long value);
		//static std::string toStr(double value);

		/**
		 * Print a message to the stream
		 */
		void print(const char* message);
		void print(std::string message);
		void operator<<(std::string message);
	};
	
	/**
	 * Convert other values to string
	 */
	template<class T>
		std::string toStr(T value){
			std::stringstream temp(std::stringstream::out);
			temp << value;
			temp.flush();
			return temp.str();
		}

}
#endif
