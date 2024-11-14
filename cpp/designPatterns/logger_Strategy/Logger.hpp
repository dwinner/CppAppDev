#ifndef LOGGER_STRATEGY_LOGGER_HPP
#define LOGGER_STRATEGY_LOGGER_HPP

#include <fstream>
#include "ILogger.hpp"

class Logger : public ILogger
{
public:
   explicit Logger(const std::string &logFilename);

   void setLogLevel(LogLevel level) override;

   void log(std::string_view message, LogLevel logLevel) override;

private:
   // Converts a log level to a human-readable string.
   std::string_view getLogLevelString(LogLevel level) const;

   std::ofstream outputStream_;
   LogLevel logLevel_{LogLevel::Error};
};


#endif //LOGGER_STRATEGY_LOGGER_HPP
