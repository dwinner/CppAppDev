#include <windows.h>

// �������� ������� ������ ��������� �� ������ � MessageBox
void ErrorMessageBox();

// ���� ��� ������� ������ ��������� �� ������ �� �������
int main()
{
  HANDLE  hHandle=NULL;

  // ������������ ����� ������� �������� �����������
  if (!CloseHandle(hHandle))
    ErrorMessageBox();

  return 0;
}