#ifndef CLIFacility_H_
#define CLIFacility_H_

#include <iostream>
#include "LogFacilityProvider.h"

class CLIFacility : public LogFacilityProvider
{
  public:
    CLIFacility() { }
    void printMessage(LogMessage* message)
    {
        std::cout << timeOfLog << " ("<< message->getLevel().getAbbr() << ") " << message->getLevel().getName() << ": " << message->getMessage() << std::endl;
    }
};

#endif

