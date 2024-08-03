export module adder;

import std;

export class Adder
{
public:
   Adder();

   virtual ~Adder();

   int add(int a, int b) const;

private:
   class Impl;
   std::unique_ptr<Impl> impl_;

public:
   Impl* getImplementation()
   {
      return impl_.get();
   }
};

module :private;

class Adder::Impl
{
public:
   ~Impl()
   {
      std::println("Destructor of Adder::Impl");
   }

   int add(int a, int b) const
   {
      return a + b;
   }
};

Adder::Adder()
   : impl_{std::make_unique<Impl>()}
{
}

Adder::~Adder()
{
}

int Adder::add(int a, int b) const
{
   return impl_->add(a, b);
}
