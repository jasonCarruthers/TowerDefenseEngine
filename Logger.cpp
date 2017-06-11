#include <iostream>
#include <string>
#include "../../include/Utilities/Logger.h"



/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Logger
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructors
*/
Logger::Logger()
{
}


/*
* Accessors
*/
Logger& Logger::GetInstance()
{
	static Logger *instance = new Logger();
	return *instance;
}


/*
* Mutators
*/
void Logger::Log(const std::string& log)
{
	std::cout << log << "\n";
}