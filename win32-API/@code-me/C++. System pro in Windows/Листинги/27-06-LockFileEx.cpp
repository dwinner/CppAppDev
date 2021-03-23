#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;     // дескриптор файла
  HANDLE  hEndLock;  // дескриптор события
  DWORD  dwFileSize;
  DWORD  dwRet;
  OVERLAPPED  ovl;   // структура управления асинхронным доступом к файлу

  // создаем события с автоматическим сбросом
  hEndLock = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hEndLock == NULL)
    return GetLastError();
    
  // инициализируем структуру OVERLAPPED
  ovl.Offset = 0;          // младшая часть смещения равна 0
  ovl.OffsetHigh = 0;      // старшая часть смещения равна 0
  ovl.hEvent = hEndLock;   // событие для оповещения завершения блокирования

  // открываем файл для записи
  hFile = CreateFile(
    "C:\\demo_file.dat",   // имя файла
    GENERIC_WRITE,         // запись в файл
    0,                     // монопольный доступ к файлу
    NULL,                  // защиты нет
    OPEN_EXISTING,         // открываем существующий файл
    FILE_FLAG_OVERLAPPED,  // асинхронный доступ к файлу
    NULL                   // шаблона нет
  );
  // проверяем на успешное открытие
  if (hFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Create file failed." << endl
      << "The last error code: " << GetLastError() << endl;

    CloseHandle(hFile);

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  // определяем размер файла
  dwFileSize = GetFileSize(hFile, NULL);
  if (dwFileSize == -1)
  {
    cerr << "Get file size failed." << endl
      << "The last error code: " << GetLastError() << endl;

    CloseHandle(hFile);

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  // блокируем файл
  if (!LockFileEx(
      hFile,         // дескриптор файла
      LOCKFILE_EXCLUSIVE_LOCK,   // монопольный доступ к файлу
      0,             // не используется
      0, dwFileSize, // длина области
      &ovl))         // асинхронная блокировка
  {
    dwRet = GetLastError();
    if (dwRet == ERROR_IO_PENDING)
      cout << "The lock file is pending." << endl;
    else
    {
      cout << "Lock file failed." << endl
        << "The last error code: " << dwRet << endl;

      CloseHandle(hFile);
      CloseHandle(hEndLock);

      return 0;
    }
  }

  // ждем, пока завершится асинхронная операция записи
  WaitForSingleObject(hEndLock, INFINITE);

  cout << "Now the file is locked." << endl
    << "Press any key to continue." << endl;
  cin.get();

  // разблокируем файл
  if (!UnlockFileEx(hFile, 0, 0, dwFileSize, &ovl))
  {
    cerr << "Unlock file failed." << endl
      << "The last error code: " << GetLastError() << endl;

    CloseHandle(hFile);
    CloseHandle(hEndLock);

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  cout << "Now the file is unlocked." << endl
    << "Press any key to continue." << endl;
  cin.get();

  // закрываем дескрипторы 
  CloseHandle(hFile);
  CloseHandle(hEndLock);
  return 0;
}