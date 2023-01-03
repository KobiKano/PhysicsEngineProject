#pragma once

#include <iostream>

/*
This class will be used to set logger levels for various outputs
Allows for removal of unneciary clutter to console(speeds up program)
*/
class Logger {
public:
	//public enum for levels
	enum Level {
		error = 0, debug, info
	};
private:
	//private members
	Level level;
public:
	//default constructor
	Logger() {}

	//contstructor for logger
	Logger(Level _level) {
		level = _level;
	}

	//Following functions print message according to level of logger
	void errorLog(std::string message) {
		if (level >= error) {
			std::cout << message;
		}
	}

	void debugLog(std::string message) {
		if (level >= debug) {
			std::cout << message;
		}
	}

	void infoLog(std::string message) {
		if (level >= info) {
			std::cout << message;
		}
	}

	//this function changes the logger level
	void setLevel(Level level) {
		this->level = level;
	}
};