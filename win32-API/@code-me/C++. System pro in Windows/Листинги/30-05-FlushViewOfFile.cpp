#include <windows.h>
#include <fstream.h>

int main()
{
  int  a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  char  file_name[] = "C:\\Demo.bin";
  char  mapping_name[] = "MappingName";
  HANDLE  hFile, hMapping;   // дескрипторы файла и объекта отображения
  int  *ptr;                 // для указателя на массив

  // открываем файл для вывода
  ofstream  out(file_name, ios::out | ios::binary);
  if (!out)
  {
    cerr << "File constructor failed." << endl;
    return 0;
  }
  // выводим исходный массив в файл и на консоль
  cout << "Initial array: ";
  for (int i = 0; i < 10; ++i)
  {
    out.write((char*)&a[i], sizeof(int));
    cout << a[i] << ' ';
  }
  cout << endl;
  // закрываем выходной файл
  out.close();
//----------------------------------------------------------------------
  // открываем файл для отображения в память
  hFile = CreateFile(file_name, GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Create file failed." << endl;
    return GetLastError();
  }
  // открываем объект, отображающий файл в память
  hMapping = CreateFileMapping(
        hFile,           // дескриптор открытого файла
        NULL,            // атрибуты защиты по умолчанию
        PAGE_READWRITE,  // режим доступа
        0, 0,      // размер объекта отображения равен размеру файла
        mapping_name);   // имя объекта отображения
  if (!hMapping)
  {
    cerr << "Create file mapping failed." << endl;
    return GetLastError();
  }
  // создаем вид файла
  ptr = (int*)MapViewOfFile(
      hMapping,        // дескриптор объекта отображения
      FILE_MAP_WRITE,  // режим доступа к виду
      0, 0,            // отображаем файл с начала
      0);              // отображаем весь файл
  // изменяем значения элементов массива
  for (i = 0; i < 10; ++i)
    ptr[i] += 10;
  // сбрасываем весь вид на диск
  if (!FlushViewOfFile(ptr, 0))
  {
    cerr << "Flush view of file failed." << endl;
    return GetLastError();
  }
//----------------------------------------------------------------------
// создаем процесс, который будет читать данные из отображаемого 
// в память файла
  char lpszAppName[] = "C:\\ConsoleProcess.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION piApp;

  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  // создаем новый консольный процесс
  if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
  {
    cerr << "Create process failed." << endl;
    return GetLastError();
  }
  // ждем завершения созданного прцесса
  WaitForSingleObject(piApp.hProcess, INFINITE);
  // закрываем дескрипторы этого процесса в текущем процессе
  CloseHandle(piApp.hThread);
  CloseHandle(piApp.hProcess);
//----------------------------------------------------------------------
// отменяем отображение файла в память
  if (!UnmapViewOfFile(ptr))
  {
    cerr << "Unmap view of file failed." << endl;
    return GetLastError();
  }
  // закрываем объкт отображения файла в память
  if (!CloseHandle(hMapping))
  {
    cerr << "Close file failed." << endl;
    return GetLastError();
  }
  // закрываем файл
  if (!CloseHandle(hFile))
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