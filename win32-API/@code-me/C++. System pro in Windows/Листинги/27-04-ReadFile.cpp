#include <windows.h>
#include <iostream.h>


int main()
{
  HANDLE  hFile;     // дескриптор файла
  HANDLE  hEndRead;  // дескриптор события
  OVERLAPPED  ovl;   // структура управления асинхронным доступом к файлу

  // создаем события с автоматическим сбросом
  hEndRead = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hEndRead == NULL)
    return GetLastError();
    
  // инициализируем структуру OVERLAPPED
  ovl.Offset = 0;         // младшая часть смещения равна 0
  ovl.OffsetHigh = 0;      // старшая часть смещения равна 0
  ovl.hEvent = hEndRead;   // событие для оповещения завершения чтения

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

    CloseHandle(hEndRead);

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // читаем данные из файла
  for (;;)
  {
    DWORD  dwBytesRead;
    DWORD  dwRet;
    int    n;

    // читаем одну запись
    if (!ReadFile(
        hFile,           // дескриптор файла
        &n,              // адрес буфера, куда читаем данные
        sizeof(n),       // количество читаемых байтов
        &dwBytesRead,    // количество прочитанных байтов
        &ovl             // чтение асинхронное
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

        // закрываем дескрипторы
        CloseHandle(hFile);
        CloseHandle(hEndRead);

        return 1;
      default:
        cout << "Read file failed." << endl
          << "The last error code: " << dwRet << endl;

        // закрываем дескрипторы
        CloseHandle(hFile);
        CloseHandle(hEndRead);

        return 0;
      }
    }
    // ждем, пока завершится асинхронная операция чтения
    WaitForSingleObject(hEndRead, INFINITE);
    // печатаем число
    cout << n << ' ';
    // увеличивает смещение в файле
    ovl.Offset += sizeof(n);
  }
}