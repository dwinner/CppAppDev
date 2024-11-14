#ifndef LOGGER_SINGLETON_LOGGER_HPP
#define LOGGER_SINGLETON_LOGGER_HPP

#include <string>
#include <fstream>

// Definition of a singleton logger class.
class Logger final
{
public:
   enum class LogLevel
   {
      Debug,
      Info,
      Error
   };

   // Sets the name of the log file.
   // Note: needs to be called before the first call to instance()!
   static void setLogFilename(std::string aLogFilename);

   // Returns a reference to the singleton Logger object.
   static Logger &instance();

   // Prevent copy/move construction.
   Logger(const Logger &) = delete;

   Logger(Logger &&) = delete;

   // Prevent copy/move assignment operations.
   Logger &operator=(const Logger &) = delete;

   Logger &operator=(Logger &&) = delete;

   // Sets the log level.
   void setLogLevel(LogLevel level);

   // Logs a single message at the given log level.
   void log(std::string_view message, LogLevel logLevel);

private:
   // Private constructor and destructor.
   Logger();

   ~Logger();

   // Converts a log level to a human-readable string.
   [[nodiscard]] std::string_view getLogLevelString(LogLevel level) const;

   static inline std::string logFilename;
   std::ofstream outputStream_;
   LogLevel logLevel_{LogLevel::Error};
};


#endif //LOGGER_SINGLETON_LOGGER_HPP
