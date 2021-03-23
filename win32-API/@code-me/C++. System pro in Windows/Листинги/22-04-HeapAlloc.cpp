#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;      // ��������� �� ������
  int  size = 4096;    // ������ �������, � ����� ����

  // ������� ���� �����������
  hHeap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_GENERATE_EXCEPTIONS,
    size, size);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // �������� ������������ ������ �� ����
  __try
  {
    a = (int*)HeapAlloc(hHeap, NULL, size * sizeof(int));
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    DWORD ecode = GetExceptionCode();

    if (ecode == STATUS_NO_MEMORY)
      cout << "STATUS_NO_MEMORY exception." << endl;
    else
      cout << "Some exception." << endl;
  }
  // ��������� ����
  if (!HeapDestroy(hHeap))
  {
    cout << "Heap destroy failed." << endl;
    return GetLastError();
  }

  return 0;
}