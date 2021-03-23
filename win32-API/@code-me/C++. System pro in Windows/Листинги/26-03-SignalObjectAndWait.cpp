#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

HANDLE  hSignal;   // дескриптор события, о котором сигнализируем
HANDLE  hWait;     // дескриптор события, которое ждем
HANDLE  hThread;   // дескриптор потока
DWORD  IDThread;   // идентификатор потока
DWORD  dwRet;      // возвращаемое значение при установке асинхронной процедуры

// процедура, которая вызывается асинхронно
void CALLBACK a_proc(DWORD p)
{
  int n;
  DWORD *ptr = (DWORD*)p;

  cout << "The asynchronous procedure is called." << endl;
  // ждем ввода целого числа
  cout << "Input integer: ";
  cin >> n;
  // увеличиваем счетчик
  *ptr += n;

  cout << "The asynchronous procedure is returned." << endl;
}

// поток, в очередь которого включается асинхронная процедура
DWORD WINAPI add(LPVOID ptr)
{
  DWORD  dwRet;    // код возврата из функции ожидания

  // распечатываем начальное значение счетчика
  cout << "Initial count = " << *(DWORD*)ptr << endl;
  // ждем timeout, или наступление события, 
  // или завершение асинхронной процедуры
  dwRet = SignalObjectAndWait(hSignal, hWait, 10, TRUE);
  switch (dwRet)
  {
  case WAIT_OBJECT_0:
    cout << "The event is signaled." << endl;
    break;
  case WAIT_IO_COMPLETION:
    cout << "The asynchronous procedure is done." << endl;
    break;
  case WAIT_TIMEOUT:
    cout << "Time out." << endl;
    break;
  default:
    cout << "Another case." << endl;
    break;
  }
  // распечатываем конечное значение счетчика
  cout << "Final count = " << *(DWORD*)ptr << endl;

  return 0;
}

// главный поток
int main()
{
  char c;
  DWORD  count = 10;

  // спрашиваем, что установить: событие или асинхронную процедуру
  cout << "Input: " << endl << "\te - to set event" << endl
    << "\ta - to set asynchronous procedure" << endl
    << "\tanother char - timeout" << endl
    << "->";
  cin >> c;

  // запускаем поток
  hThread = CreateThread(NULL, 0, add, &count, 0, &IDThread);
  if (hThread == NULL)
    return GetLastError();

  // создаем события с автоматическим сбросом
  hSignal = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hSignal == NULL)
    return GetLastError();
  hWait = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hWait == NULL)
    return GetLastError();

  // ждем сигнала
  WaitForSingleObject(hSignal, INFINITE);
  // запрашиваем вариант работы программы
  switch (c)
  {
  case 'e':
    // устанавливаем событие
    SetEvent(hWait);
    break;
  case 'a':
    // устанавливаем асинхронную процедуру для потока 
    dwRet = QueueUserAPC(a_proc, hThread, (DWORD) &count);
    if (!dwRet)
    {
      cout << "Queue user APC failed:" << dwRet << endl;
      return 0;
    }
    break;
  default:
    break;
  }

  // ждем, пока поток add закончит работу
  WaitForSingleObject(hThread, INFINITE);
  // закрываем дескриптор потока
  CloseHandle(hThread);

  return 0;
}