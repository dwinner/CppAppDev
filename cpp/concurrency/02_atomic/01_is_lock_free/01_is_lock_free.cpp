import std;

using namespace std;

struct Foo
{
   int array[123];
};

struct Bar
{
   int intVal;
};

int main()
{
   atomic<Foo> f;
   println("{} {}", is_trivially_copyable_v<Foo>, f.is_lock_free());

   atomic<Bar> b;
   println("{} {}", is_trivially_copyable_v<Bar>, b.is_lock_free());
}
