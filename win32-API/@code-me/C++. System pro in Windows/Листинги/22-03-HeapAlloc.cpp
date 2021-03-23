#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;      // ��������� �� ������
  int  size = 4096;    // ������ �������, � ����� ����

  // ������� ���� �����������
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // �������� ������������ ������ ��� ������
  a = (int*)HeapAlloc(hHeap, NULL, size * sizeof(int));
  // ������������ ������ � ������ �������
  if (!a)
  {
    cout << "Heap allocation failed." << endl;
    return GetLastError();
  }
  // ��������� ����
  if (!HeapDestroy(hHeap))
  {
    cout << "Heap destroy failed." << endl;
    return GetLastError();
  }

  return 0;
}