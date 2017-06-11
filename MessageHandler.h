#ifndef HFILE_MESSAGE_HANDLER
#define HFILE_MESSAGE_HANDLER


class MessageHandler
{
public:
	enum MessageRecipient
	{
		MessageRecipient_Error,
		//Other message recipients
	};
public:
	static MessageHandler& GetInstance();

	void Receive(const std::string& message, MessageRecipient messageRecipient);
private:
	MessageHandler();
	std::unordered_map<std::string, void*> messageResponseMap;
	
};


class Handler
{
public:
	static Handler& GetInstance();
private:
	Handler();
	std::unordered_map<std::string, void*> messageResponseMap;
};


class ErrorHandler : public Handler
{
public:
	enum Error
	{
		
	};
private:
};


#endif /*HFILE_MESSAGE_HANDLER*/