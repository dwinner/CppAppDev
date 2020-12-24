#include <iostream>
#include "SingingWaiter.h"

using namespace std;

// SingingWaiter methods
void SingingWaiter::data() const
{
   Singer::data();
   Waiter::data();
}

void SingingWaiter::get()
{
   Waiter::get();
   Singer::get();
}

void SingingWaiter::set()
{
   cout << "Enter singing waiter's name: ";
   Worker::get();
   get();
}

void SingingWaiter::show() const
{
   cout << "Category: singing waiter\n";
   Worker::data();
   data();
}
