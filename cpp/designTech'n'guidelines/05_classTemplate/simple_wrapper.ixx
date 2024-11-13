export module simple_wrapper;

export template <typename T>
class SimpleWrapper
{
public:
   explicit SimpleWrapper(T& object) : obj_{object}
   {
   }

   T& get() const
   {
      return obj_;
   }

private:
   T& obj_;
};
