#include <iostream>
#include "ILogger.hpp"
#include "Logger.hpp"

using namespace std;

class Foo
{
public:
   explicit Foo(ILogger *logger) : logger_{logger}
   {
      if (logger_ == nullptr)
      {
         throw invalid_argument{"ILogger cannot be null."};
      }
   }

   void doSomething()
   {
      logger_->log("Hello strategy!", ILogger::LogLevel::Info);
   }

private:
   ILogger *logger_;
};

int main()
{
   Logger concreteLogger{"log.out"};
   concreteLogger.setLogLevel(ILogger::LogLevel::Debug);

   Foo f{&concreteLogger};
   f.doSomething();
}
