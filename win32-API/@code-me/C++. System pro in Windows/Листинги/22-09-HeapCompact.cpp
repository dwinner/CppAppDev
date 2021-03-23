#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;    // ��������� �� ������
  int  *b = NULL;    // ��������� �� ������
  int  *c = NULL;    // ��������� �� ������
  int  size = 4096;  // ������ ����
  UINT free;         // ����� ��������� ������ ����� ����������

  // ������� ���� �����������
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
    // ����������� ������ ��� �������
  a = (int*)HeapAlloc(hHeap, NULL, 1024);
  cout << "a = " << a << endl;
  b = (int*)HeapAlloc(hHeap, NULL, 1024);
  cout << "b = " << b << endl;
  c = (int*)HeapAlloc(hHeap, NULL, 1024);
  cout << "c = " << c << endl << endl;

  // ���������, ������� �������� ���������� ����� � ����
  free = HeapCompact(hHeap, HEAP_NO_SERIALIZE);
  if (!free) 
  {
    cout << "Heap compact failed." << endl;
    return GetLastError();
  }
  else
    cout << "Free: " << free << endl;

  // ����������� ������ ��� �������
  HeapFree(hHeap, NULL, b);
  HeapFree(hHeap, NULL, a);

  // ��������� ����
  free = HeapCompact(hHeap, HEAP_NO_SERIALIZE);
  if (!free) 
  {
    cout << "Heap compact failed." << endl;
    return GetLastError();
  }
  else
    cout << "Free: " << free << endl;

  // ��������� ����
  HeapDestroy(hHeap);

  return 0;
}