#include <string>
#include <unordered_map>
#include "../../include/Message/MessageHandler.h"



/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class MessageHandler
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructors
*/
MessageHandler::MessageHandler()
{
}


/*
* Accessors
*/
MessageHandler& MessageHandler::GetInstance()
{
	static MessageHandler *instance = new MessageHandler();
	return *instance;
}


/*
* Mutators
*/
void MessageHandler::Receive(const std::string& message, MessageHandler::MessageRecipient)
{
	
}