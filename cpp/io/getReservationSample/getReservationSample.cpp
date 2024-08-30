import std;

using namespace std;

void get_reservation_data()
{
   string guestName;
   int partySize;
   print("Name and number of guests: ");
   cin >> guestName >> partySize;
   println("Thank you, {}.", guestName);
   if (partySize > 10)
   {
      println("An extra gratuity will apply.");
   }
}

int main()
{
   get_reservation_data();
}
