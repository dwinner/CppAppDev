#include <windows.h>
#include <iostream.h>

// �������� ������� ��� ������ ��������� �� ������ �� �������
void CoutErrorMessage();

// ���� ��� ������� ������ ��������� �� ������ �� �������
int main()
{
  HANDLE  hHandle=NULL;

  // ������������ ����� ������� �������� �����������
  if (!CloseHandle(hHandle))
    CoutErrorMessage();

  return 0;
}