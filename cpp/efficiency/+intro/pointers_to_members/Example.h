#ifndef POINTERS_TO_MEMBERS_EXAMPLE_H
#define POINTERS_TO_MEMBERS_EXAMPLE_H


class Example
{
public:
   Example();

   explicit Example(int ft);

   ~Example();

   void show_in() const;

   void show_ft() const;

   void use_ptr() const;

private:
   int feet;
   int inches;
};


#endif //POINTERS_TO_MEMBERS_EXAMPLE_H
