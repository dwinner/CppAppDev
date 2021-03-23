#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;
  LARGE_INTEGER  liFileSize;  // размер файла

  // открываем файл для чтения
  hFile = CreateFile(
    "C:\\demo_file.dat",   // имя файла
    GENERIC_READ,          // чтение из файла
    0,                     // монопольный доступ к файлу
    NULL,                  // защиты нет 
    OPEN_EXISTING,         // открываем существующий файл
    FILE_ATTRIBUTE_NORMAL, // обычный файл
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
  
  // определяем размер файла
  if (!GetFileSizeEx(hFile, &liFileSize))
    cerr << "Get file size failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // выводим размер файла
  cout << "File size: " << liFileSize.LowPart << endl;
  // закрываем дескриптор файла 
  CloseHandle(hFile);

  return 0;
}