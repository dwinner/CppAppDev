#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;
  BY_HANDLE_FILE_INFORMATION  bhfi;  // информация о файле

  // открываем файл для чтения
  hFile = CreateFile(
    "C:\\demo_file.dat",   // имя файла
    0,                     // получение информации о файле
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
  // получаем информацию о файле
  if (!GetFileInformationByHandle(hFile, &bhfi))
  {
    cerr << "Get file information by handle failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // распечатываем информацию о файле
  cout << "File attributes: " << bhfi.dwFileAttributes << endl
    << "Creation time: high date: " 
      << bhfi.ftCreationTime.dwHighDateTime << endl
    << "Creation time: low date: " 
      << bhfi.ftCreationTime.dwLowDateTime << endl
    << "Last access time: high date: " 
      << bhfi.ftLastAccessTime.dwHighDateTime << endl
    << "Last access time: low date: " 
      << bhfi.ftLastAccessTime.dwLowDateTime << endl
    << "Last write time: high date: " 
      << bhfi.ftLastWriteTime.dwHighDateTime << endl
    << "Last write time: low date: " 
      << bhfi.ftLastWriteTime.dwLowDateTime << endl
    << "Volume serial number: " << bhfi.dwVolumeSerialNumber << endl
    << "File size high: " << bhfi.nFileSizeHigh << endl
    << "File size low: " << bhfi.nFileSizeLow << endl
    << "Number of links: " << bhfi.nNumberOfLinks << endl
    << "File index high: " << bhfi.nFileIndexHigh << endl
    << "File index low: " << bhfi.nFileIndexLow << endl;

  // закрываем дескриптор файла 
  CloseHandle(hFile);

  return 0;
}