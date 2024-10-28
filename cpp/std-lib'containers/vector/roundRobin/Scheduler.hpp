#pragma once

#include <iostream>
#include <vector>
#include "Process.hpp"
#include "RoundRobin.hpp"

/**
 * Basic round-robin based process scheduler.
 */
class Scheduler final
{
public:
   // Constructor takes a vector of processes.
   explicit Scheduler(const std::vector<Process> &processes)
   {
      // Add the processes.
      for (auto &process: processes)
      {
         processes_.add(process);
      }
   }

   // Selects the next process using a round-robin scheduling algorithm
   // and allows it to perform some work during this time slice.
   void scheduleTimeSlice()
   {
      try
      {
         processes_.getNext().doWorkDuringTimeSlice();
      }
      catch (const std::out_of_range &)
      {
         println(std::cerr, "No more processes to schedule.");
      }
   }

   // Removes the given process from the list of processes.
   void removeProcess(const Process &process)
   {
      processes_.remove(process);
   }

private:
   RoundRobin<Process> processes_;
};
