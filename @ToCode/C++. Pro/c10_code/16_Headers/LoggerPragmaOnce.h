#pragma once

#include "Preferences.h"

class Logger 
{
public:
	static void setPreferences(const Preferences& prefs);
	static void logError(const char* error);
}; 
