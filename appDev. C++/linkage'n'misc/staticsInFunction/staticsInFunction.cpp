import std;

using namespace std;

void PerformTask()
{
   static bool initialized{false};

   if (!initialized)
   {
      println("initializing");
      // Perform initialization.
      initialized = true;
   }

   // Perform the desired task.
}

int main()
{
   PerformTask();
   PerformTask();
}
