import std;

using namespace std;
using namespace std::chrono;

void Beeper(duration<int> delay)
{
   while (true)
   {
      print("\a");
      this_thread::sleep_for(delay);
   }
}

int main()
{
   jthread beepThread{Beeper, 3s};
}
