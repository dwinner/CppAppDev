#include <iostream>
#include "Waiter.h"

using namespace std;

// Waiter methods
void Waiter::set()
{
   cout << "Enter waiter's name: ";
   Worker::get();
   get();
}

void Waiter::show() const
{
   cout << "Category: waiter\n";
   Worker::data();
   data();
}

// protected methods
void Waiter::data() const
{
   cout << "Panache rating: " << panache_ << endl;
}

void Waiter::get()
{
   cout << "Enter waiter's panache rating: ";
   cin >> panache_;
   while (cin.get() != '\n')
   {
   }
}
