#include <iostream>
#include "Useless.h"

using namespace std;

int Useless::ct = 0;

Useless::Useless()
{
   ++ct;
   n = 0;
   pc = nullptr;
}

Useless::Useless(int k) : n(k)
{
   ++ct;
   pc = new char[n];
}

Useless::Useless(int k, char ch) : n(k)
{
   ++ct;
   pc = new char[n];
   for (int i = 0; i < n; i++)
   {
      pc[i] = ch;
   }
}

Useless::Useless(const Useless &f) : n(f.n)
{
   ++ct;
   pc = new char[n];
   for (int i = 0; i < n; i++)
   {
      pc[i] = f.pc[i];
   }
}

Useless::Useless(Useless &&f) noexcept: n(f.n)
{
   ++ct;
   pc = f.pc;       // steal address
   f.pc = nullptr;  // give old object nothing in return
   f.n = 0;
}

Useless::~Useless()
{
   delete[] pc;
}

Useless &Useless::operator=(const Useless &f)  // copy assignment
{
   std::cout << "copy assignment operator called:\n";
   if (this == &f)
   {
      return *this;
   }

   delete[] pc;
   n = f.n;
   pc = new char[n];
   for (int i = 0; i < n; i++)
   {
      pc[i] = f.pc[i];
   }

   return *this;
}

Useless &Useless::operator=(Useless &&f) noexcept // move assignment
{
   std::cout << "move assignment operator called:\n";
   if (this == &f)
   {
      return *this;
   }

   delete[] pc;

   n = f.n;
   pc = f.pc;
   f.n = 0;
   f.pc = nullptr;

   return *this;
}

Useless Useless::operator+(const Useless &f) const
{
   Useless temp = Useless(n + f.n);

   for (int i = 0; i < n; i++)
   {
      temp.pc[i] = pc[i];
   }

   for (int i = n; i < temp.n; i++)
   {
      temp.pc[i] = f.pc[i - n];
   }

   return temp;
}

void Useless::ShowData() const
{
   if (n == 0)
   {
      std::cout << "(object empty)";
   }
   else
   {
      for (int i = 0; i < n; i++)
      {
         std::cout << pc[i];
      }
   }

   std::cout << std::endl;
}
