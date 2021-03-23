#include <windows.h>
#include <iostream.h>

// процедура завершения ввода-вывода
VOID  CALLBACK completion_routine(
    DWORD  dwErrorCode,                // код возврата
    DWORD  dwNumberOfBytesTransferred, // количество переданных байтов
    LPOVERLAPPED  lpOverlapped         // асинхронная передача данных
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
  HANDLE  hFile;     // дескриптор файла
  OVERLAPPED  ovl;   // структура управления асинхронным доступом к файлу

  // инициализируем структуру OVERLAPPED
  ovl.Offset = 0;      // младшая часть смещения равна 0
  ovl.OffsetHigh = 0;  // старшая часть смещения равна 0

  // открываем файл для чтения
  hFile = CreateFile(
    "C:\\demo_file.dat",   // имя файла
    GENERIC_READ,          // чтение из файла
    FILE_SHARE_READ,       // совместный доступ к файлу
    NULL,                  // защиты нет
    OPEN_EXISTING,         // открываем существующий файл
    FILE_FLAG_OVERLAPPED,  // асинхронный ввод
    NULL                   // шаблона нет
  );
  // проверяем на успешное открытие
  if (hFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Create file failed." << endl
      << "The last error code: " << GetLastError() << endl;

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // читаем данные из файла
  for (;;)
  {
    DWORD  dwRet;
    int    n;

    // читаем одну запись
    if (!ReadFileEx(
        hFile,       // дескриптор файла
        &n,          // адрес буфера, куда читаем данные
        sizeof(n),   // количество читаемых байтов
        &ovl,        // чтение асинхронное
        completion_routine   // процедура завершения чтения
      ))
    {
      switch(dwRet = GetLastError())
      {
      case ERROR_IO_PENDING:
        cout << "Read file pending." << endl;
        break;
      case ERROR_HANDLE_EOF:
        cout << endl << "End of the file." << endl;
        cout << "The file is read." << endl;
        // закрываем дескриптор файла
        CloseHandle(hFile);

        return 0;
      default:
        cout << "Read file failed." << endl
          << "The last error code: " << dwRet << endl;

        // закрываем дескриптор файла
        CloseHandle(hFile);

        return 0;
      }
    }
    // ждем, пока сработает асинхронная процедура завершения чтения
    SleepEx(INFINITE, TRUE);
    // печатаем число
    cout << n << endl;
    // увеличивает смещение в файле
    ovl.Offset += sizeof(n);
  }
}