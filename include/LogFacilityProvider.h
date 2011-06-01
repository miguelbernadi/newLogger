#ifndef LogFacilityProvider_H_
#define LogFacilityProvider_H_

#include <string>

class LogLevel;

/** \class Log
 * Abstract class to be derived by the Log backends (FileLog, CLILog...)
*/
class LogFacilityProvider
{
  private:
    std::string _LogName;
   /**
    * Needed for message filtering. Messages with LogLevel._LevelPriority 
    * higher than this are ignored. 
    */
    LogLevel _currentLevel;

  public:
    Log();
    virtual ~Log();
   
    virtual std::string getLogName() const { return _LogName; }

// Manage actual level of logging.
   /**
    * Points a const_iterator to the selected actual level. 
    * This is used to set the message filter.
    * @param level LogLevel numerical identifier. If bigger than
    *              biggest added level the last registered
    *              level is selected.
    */
    virtual void setLoggingToLevel(int level);
   /**
    * Points a const_iterator to the selected actual level. 
    * This is used to set the message filter.
    * @param level LogLevel identifier. Must be previously registered.
    */
    virtual void setLoggingToLevel(LogLevel level);
   /**
    * @return LogLevel corresponding to actual LogLevel.
    */
    virtual LogLevel const getLoggingLevel() const { return *_currentLevel; }
   /**
    * Registers itself to the LogManager using _registerLogFacilityProvider(LogFacilityProvider* facility)
    */
    virtual registerLogFacilityProvider();

// Message management
    virtual void printMessage(LogMessage* message) = 0;
};

#endif

