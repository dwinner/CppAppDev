import std;

using namespace std;
using namespace std::chrono;

atomic<bool> IsBeepingEnabled{true};

void Beeper(const duration<int> delay)
{
   while (true)
   {
      if (IsBeepingEnabled)
      {
         print("\a");
      }

      this_thread::sleep_for(delay);
   }
}

int main()
{
   jthread beepThread{Beeper, 3s};

   while (true)
   {
      print("Press enter to pause beeping");
      cin.ignore();
      IsBeepingEnabled = !IsBeepingEnabled;

      print("Press enter to resume beeping");
      cin.ignore();
      IsBeepingEnabled = !IsBeepingEnabled;
   }
}
