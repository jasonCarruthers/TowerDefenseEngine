#ifndef HFILE_LOGGER
#define HFILE_LOGGER

#include <vector>



class Logger
{
public: 
enum LogType
{
    LogType_Debug,  //Used for debugging. Values of vars, enter method, exit method, etc. Turn off for production.
    LogType_Info,   //Used for narrating the program's path. Begin task, finished task, etc. Always on.
    LogType_Error,  //Used when an error has occured. Errors are failures that are not bad enough to cause program termination.
    LogType_Fatal,   //Used when a fatal has occured. Fatals are failures that are bad enough to cause program termination.
};
private: Logger();
public: static Logger* GetInstancePtr();
public: void Log(const std::string& log, Logger::LogType logType);
private: bool IsLogTypeValid(Logger::LogType logType);
private: static bool EXISTS;
public: static std::vector<std::string> LOG_TYPE_STR;
};


#endif /*HFILE_LOGGER*/