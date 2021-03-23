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
    // если блок __try закончился нормально
    if (!AbnormalTermination())
    {
      // то освобождаем память
      delete p;
      cout << "The memory is free." << endl;
    }
    else
      // иначе нечего освобождать
      cout << "The memory was not allocated." << endl;
  }

  return 0;
}