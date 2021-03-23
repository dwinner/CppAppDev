#include <windows.h>
#include <iostream.h>

int main()
{
  char c;    // служебный символ
  char lpszCommandLine[80];            // командная строка
  char send[] = "This is a message.";  // строка для пересылки
  char buffer[80];                     // буфер для ответа
  LPVOID  v = (LPVOID)0x00880000;      // указатель на область памяти

  HANDLE  hWrite, hRead;     // события для синхронизации
                             // записи-чтения в виртуальную память
  char  WriteEvent[] = "WriteEvent";
  char  ReadEvent[] = "ReadEvent";

  // создаем события
  hWrite = CreateEvent(NULL, FALSE, FALSE, WriteEvent);
  hRead = CreateEvent(NULL, FALSE, FALSE, ReadEvent);


  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  // формируем командную строку
  wsprintf(lpszCommandLine, "C:\\ConsoleProcess.exe %d", (int)v);
  // создаем новый консольный процесс
  if (!CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
  {
    cout << "Create process failed." << endl;
    return GetLastError();
  }

  // распределяем виртуальную память в этом процессе
  v = VirtualAllocEx(
      pi.hProcess,
      v, 
      sizeof(send), 
      MEM_RESERVE | MEM_COMMIT, 
      PAGE_READWRITE);
  if(!v)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  // записываем в виртуальную память сообщение
  WriteProcessMemory(pi.hProcess, v, (void*)send, sizeof(send), NULL);
  // оповещаем о записи
  SetEvent(hWrite);
  // ждем сигнала на чтение
  WaitForSingleObject(hRead, INFINITE);
  // читаем ответ
  ReadProcessMemory(pi.hProcess, v, (void*)buffer, sizeof(buffer), NULL);
  // выводим ответ
  cout << buffer << endl;

  // освобождаем виртуальную память
  if (!VirtualFreeEx(pi.hProcess, v, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}