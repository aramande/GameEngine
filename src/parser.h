#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "logger.h"

namespace engine{
	/**
	 * Abstract class to parse files for both reading and writing.
	 */
	class Parser{
	protected:
		Parser(){}
		/** 
		 * String searching help functions. 
		 * These functions all strip line of any extra whitespace 
		 * to make sure that it can give the most accurate answer.
		 */
		bool consistsOf(const std::string& line, const std::string& searchItem){
			std::string source = trim(line, " \n\r\t;");
			return source == searchItem;
		}
		bool startsWith(const std::string& line, const std::string& searchItem){
			std::string source = trim(line, " \n\r\t;");
			//logger->printf("%s starts with %s", source.c_str(), searchItem.c_str());
			return source.compare(0, searchItem.length(), searchItem) == 0;
		}
		bool endsWith(const std::string& line, const std::string& searchItem){
			std::string source = trim(line, " \n\r\t;");
			//std::cout << source.substr(source.length()-searchItem.length(), searchItem.length()) << "!"<< std::endl;
			return source.compare(source.length()-searchItem.length(), searchItem.length(), searchItem) == 0;
		}
		bool contains(const std::string& line, const std::string& searchItem){
			std::string source = trim(line, " \n\r\t;");
			return source.find(searchItem) != std::string::npos;
		}

		/**
		 * String manipulation help functions
		 */
		std::string trim(std::string source, const std::string& token){
			return trimRight(trimLeft(source, token), token);
		}
		std::string trimRight(std::string source, const std::string &token) {
			source.erase(source.find_last_not_of(token)+1);
			return source;
		}
		std::string trimLeft(std::string source, const std::string &token) {
			source.erase(0, source.find_first_not_of(token));
			return source;
		}
		std::vector<std::string> split(std::string source, const char& delim){
			size_t delimLocation = -1, lastLocation = -1;
			std::vector<std::string> result;
			while(source != ""){
				delimLocation = source.find(delim, delimLocation+1);
				if(delimLocation == std::string::npos){
					// Last string, just add it
					result.push_back(source.substr(lastLocation+1));
					//logger->printf("Splitting last word: %s", result[result.size()-1].c_str());
					break;
				}
				result.push_back(source.substr(lastLocation+1, delimLocation-lastLocation-1));
				//logger->printf("Splitting word: %s", result[result.size()-1].c_str());
				lastLocation = delimLocation;
			}
			return result;
		}


		/**
		 * Checks if the line contains a variable defenition and stores the value
		 * of the variable.
		 *
		 * @param line String to search through
		 * @param searchItem String to search for
		 * @param value The value of the variable, or an empty string if it's not on
		 * this line
		 *
		 * @returns true if this line has information about the searchItem
		 * variable, false otherwise
		 */
		virtual bool isVariable(const std::string& line, const std::string& searchItem, std::string& value) = 0;

		/**
		 * Check if this line is a specific category, and store all
		 * arguments that follows the category declaration.
		 *
		 * @param line String to search through
		 * @param searchItem String to search for
		 * @param argv Passes on the tokens after searchItem until linebreak (\n) 
		 * or opening brace ({)
		 *
		 * @returns true if this line has information about the searchItem
		 * category, false otherwise
		 */
		virtual bool isCategory(const std::string& line, const std::string& searchItem, std::vector<std::string>& argv) = 0;

	public:
		virtual ~Parser(){}
		virtual void read(const std::string& filename) = 0;
		virtual void write(const std::string& filename) const = 0;
	};
}

#endif
