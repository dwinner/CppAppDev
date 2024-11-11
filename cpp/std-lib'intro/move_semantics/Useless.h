#ifndef MOVE_SEMANTICS_USELESS_H
#define MOVE_SEMANTICS_USELESS_H


class Useless
{
public:
   Useless();

   explicit Useless(int k);

   Useless(int k, char ch);

   Useless(const Useless &f); // regular copy constructor

   Useless(Useless &&f) noexcept;  // move constructor

   ~Useless();

   Useless operator+(const Useless &f) const;

   Useless &operator=(const Useless &f); // copy assignment

   Useless &operator=(Useless &&f) noexcept;      // move assignment

   void ShowData() const;

private:
   int n;          // number of elements
   char *pc;      // pointer to data
   static int ct;  // number of objects
};


#endif //MOVE_SEMANTICS_USELESS_H
