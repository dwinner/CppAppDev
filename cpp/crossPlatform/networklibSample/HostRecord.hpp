#ifndef NETWORKLIBSAMPLE_HOSTRECORD_HPP
#define NETWORKLIBSAMPLE_HOSTRECORD_HPP

#include <string>
#include <memory>
#include "networklib.hpp"

// A class wrapping a HostHandle from the networklib library.
class HostRecord final
{
public:
   // Looks up the host record for the given host.
   explicit HostRecord(const std::string &host) :
       hostHandle_{
           lookupHostByName(host.c_str()),
           freeHostHandle
       }
   {}

   // Returns the underlying handle.
   HostHandle *get() const noexcept
   {
      return hostHandle_.get();
   }

private:
   std::unique_ptr<HostHandle, decltype(&freeHostHandle)> hostHandle_;
};


#endif //NETWORKLIBSAMPLE_HOSTRECORD_HPP
