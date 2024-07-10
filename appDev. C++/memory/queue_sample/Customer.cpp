#include <cstdlib>
#include "Customer.h"

using namespace std;

void Customer::set(long when)
{
   processtime = std::rand() % 3 + 1;
   arrive = when;
}
