
// #define _WIN32_WINNT 0x0500  // или определить этот макрос вместо функции, если новая платформа

#include <windows.h>
#include <iostream>
using namespace std;

extern "C" WINBASEAPI BOOL WINAPI SetFilePointerEx(
    HANDLE hFile,
    LARGE_INTEGER liDistanceToMove,
    PLARGE_INTEGER lpNewFilePointer,
    DWORD dwMoveMethod
    );

int main()
{
  HANDLE  hFile;        // дескриптор файла
  int     n;            // для номера записи
  LARGE_INTEGER  p, q;  // для указателя позиции
  DWORD dwBytesRead;    // количество прочитанных байтов
  int     m;            // прочитанное число
  
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
  q.HighPart = 0;
  q.LowPart = n * sizeof(int);
  // сдвигаем указатель позиции файла
  if(!SetFilePointerEx(hFile, q, &p, FILE_BEGIN))
  {
    cerr << "Set file pointer failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  // выводим на консоль значение указателя позиции файла
  cout << "File pointer: " << p.HighPart << ' ' << p.LowPart << endl;
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