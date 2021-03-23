#include <windows.h>
#include <iostream.h>

int main()
{
  BYTE *a, *b;     // ��������� �� ����� ������
  const int size = 1000;   // ����������� �������

  // ������������ ����������� ������
  a = (BYTE*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
  if(!a)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }
  b = (BYTE*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
  if(!b)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  // �������������� �������� X
  FillMemory(a, size, 'X');
  // �������� ���� A � ���� B
  CopyMemory(b, a, size);
  // ������������� ���������
  cout << "b[10] = " << b[10] << endl;

  // ����������� ����������� ������
  if (!VirtualFree(a, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  return 0;
}