#include <windows.h>
#include <fstream.h>

int main()
{
  char  MappingName[] = "MappingName";
  HANDLE  hMapping;      // дескриптор объекта, отображающего файл
  int    *ptr;           // для указателя на массив
  const int    n = 10;   // размерность массива

  cout << "This is a child process." << endl;
  // открываем объект отображения файла в память
  hMapping = CreateFileMapping(
        INVALID_HANDLE_VALUE,  // файл подкачки страниц
        NULL,            // атрибуты защиты по умолчанию
        PAGE_READWRITE,  // режим доступа: чтение и запись
        0,               // старшее слово = 0
        n * sizeof(int), // младшее слово = длине массива
        MappingName);    // имя объекта отображения
  if (!hMapping)
  {
    cerr << "Create file mapping failed." << endl;
    return GetLastError();
  }
  // создаем вид файла
  ptr = (int*)MapViewOfFile(
      hMapping,        // дескриптор объекта отображения
      FILE_MAP_WRITE,  // режим доступа к виду
      0,0,             // отображаем файл с начала
      0);              // отображаем весь файл
  // выводим массив из вида на консоль
  cout  << "Array: ";
  for (int i = 0; i < n; ++i)
    cout << ptr[i] << ' ';
  cout << endl;
  // отменяем отображение файла в память
  if (!UnmapViewOfFile(ptr))
  {
    cerr << "Unmap view of file failed." << endl;
    return GetLastError();
  }
  // закрываем объект отображения файла в память
  if (!CloseHandle(hMapping))
  {
    cerr << "Close file failed." << endl;
    return GetLastError();
  }
  // ждем команду на завершение процесса
  char  c;
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}