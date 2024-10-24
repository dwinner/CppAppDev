#include "Processor.hpp"

Processor::Processor(const std::function<int(int)> &delegate) :
    delegate_(delegate)
{}

int Processor::operator()(int inputValue) const
{
   return delegate_(inputValue);
}

const std::function<int(int)> &Processor::getDelegate() const
{
   return delegate_;
}

void Processor::setDelegate(const std::function<int(int)> &delegate)
{
   delegate_ = delegate;
}
