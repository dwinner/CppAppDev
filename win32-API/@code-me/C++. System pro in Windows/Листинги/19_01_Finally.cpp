#include <windows.h>
#include <iostream.h>

int main()
{
  char c;
  int  *p = NULL;  // пустой указатель на целое число

  // введите 'y', чтобы распределить память под целое число
  cout << "Input 'y' to allocate memory: ";
  // вводим символ
  cin >> c;
  // если ввели 'y', то память распределяется, иначе - не распределяется
  if (c == 'y')
    p = new int;

  __try
  {
    *p = 10;  // может быть исключение, если память не распределена
  }
  __finally
  {
    // в любом случае пробуем освободить память
    delete p;
    // выводим сообщение
    cout << "The finally block finished." << endl;
  }

  return 0;
}