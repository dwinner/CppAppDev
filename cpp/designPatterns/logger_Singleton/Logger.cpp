#include <chrono>
#include "Logger.hpp"

using namespace std;

void Logger::setLogFilename(string aLogFilename)
{
   logFilename = std::move(aLogFilename);
}

Logger &Logger::instance()
{
   static Logger instance; // Thread-safe static local variable.
   return instance;
}

Logger::Logger()
{
   outputStream_.open(logFilename, ios_base::app);
   if (!outputStream_.good())
   {
      throw runtime_error{"Unable to initialize the Logger!"};
   }

   println(outputStream_, "{}: Logger started.", chrono::system_clock::now());
}

Logger::~Logger()
{
   println(outputStream_, "{}: Logger stopped.", chrono::system_clock::now());
}

void Logger::setLogLevel(LogLevel level)
{
   logLevel_ = level;
}

string_view Logger::getLogLevelString(LogLevel level) const
{
   switch (level)
   {
      case LogLevel::Debug:
         return "DEBUG";
      case LogLevel::Info:
         return "INFO";
      case LogLevel::Error:
         return "ERROR";
   }

   throw runtime_error{"Invalid log level."};
}

void Logger::log(string_view message, LogLevel logLevel)
{
   if (logLevel_ > logLevel)
   {
      return;
   }

   println(outputStream_, "{}: [{}] {}", chrono::system_clock::now(),
           getLogLevelString(logLevel), message);
}
