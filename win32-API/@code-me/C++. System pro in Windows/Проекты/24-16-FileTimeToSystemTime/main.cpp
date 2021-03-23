#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;
  BY_HANDLE_FILE_INFORMATION  bhfi;  // информация о файле
  SYSTEMTIME  st;    // системное время

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
  // переводим время создания файла в системное время
  if (!FileTimeToSystemTime(&(bhfi.ftCreationTime), &st))
  {
    cerr << "File time to system time failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // распечатываем системное время
  cout << "File creation time in system format: " << endl
    << "\tYear: " << st.wYear << endl
    << "\tMonth: " << st.wMonth << endl
    << "\tDay of week: " << st.wDayOfWeek << endl
    << "\tDay: " << st.wDay << endl
    << "\tHour: " << st.wHour << endl
    << "\tMinute: " << st.wMinute << endl
    << "\tSecond: " << st.wSecond << endl
    << "\tMilliseconds: " << st.wMilliseconds << endl;

  // закрываем дескриптор файла 
  CloseHandle(hFile);

  return 0;
}