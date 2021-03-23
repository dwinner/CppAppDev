#include <windows.h>
#include <conio.h>

int main()
{
  // ������������ �������
  if (!AllocConsole())
  {
    MessageBox(NULL,
      "Console allocation failed", "������ Win32 API",
      MB_OK | MB_ICONINFORMATION
    );
    return 0;
  }

  _cputs("I am created.\n");
  _cputs("Press any char to exit.\n");
  _getch();

  // ����������� �������
  if (!FreeConsole())
  {
    _cputs("Free console failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
  }

  return 0;
}