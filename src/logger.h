#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <sstream>
#include <string>

namespace engine{
	class Logger{
		std::ofstream file;
		bool toCommand;
		//static Logger* logger;
	public:
		Logger();
		virtual ~Logger();
		/**
		 * Sets the output stream to print loggermessages to
		 */
		//static Logger* init(std::string filename);
		//static Logger* init();

		/**
		 * Print a message to the stream
		 */
		void print(const char* message);
		void print(const std::string& message);
		/**
		 * Print a formatted message to the stream
		 */
		void printf(const char* message, ...);

		void setLogFile(const std::string& filename);
		void setToCommand(bool value);
		void operator<<(std::string message);
	};

	extern Logger* logger;
	
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
