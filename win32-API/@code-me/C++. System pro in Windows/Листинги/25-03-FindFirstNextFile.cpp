#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFindFile;
  WIN32_FIND_DATA  fd;

  // находим первый файл
  hFindFile = FindFirstFile("C:\\demo_dir\\*", &fd);
  if (hFindFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Find first file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // выводим на консоль имя первого файла
  cout << "The first file name: " << fd.cFileName << endl;
  // находим следующий файл и выводим на консоль его имя
  while (FindNextFile(hFindFile, &fd))
    cout << "The next file name: " << fd.cFileName << endl;
  // закрываем дескриптор поиска
  FindClose(hFindFile);

  return 0;
}