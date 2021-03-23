#include <windows.h>
#include <fstream.h>

int main()
{
  char    MappingName[] = "MappingName";
  HANDLE  hMapping;      // дескриптор объекта, отображающего файл
  int    *ptr;           // для указателя на массив
  const int    n = 10;   // размерность массива

  cout << "This is a parent process." << endl;
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
  // инициализируем массив и выводим его на консоль
  cout  << "Array: ";
  for (int i = 0; i < n; ++i)
  {
    ptr[i] = i;
    cout << ptr[i] << ' ';
  }
  cout << endl;
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