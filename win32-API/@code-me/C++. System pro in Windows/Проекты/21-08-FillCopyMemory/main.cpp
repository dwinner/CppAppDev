#include <windows.h>
#include <iostream.h>

int main()
{
  BYTE *a, *b;     // указатели на блоки памяти
  const int size = 1000;   // размерность массива

  // распределяем виртуальную память
  a = (BYTE*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
  if(!a)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }
  b = (BYTE*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
  if(!b)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  // инициализируем символом X
  FillMemory(a, size, 'X');
  // копируем блок A в блок B
  CopyMemory(b, a, size);
  // распечатываем результат
  cout << "b[10] = " << b[10] << endl;

  // освобождаем виртуальную память
  if (!VirtualFree(a, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  return 0;
}