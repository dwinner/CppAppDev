#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;    // ��������� �� ������
  int  size = 4096;  // ������ ����

  // ������� ���� �����������
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, 0);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // ������������ ������ ��� �������
  a = (int*)HeapAlloc(hHeap, NULL, 4 * sizeof(int));
  // ��������� ��������� ��������������� ����� ������
  if (!HeapValidate(hHeap, HEAP_NO_SERIALIZE, a))
    cout << "The block is bad." << endl;
  else
    cout << "The block is good." << endl;

  // ��������� ����
  HeapDestroy(hHeap);

  return 0;
}