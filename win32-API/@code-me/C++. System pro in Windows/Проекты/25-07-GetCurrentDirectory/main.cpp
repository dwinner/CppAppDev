#include <windows.h>
#include <iostream.h>

int main()
{
  DWORD  dwNumberOfChar;
  char  szDirName[MAX_PATH];

  // определяем имя текущего каталога
  dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);
  if (dwNumberOfChar == 0)
  {
    cerr << "Get current directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // выводим на консоль имя текущего каталога
  cout << "Current directory name: " << szDirName << endl;
  // устанавливаем текущий каталог для удаления из него файлов
  if (!SetCurrentDirectory("C:\\demo_dir"))
  {
    cerr << "Set current directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // определяем имя нового текущего каталога
  dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);
  if (dwNumberOfChar == 0)
  {
    cerr << "Get current directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // выводим на консоль имя нового текущего каталога
  cout << "Current directory name: " << szDirName << endl;

  return 0;
}