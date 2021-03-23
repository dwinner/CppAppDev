#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hChangeHandle;
  
  // находим первое изменение в каталоге
  hChangeHandle = FindFirstChangeNotification(
    "C:\\demo_dir",    // имя каталога
    TRUE,              // отслеживать также подкаталоги
    FILE_NOTIFY_CHANGE_FILE_NAME // отслеживать изменение имени каталога
    | FILE_NOTIFY_CHANGE_SIZE    // и изменение его размера
  );

  if (hChangeHandle == INVALID_HANDLE_VALUE)
  {
    cerr << "Find first change notification failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // нужно изменить каталог
  cout << "Wait for changes in the directory." << endl;
  // ждем первого изменения в каталоге
  if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
    cout << "First notification: the directory was changed." << endl;
  else
  {
    cerr << "Wait for single object failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // находим второе изменение в каталоге
  if (!FindNextChangeNotification(hChangeHandle))
  {
    cerr << "Find next change notification failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ждем второго изменения в каталоге
  if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
    cout << "Next notification: the directory was changed." << endl;
  else
  {
    cerr << "Wait for single object failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // закрываем дескриптор поиска
  FindCloseChangeNotification(hChangeHandle);

  return 0;
}