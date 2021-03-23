#include <windows.h>
#include <iostream.h>

int main()
{
  const int size = 4096;   // размер страницы
  HANDLE  hProcess;        // дескриптор процесса

  SIZE_T  min, max;  // мин. и макс. размеры рабочего множества страниц
  SIZE_T  *pMin = &min;    // указатель на минимальный размер
  SIZE_T  *pMax = &max;    // указатель на максимальный размер

  // получить дескриптор текущего процесса
  hProcess = GetCurrentProcess();
  // прочитать границы рабочего множества
  if(!GetProcessWorkingSetSize(hProcess, pMin, pMax))
  {
    cout << "Get process working set size failed." << endl;
    return GetLastError();
  }
  else
  {
    cout << "Min = " << (min/size) << endl;
    cout << "Max = " << (max/size) << endl;
  }

  // установить новые границы рабочего множества
  if(!SetProcessWorkingSetSize(hProcess, min-10, max-10))
  {
    cout << "Set process working set size failed." << endl;
    return GetLastError();
  }

  // прочитать новые границы рабочего множества
  if(!GetProcessWorkingSetSize(hProcess, pMin, pMax))
  {
    cout << "Get process working set size failed." << endl;
    return GetLastError();
  }
  else
  {
    cout << "Min = " << (min/size) << endl;
    cout << "Max = " << (max/size) << endl;
  }
  return 0;
}