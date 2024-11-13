import std;

using namespace std;

template <typename T>
class Pointer final
{
public:
   [[nodiscard]] explicit Pointer(T* data);

   ~Pointer();

   // Prevent copy construction and copy assignment.
   Pointer(const Pointer& src) = delete;

   Pointer& operator=(const Pointer& rhs) = delete;

   // Allow move construction and move assignment.
   Pointer(Pointer&& src) noexcept;

   Pointer& operator=(Pointer&& rhs) noexcept;

   T& operator*() noexcept;

   const T& operator*() const noexcept;

   [[nodiscard]] T* release() noexcept;

   void reset(T* data = nullptr) noexcept;

private:
   T* data_{nullptr};
};

template <typename T>
Pointer<T>::Pointer(T* data) : data_{data}
{
}

template <typename T>
Pointer<T>::~Pointer()
{
   reset();
}

template <typename T>
Pointer<T>::Pointer(Pointer&& src) noexcept
   : data_{std::exchange(src.data_, nullptr)}
{
}

template <typename T>
Pointer<T>& Pointer<T>::operator=(Pointer&& rhs) noexcept
{
   if (this != &rhs)
   {
      reset();
      data_ = std::exchange(rhs.data_, nullptr);
   }

   return *this;
}

template <typename T>
T& Pointer<T>::operator*() noexcept
{
   return *data_;
}

template <typename T>
const T& Pointer<T>::operator*() const noexcept
{
   return *data_;
}

template <typename T>
T* Pointer<T>::release() noexcept
{
   return std::exchange(data_, nullptr);
}

template <typename T>
void Pointer<T>::reset(T* data /*= nullptr*/) noexcept
{
   if (data_)
   {
      delete data_;
   }

   data_ = data;
}

int main()
{
   Pointer pointer{new int{42}};
   println("{}", *pointer);

   Pointer pointer2{std::move(pointer)};
   println("{}", *pointer2);

   Pointer<int> pointer3{nullptr};
   pointer3 = std::move(pointer2);
   println("{}", *pointer3);

   pointer3 = std::move(pointer3);
   println("{}", *pointer3);
}
