#include <iostream>
#include <string>
#include <vector>
#include "../../Assert.h"
#include "../../include/Utilities/Logger.h"



/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Logger
* -------------------------------------------------------------------------------------------------------
*/
/*
* Initialize static variables
*/
bool Logger::EXISTS = false;
std::vector<std::string> Logger::LOG_TYPE_STR = { "DEBUG", "INFO", "ERROR", "FATAL" };

/*
* Constructors
*/
Logger::Logger()
{
}


/*
* Accessors
*/
Logger* Logger::GetInstancePtr()
{
	static Logger *instance;
    if(!EXISTS)
    {
        EXISTS = true;
        instance = new Logger();
    }
	return instance;
}

bool Logger::IsLogTypeValid(Logger::LogType logType)
{
    return Logger::LogType_Debug == logType || Logger::LogType_Info == logType ||
           Logger::LogType_Error == logType || Logger::LogType_Fatal == logType;
}


/*
* Mutators
*/
void Logger::Log(const std::string& log, Logger::LogType logType)
{
    std::string fatalMessage = "Log type " + std::to_string((int)logType) + " is not valid.";
    AssertTrue(IsLogTypeValid(logType), fatalMessage);
	std::cout << "[" << Logger::LOG_TYPE_STR[logType] << "] " << log << "\n";
}