#pragma once

#include <string>
#include <print>

/**
 * Basic Process class.
 */
class Process final
{
public:
   // Constructor accepting the name of the process.
   explicit Process(std::string name)
       : name_{std::move(name)}
   {
   }

   // Lets a process perform its work for the duration of a time slice.
   void doWorkDuringTimeSlice()
   {
      println("Process {} performing work during time slice.", name_);
      // Actual implementation omitted.
   }

   // Needed for the RoundRobin::remove() member function to work.
   bool operator==(const Process &) const = default; // = default since C++20.
   // Pre-C++20:
   //bool operator==(const Process& rhs) const
   //{
   //	return name_ = rhs.name_;
   //}

private:
   std::string name_;
};