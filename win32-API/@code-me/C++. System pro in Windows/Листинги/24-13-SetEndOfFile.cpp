#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;       // дескриптор файла
  DWORD   dwFileSize;  // размер файла
  long    p;           // указатель позиции
  
  // открываем файл для чтения
  hFile = CreateFile(
    "C:\\demo_file.dat",   // имя файла
    GENERIC_WRITE,         // запись в файл
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
  // выводим на консоль размер файла
  cout << "Old file size: " << dwFileSize << endl;
  // уменьшаем размер файла вдвое
  dwFileSize /= 2;
  // сдвигаем указатель позиции файла
  p = SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
  if(p == -1)
  {
    cerr << "Set file pointer failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // устанавливаем новый размер файла
  if (!SetEndOfFile(hFile))
  {
    cerr << "Set end of file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // определяем новый размер файла
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
  // выводим на консоль размер файла
  cout << "New file size: " << dwFileSize << endl;
  // закрываем дескриптор файла 
  CloseHandle(hFile);

  return 0;
}