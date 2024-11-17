#ifndef NETWORKLIBSAMPLE_WEBHOST_HPP
#define NETWORKLIBSAMPLE_WEBHOST_HPP

#include <string>
#include <memory>
#include "networklib.hpp"
#include "HostRecord.hpp"

// A class wrapping a ConnectionHandle from the networklib library.
class WebHost final
{
public:
   // Connects to the given host.
   explicit WebHost(const std::string &host);

   // Obtains the given page from this host.
   std::string getPage(const std::string &page);

private:
   std::unique_ptr<ConnectionHandle, decltype(&closeConnection)> connection_{nullptr, closeConnection};
};

WebHost::WebHost(const std::string &host)
{
   HostRecord hostRecord{host};
   if (hostRecord.get())
   {
      connection_ = {connectToHost(hostRecord.get()), closeConnection};
   }
}

std::string WebHost::getPage(const std::string &page)
{
   std::string resultAsString;
   if (connection_)
   {
      std::unique_ptr<char[], decltype(&freeWebPage)> result{
          retrieveWebPage(connection_.get(), page.c_str()),
          freeWebPage
      };
      resultAsString = result.get();
   }

   return resultAsString;
}


#endif //NETWORKLIBSAMPLE_WEBHOST_HPP
