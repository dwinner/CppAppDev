#include "Example.h"
#include <iostream>

using namespace std;

Example::Example()
{
   feet = 0;
   inches = 0;
}

Example::Example(int ft)
{
   feet = ft;
   inches = 12 * feet;
}

Example::~Example() = default;

void Example::show_in() const
{
   cout << inches << " inches\n";
}

void Example::show_ft() const
{
   cout << feet << " feet\n";
}

void Example::use_ptr() const
{
   Example yard(3);
   int Example::*pt;
   pt = &Example::inches;
   cout << "Set pt to &Example::inches:\n";
   cout << "this->pt: " << this->*pt << endl;
   cout << "yard.*pt: " << yard.*pt << endl;
   pt = &Example::feet;
   cout << "Set pt to &Example::feet:\n";
   cout << "this->pt: " << this->*pt << endl;
   cout << "yard.*pt: " << yard.*pt << endl;
   void (Example::*pf)() const;
   pf = &Example::show_in;
   cout << "Set pf to &Example::show_in:\n";
   cout << "Using (this->*pf)(): ";
   (this->*pf)();
   cout << "Using (yard.*pf)(): ";
   (yard.*pf)();
}
