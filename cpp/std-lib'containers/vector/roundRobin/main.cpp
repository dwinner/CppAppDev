#include <vector>
#include "Process.hpp"
#include "Scheduler.hpp"

using namespace std;

int main()
{
   vector processes{Process{"1"}, Process{"2"}, Process{"3"}};
   Scheduler scheduler{processes};
   for (size_t i{0}; i < 4; ++i)
   {
      scheduler.scheduleTimeSlice();
   }

   scheduler.removeProcess(processes[1]);
   println("Removed second process");

   for (size_t i{0}; i < 4; ++i)
   {
      scheduler.scheduleTimeSlice();
   }
}
