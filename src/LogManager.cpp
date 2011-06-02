#include <LogManager.h>
#include <LogFacilityProvider.h>

LogManager::LogManager()
{
}

// Manage LogLevel List
   /**
    * Adds a new LogLevel to Levels. Note priority is assigned
    * sequentially in a first is highest policy.
    * @param name String representation of the level
    * @param abbr Abbreviation of the level's string representation.
    *             Default to empty string.
    */
void LogManager::addLogLevel(std::string name, std::string abbr)
{
    unsigned int tmp;
    if( _Levels.empty() )
    {
        tmp = 0;
    }
    else
    {
        tmp = _Levels.size() - 1;
    }
    _Levels[tmp] = new LogLevel(tmp, name, abbr);
}

   /**
    * Returns a registered LogLevel by its priority.
    * @param level LogLevel priority.
    * @return Registered LogLevel of specified priority.
    */
LogLevel* const LogManager::getLogLevelByPriority(unsigned int level) const
{
    return _Levels.find(level)->second;
}

   /**
    * Returns the priority of the last registered LogLevel. (_Levels.size() - 1)
    * @return Priority of last registered LogLevel. Least priority level.
    */
unsigned int LogManager::getLeastPriorityLevel() const
{
    if( _Levels.empty() ) return 0;
    return _Levels.size() - 1;
}

// Manage log messages
   /**
    * Publish message to all log facilities.
    */
void LogManager::addLogMessage(LogMessage* message)
{
    for(LogFacilityList::iterator it = _Listeners.begin(); it != _Listeners.end(); ++it)
    {
        (*it)->printMessage(message);
    }
}

   /**
    * Publish message to all log facilities.
    */
void LogManager::addLogMessage(std::string message, LogLevel level)
{
    this->addLogMessage( new LogMessage(message, level) );
}

   /**
    * Publish message to a certain facility.
    */
void LogManager::addLogMessageTo(LogMessage* message, LogFacilityProvider* facility)
{
    facility->addMessage(message);
}

   /**
    * Publish message to a certain facility.
    */
void LogManager::addLogMessageTo(std::string message, LogLevel level, LogFacilityProvider* facility)
{
    this->addLogMessageTo(new LogMessage(message, level), facility);
}

// Manage log facilities
   /**
    * Register a LogFacilityProvider
    */
void LogManager::_registerLogFacilityProvider(LogFacilityProvider* facility)
{
    _Listeners.push_back(facility);
}
