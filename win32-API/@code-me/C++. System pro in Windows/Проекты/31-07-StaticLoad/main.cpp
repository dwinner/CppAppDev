#include <windows.h>
#include <iostream.h>

extern "C" __declspec(dllimport) int count;
extern "C" __declspec(dllimport) int Add(int n);
extern "C" __declspec(dllimport) int Sub(int n);

int main()
{
  // выводим начальное значение переменной count
  cout << "Initial count = " << count << endl;
  // измен€ем значение счетчика
  cout << "count = " << Add(20) << endl;
  cout << "count = " << Sub(15) << endl;

  // выходим из программы
  cout << "Press any key to exit.";
  cin.get();

  return 0;
}