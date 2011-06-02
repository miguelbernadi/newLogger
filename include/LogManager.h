#ifndef LogManager_H_
#define LogManager_H_

#include <string>
#include <map>
#include <vector>
//#include <memory>

// Forward declarations.
class LogFacilityProvider;
class LogLevel;

typedef std::map< unsigned int, LogLevel* > LevelList;

/**
 * Defines a numeric level for comparison (should be unique) and associates it
 * to its string representations.
 */
class LogLevel
{
  private:
   /**
    * Needed for message filtering.
    */
    unsigned int _LevelPriority;
   /**
    * String displayed on log entries of this level.
    */
    std::string _LevelName;
   /**
    * String abbreviation displayed on log entries of this level.
    */
    std::string _LevelAbbr;
  public:
    LogLevel(int number, std::string name, std::string abbr) : _LevelPriority(number), _LevelName(name), _LevelAbbr(abbr) { }
    unsigned int getPriority() const { return _LevelPriority; }
    std::string getName() const { return _LevelName; }
    std::string getAbbr() const { return _LevelAbbr; }

   // Comparison operator
};

/**
 *
 */
class LogMessage
{
  private:
    std::string const _Message;
    LogLevel const _MessageLevel;

  public:
    LogMessage(std::string message, LogLevel level) : _Message(message), _MessageLevel(level) { }
    std::string getMessage() const { return _Message; }
    LogLevel getLevel() const { return _MessageLevel; }
    unsigned int const getMessagePriority() const { return _MessageLevel.getPriority(); }
};

/**
 * Manages the logs and loglevels.
 * @note Should be a singleton.
 */
class LogManager
{
  public:
    typedef std::vector< LogFacilityProvider* > LogFacilityList;
//    typedef std::auto_ptr< LogManager > LogManagerPtr;
    typedef LogManager* LogManagerPtr;

  private:
    LevelList _Levels;
    LogFacilityList _Listeners;

    static LogManagerPtr _ptr;

   /**
    * Private constructor. Is a Singleton.
    */
    LogManager();
    LogManager(const LogManager& p);

  public:

// Manage LogLevel List
   /**
    * Adds a new LogLevel to Levels. Note priority is assigned
    * sequentially in a first is highest policy.
    * @param name String representation of the level
    * @param abbr Abbreviation of the level's string representation.
    *             Default to empty string.
    */
    void addLogLevel(std::string name, std::string abbr = "");
   /**
    * Sets the LevelList to a certain level list created by
    * the user by hand.
    */
    void _setLogLevelList(LevelList levelList) { _Levels = levelList; }
   /**
    * Returns a registered LogLevel by its priority.
    * @param level LogLevel priority.
    * @return Registered LogLevel of specified priority.
    */
    LogLevel* const getLogLevelByPriority(unsigned int level) const;
   /**
    * Returns the priority of the last registered LogLevel. (_Levels.size() - 1)
    * @return Priority of last registered LogLevel. Least priority level.
    */
    unsigned int getLeastPriorityLevel() const;

// Manage log messages
   /**
    * Publish message to all log facilities.
    */
    void addLogMessage(LogMessage* message);
   /**
    * Publish message to all log facilities.
    */
    void addLogMessage(std::string message, LogLevel level);
   /**
    * Publish message to a certain facility.
    */
    void addLogMessageTo(LogMessage* message, LogFacilityProvider* facility);
   /**
    * Publish message to a certain facility.
    */
    void addLogMessageTo(std::string message, LogLevel level, LogFacilityProvider* facility);

// Manage log facilities
   /**
    * Register a LogFacilityProvider
    */
    void _registerLogFacilityProvider(LogFacilityProvider* facility);

// Static memebers
    static void create() { _ptr = new LogManager(); }
    static LogManagerPtr getSingletonPtr() { return _ptr; }
    static void destroy() { delete _ptr; }
};

#endif

