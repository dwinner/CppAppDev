#ifndef LOGGER_STRATEGY_ILOGGER_HPP
#define LOGGER_STRATEGY_ILOGGER_HPP

#include <string_view>

/**
 * @brief Definition of a logger interface.
 */
class ILogger
{
public:
   /**
    * @brief Virtual destructor.
    */
   virtual ~ILogger() = default;

   /**
    * @brief Enumeration for the different log levels.
    */
   enum class LogLevel
   {
      Debug,
      Info,
      Error
   };

   /**
    * @brief Sets the log level.
    * @param level log level
    */
   virtual void setLogLevel(LogLevel level) = 0;

   /**
    * @brief Logs a single message at the given log level.
    * @param message message
    * @param logLevel log level
    */
   virtual void log(std::string_view message, LogLevel logLevel) = 0;
};

#endif //LOGGER_STRATEGY_ILOGGER_HPP
