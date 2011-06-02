#ifndef LogFacilityProvider_H_
#define LogFacilityProvider_H_

#include <string>
#include "LogManager.h"

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
    LogLevel* _currentLevel;

  public:
    LogFacilityProvider(LogLevel* level);
    virtual ~LogFacilityProvider();

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
    virtual void setLoggingToLevel(LogLevel* level);
   /**
    * @return LogLevel corresponding to actual LogLevel.
    */
    virtual LogLevel const getLoggingLevel() const { return *_currentLevel; }
   /**
    * Registers itself to the LogManager using _registerLogFacilityProvider(LogFacilityProvider* facility)
    */
    virtual void registerLogFacilityProvider();

// Message management
   /**
    * Returns a string containing the time message is logged.
    *
    * @param format
    * <table>
    * <tr><td>specifier</td><td>Replaced by</td><td>Example</td></tr>
    * <tr><td>%%a</td><td>Abbreviated weekday name *</td><td>Thu</td></tr>
    * <tr><td>%%A</td><td>Full weekday name *</td><td>Thursday</td></tr>
    * <tr><td>%%b</td><td>Abbreviated month name *</td><td>Aug</td></tr>
    * <tr><td>%%B</td><td>Full month name *</td><td>August</td></tr>
    * <tr><td>%%c</td><td>Date and time representation *</td><td>Thu Aug 23 14:55:02 2001</td></tr>
    * <tr><td>%%d</td><td>Day of the month (01-31)</td><td>23</td></tr>
    * <tr><td>%%H</td><td>Hour in 24h format (00-23)</td><td>14</td></tr>
    * <tr><td>%%I</td><td>Hour in 12h format (01-12)</td><td>02</td></tr>
    * <tr><td>%%j</td><td>Day of the year (001-366)</td><td>235</td></tr>
    * <tr><td>%%m</td><td>Month as a decimal number (01-12)</td><td>08</td></tr>
    * <tr><td>%%M</td><td>Minute (00-59)</td><td>55</td></tr>
    * <tr><td>%%p</td><td>AM or PM designation</td><td>PM</td></tr>
    * <tr><td>%%S</td><td>Second (00-61)</td><td>02</td></tr>
    * <tr><td>%%U</td><td>Week number with the first Sunday as the first day of week one (00-53)</td><td>33</td></tr>
    * <tr><td>%%w</td><td>Weekday as a decimal number with Sunday as 0 (0-6)</td><td>4</td> </tr>
    * <tr><td>%%W</td><td>Week number with the first Monday as the first day of week one (00-53)</td><td>34</td></tr>
    * <tr><td>%%x</td><td>Date representation *</td><td>08/23/01</td></tr>
    * <tr><td>%%X</td><td>Time representation *</td><td>14:55:02</td></tr>
    * <tr><td>%%y</td><td>Year, last two digits (00-99)</td><td>01</td></tr>
    * <tr><td>%%Y</td><td>Year</td><td>2001</td></tr>
    * <tr><td>%%Z</td><td>Timezone name or abbreviation</td><td>CDT</td></tr>
    * <tr><td>%%</td><td>A % sign</td><td>%</td></tr>
    * </table>
    *
    * The specifiers whose description is marked with an asterisk (*) are locale-dependent.
    */
    virtual std::string timeOfLog(std::string format = "%Y%m%d %H:%M:%S");
   /**
    * If message priority is higher than provider's, the message is printed.
    */
    virtual void addMessage(LogMessage* message);
   /**
    * @warning Must delete message after printing.
    */
    virtual void printMessage(LogMessage* message) = 0;
};

#endif

