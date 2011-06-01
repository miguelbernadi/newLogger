#include <ctime>
#include <LogFacilityProvider.h>

LogFacilityProvider::Log()
{
}

virtual LogFacilityProvider::~Log()
{
}

// Manage actual level of logging.
   /**
    * Points a const_iterator to the selected actual level.
    * This is used to set the message filter.
    * @param level LogLevel numerical identifier. If bigger than
    *              biggest added level the last registered
    *              level is selected.
    */
virtual void LogFacilityProvider::setLoggingToLevel(int level)
{
}

   /**
    * Points a const_iterator to the selected actual level.
    * This is used to set the message filter.
    * @param level LogLevel identifier. Must be previously registered.
    */
virtual void LogFacilityProvider::setLoggingToLevel(LogLevel level)
{
}

   /**
    * Registers itself to the LogManager using _registerLogFacilityProvider(LogFacilityProvider* facility)
    */
virtual void LogFacilityProvider::registerLogFacilityProvider()
{
    LogManager::getSingletonPtr()->_registerLogFacilityProvider(this);
}

virtual std::string LogFacilityProvider::timeOfLog(std::string format)
{
// Things to discover the current date, and convert it to a string in format
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char buffer [80];
    strftime (buffer,80,format.c_str(),timeinfo);
    return buffer;
}

virtual void LogFacilityProvider::addMessage(LogMessage* message)
{
    if( message->getMessagePriority() <= _currentLevel->getMessagePriority() )
    {
        this->printMessage(message);
    }
}