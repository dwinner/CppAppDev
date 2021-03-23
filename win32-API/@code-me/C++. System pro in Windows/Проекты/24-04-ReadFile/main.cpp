#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;

  // открываем файл для чтения
  hFile = CreateFile(
    "C:\\demo_file.dat",     // имя файла
    GENERIC_READ,            // чтение из файла
    0,                       // монопольный доступ к файлу
    NULL,                    // защиты нет 
    OPEN_EXISTING,           // открываем существующий файл
    FILE_ATTRIBUTE_NORMAL,   // обычный файл
    NULL        // шаблона нет
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
    DWORD  dwBytesRead;
    int    n;
    
    // читаем одну запись
    if (!ReadFile(
        hFile,               // дескриптор файла
        &n,                  // адрес буфера, куда читаем данные
        sizeof(n),           // количество читаемых байтов
        &dwBytesRead,        // количество прочитанных байтов
        (LPOVERLAPPED)NULL   // чтение синхронное
      ))
    {
      cerr << "Read file failed." << endl
        << "The last error code: " << GetLastError() << endl;
      CloseHandle(hFile);
      cout << "Press any key to finish.";
      cin.get();
      return 0;
    }
    // проверяем на конец файла
    if (dwBytesRead == 0)
      // если да, то выходим из цикла
      break;
    else
      // иначе выводим запись на консоль
      cout << n << ' ';
  }

  cout << endl;

  // закрываем дескриптор файла 
  CloseHandle(hFile);

  cout << "The file is opened and read." << endl;

  return 0;
}