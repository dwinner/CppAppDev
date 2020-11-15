#ifndef LOGGER_H
#define LOGGER_H

//#include "Preferences.h"
class Preferences;  // forward declaration

class Logger 
{
public:
	static void setPreferences(const Preferences& prefs);
	static void logError(const char* error);
}; 

#endif // LOGGER_H
