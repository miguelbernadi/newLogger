#ifndef LogManager_H_
#define LogManager_H_

#include <string>
#include <map>

// Forward declarations.
class LogFacilityProvider;

typedef std::map< unsigned int, LogLevel > LevelList;

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
    unsigned int const _LevelPriority;
   /**
    * String displayed on log entries of this level.
    */
    std::string const _LevelName;
   /**
    * String abbreviation displayed on log entries of this level.
    */
    std::string const _LevelAbbr;
  public:
    LogLevel(int number, std::string name, std::string abbr) : _LevelPriority(number), _LevelName(name), _LevelAbbr(abbr) { }
    unsigned int const getPriority() const { return _LevelNumber; }
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
    LogLevel _MessageLevel;

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

  private:
    LevelList _Levels;
    LogFacilityList _Listeners;
    static LogManager* _ptr;

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
    LogLevel const getLogLevelByPriority(unsigned int level) const;
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
    void addLogMessage(std::string message, unsigned int level);
   /**
    * Publish message to a certain facility.
    */
    void addLogMessageTo(LogMessage* message, LogFacilityProvider* facility);
   /**
    * Publish message to a certain facility.
    */
    void addLogMessageTo(std::string message, unsigned int level, LogFacilityProvider* facility);

// Manage log facilities
   /**
    * Register a LogFacilityProvider
    */
    void _registerLogFacilityProvider(LogFacilityProvider* facility);

// Static memebers
    static void create() { _ptr = new LogManager(); }
    static LogManager* getSingletonPtr() { return _ptr; }
    static void destroy() { delete _ptr; }
};

#endif

