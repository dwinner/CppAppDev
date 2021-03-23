#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;     // дескриптор файла
  long    n;         // для номера записи
  long    p;         // для указателя позиции
  DWORD dwBytesRead; // количество прочитанных байт
  int     m;         // прочитанное число
  
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

  // вводим номер нужной записи
  cout << "Input a number from 0 to 9: ";
  cin >> n;
  // сдвигаем указатель позиции файла
  p = SetFilePointer(hFile, n * sizeof(int), NULL, FILE_BEGIN);
  if(p == -1)
  {
    cerr << "Set file pointer failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  // выводим на консоль значение указателя позиции файла
  cout << "File pointer: " << p << endl;
  // читаем данные из файла
  if (!ReadFile(
      hFile,             // дескриптор файла
      &m,                // адрес буфера, куда читаем данные
      sizeof(m),         // количество читаемых байтов
      &dwBytesRead,      // количество прочитанных байтов
      (LPOVERLAPPED)NULL // чтение синхронное
    ))
  {
    cerr << "Read file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  // выводим прочитанное число на консоль
  cout << "The read number: " << m << endl;
  // закрываем дескриптор файла 
  CloseHandle(hFile);

  return 0;
}