#include <windows.h>
#include <iostream.h>

LONG new_filter(PEXCEPTION_POINTERS  pExceptionInfo)
{
  cout << "New filter-function is called." << endl;

  cout << "Exception code = " << hex 
       << pExceptionInfo->ExceptionRecord->ExceptionCode << endl;

  return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
  int *p = NULL;
  LPTOP_LEVEL_EXCEPTION_FILTER  old_filter;

  // устанавливаем новую функцию-фильтр необработанных исключений
  old_filter = 
   SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)new_filter);
  // выводим адрес старой функции-фильтра
  cout << "Old filter-function address = " << hex << old_filter << endl;
  // создаем необработанное исключение
  *p = 10;

  return 0;
}