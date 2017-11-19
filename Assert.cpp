#include <string>
#include "include/Utilities/Logger.h"
#include "Assert.h"

/*
* Global functions
*/
void AssertTrue(bool boolExpression, const std::string& fatalMessage)
{
    if (!boolExpression)
    {
        Logger::GetInstancePtr()->Log(fatalMessage, Logger::LogType_Fatal);
        //Graceful program termination (call a method that writes logs to file(s), closes all files, etc., 
        //then exit(EXIT_FAILURE)). Note that EXIT_FAILURE and EXIT_SUCCESS are constants that already exist in C++.
    }
}

void AssertFalse(bool boolExpression, const std::string& fatalMessage)
{
    AssertTrue(!boolExpression, fatalMessage);
}