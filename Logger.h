#ifndef HFILE_LOGGER
#define HFILE_LOGGER



class Logger
{
public:
	static Logger& GetInstance();

	void Log(const std::string& log);
private:
	Logger();
};


#endif /*HFILE_LOGGER*/