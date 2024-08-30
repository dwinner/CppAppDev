#ifndef LEAKY_SIMPLE_H
#define LEAKY_SIMPLE_H

class Simple
{
public:
   Simple()
   {
      _intPtr = new int{};
   }

   ~Simple()
   {
      delete _intPtr;
   }

   void setValue(int value)
   {
      *_intPtr = value;
   }

private:
   int *_intPtr;
};

#endif //LEAKY_SIMPLE_H
