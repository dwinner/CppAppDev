import std;

using namespace std;
using namespace std::chrono;

void beeper(const stop_token& token, const duration<int> delay)
{
   while (!token.stop_requested())
   {
      print("\a");
      this_thread::sleep_for(delay);
   }
}

int main()
{
   jthread beepThread{beeper, 3s};

   print("Press enter to stop beeping");
   cin.ignore();

   beepThread.request_stop();
}
