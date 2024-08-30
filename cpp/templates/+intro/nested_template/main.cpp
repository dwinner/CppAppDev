/**
 * Template members
 */

#include <iostream>

using std::cout;
using std::endl;

template<typename T>
class beta
{
public:
   beta(T t, int i)
      : q(t),
        n(i)
   {
   }

   // template method
   template<typename U>
   U blab(U u, T t)
   {
      return (n.Value() + q.Value()) * u / t;
   }

   void Show() const
   {
      q.show();
      n.show();
   }

private:
   // nested template class member
   template<typename V>
   class hold
   {
   public:
      hold(V v = 0)
         : val(v)
      {
      }

      void show() const
      {
         cout << val << endl;
      }

      V Value() const
      {
         return val;
      }

   private:
      V val;
   };

   hold<T> q;             // template object
   hold<int> n;           // template object
};

int main()
{
   beta<double> guy(3.5, 3);
   cout << "T was set to double\n";
   guy.Show();
   cout << "V was set to T, which is double, then V was set to int\n";
   cout << guy.blab(10, 2.3) << endl;
   cout << "U was set to int\n";
   cout << guy.blab(10.0, 2.3) << endl;
   cout << "U was set to double\n";
   cout << "Done\n";

   return 0;
}
