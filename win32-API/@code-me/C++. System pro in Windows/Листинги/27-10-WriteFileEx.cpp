#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

// процедура завершения ввода-вывода
VOID  CALLBACK completion_routine(
  DWORD  dwErrorCode,                 // код возврата
  DWORD  dwNumberOfBytesTransferred,  // количество переданных байтов
  LPOVERLAPPED  lpOverlapped          // асинхронная передача данных
    )
{
  cout << "Completion routine parameters: " << endl
    << "\tErrorCode: " << dwErrorCode << endl
    << "\tNumber of bytes transferred: " << dwNumberOfBytesTransferred << endl
    << "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' '
    << (*lpOverlapped).Offset << endl;
}

// главная программа
int main()
{
  HANDLE  hFile;    // дескриптор файла
  OVERLAPPED  ovl;  // структура управления асинхронным доступом к файлу

  // инициализируем структуру OVERLAPPED
  ovl.Offset = 0;      // младшая часть смещения равна 0
  ovl.OffsetHigh = 0;  // старшая часть смещения равна 0

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

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  
  // пишем данные в файл
  for (int i = 0; i < 10; ++i)
  {
    DWORD  dwRet;

    if (!WriteFileEx(
        hFile,       // дескриптор файла
        &i,          // адрес буфера, откуда идет запись
        sizeof(i),   // количество записываемых байтов
        &ovl,        // запись асинхронная
        completion_routine // процедура завершения
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
    // ждем, пока сработает асинхронная процедура 
    // завершения операции вывода
    SleepEx(INFINITE, TRUE);
    // увеличивает смещение в файле
    ovl.Offset += sizeof(i);
  }
  // закрываем дескриптор файла 
  CloseHandle(hFile);

  cout << "The file is written." << endl;

  return 0;
}