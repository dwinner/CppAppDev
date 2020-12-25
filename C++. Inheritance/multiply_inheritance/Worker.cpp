#include <iostream>
#include "Worker.h"

using std::cout;
using std::cin;
using std::endl;

Worker::~Worker()
{
}

// protected methods
void Worker::data() const
{
   cout << "Name: " << fullName_ << endl;
   cout << "Employee ID: " << id_ << endl;
}

void Worker::get()
{
   getline(cin, fullName_);
   cout << "Enter worker's ID: ";
   cin >> id_;
   while (cin.get() != '\n')
   {
   }
}
