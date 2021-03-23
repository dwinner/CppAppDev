#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

HANDLE  hCompletionPort;   // порт завершения

DWORD WINAPI thread(LPVOID)
{
  int  i = 0;      // количество полученных пакетов
  DWORD  dwNumberOfBytes;      // количество переданных байтов
  ULONG    ulCompletionKey;    // ключ файла
  LPOVERLAPPED  lpOverlapped;  // указатель на структуру типа OVERLAPPED

  cout << "The thread is started." << endl;

  // подключаем поток к порту
  while (GetQueuedCompletionStatus(
    hCompletionPort,   // дескриптор порта завершения
    &dwNumberOfBytes,  // количество переданных байтов
    &ulCompletionKey,  // ключ файла
    &lpOverlapped,     // указатель на структуру типа OVERLAPPED
    INFINITE))         // бесконечное ожидание
//  {---тело цикла---
    // проверяем пакет на завершение вывода
    if (ulCompletionKey == 0)
    {
      cout << endl << "The thread is finished." << endl;
      break;
    }
    else
      cout << "\tPacket: " << ++i << endl
        << "Number of bytes: " << dwNumberOfBytes << endl
        << "Completion key: " << ulCompletionKey << endl;
//  }---конец тела цикла---

  return 0;
}

int main()
{
  HANDLE  hFile;     // дескриптор файла
  OVERLAPPED  ovl;   // структура управления асинхронным доступом к файлу
  ULONG    ulKey;    // ключ файла
  HANDLE  hThread;   // массив для дескрипторов потоков
  DWORD  dwThreadID; // массив для идентификаторов потоков 

  // инициализируем структуру OVERLAPPED
  ovl.Offset = 0;      // младшая часть смещения равна 0
  ovl.OffsetHigh = 0;  // старшая часть смещения равна 0
  ovl.hEvent = 0;      // события нет

  // запрашиваем ключ файла
  cout << "Input a number for file key (not zero): ";
  cin >> ulKey;
  if (ulKey == 0)
  {
    cout << "The file key can't be equal to zero." << endl
      << "Press any key to exit." << endl;

    return 0;
  }

  // создаем файл для записи данных
  hFile = CreateFile(
    "C:\\demo_file.dat",   // имя файла
    GENERIC_WRITE,         // запись в файл
    FILE_SHARE_WRITE,      // совместный доступ к файлу
    NULL,                  // защиты нет
    OPEN_ALWAYS,           // открываем или создаем новый файл
    FILE_FLAG_OVERLAPPED,  // асинхронный доступ к файлу
    NULL                   // шаблона нет
  );
  // проверяем на успешное создание
  if (hFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Create file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish." << endl;

    cin.get();
    return 0;
  }

  // создаем порт завершения и подключаем к нему файл
  hCompletionPort = CreateIoCompletionPort(
      hFile,   // дескриптор файла
      NULL,    // новый порт
      ulKey,   // ключа файла
      1        // один поток
    );

  // проверяем на успешное создание
  if (hCompletionPort == NULL)
  {
    cerr << "Create completion port failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish." << endl;

    cin.get();
    return 0;
  }

  // запускаем поток
  hThread = CreateThread(NULL, 0, thread, NULL, 0, &dwThreadID);

  // пишем данные в файл
  for (int i = 0; i < 10; ++i)
  {
    DWORD  dwBytesWrite;
    DWORD  dwRet;

    if (!WriteFile(
        hFile,       // дескриптор файла
        &i,          // адрес буфера, откуда идет запись
        sizeof(i),   // количество записываемых байтов
        &dwBytesWrite,   // количество записанных байтов
        &ovl         // запись асинхронная
      ))
    {
      dwRet = GetLastError();
      if (dwRet == ERROR_IO_PENDING)
        cout << "Write file pending." << endl;
      else
      {
        cout << "Write file failed." << endl
          << "The last error code: " << dwRet << endl;
        return 0;
      }
    }
    // ждем, пока завершится асинхронная операция записи
    WaitForSingleObject(hFile, INFINITE);
    // увеличивает смещение в файле
    ovl.Offset += sizeof(i);
  }

  // посылаем пакет с командой на завершение потока
  PostQueuedCompletionStatus(
    hCompletionPort,   // дескрипор потока
    0,       // нет передачи
    0,       // ключ завершения
    NULL);   // нет структуры типа OVERLAPPED

  // ждем завершения потока
  WaitForSingleObject(hThread, INFINITE);
  // закрываем дескрипторы 
  CloseHandle(hFile);
  CloseHandle(hCompletionPort);
  CloseHandle(hThread);

  cout << "The file is written." << endl;

  return 0;
}