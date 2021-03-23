#include <windows.h>
#include <iostream.h>

int main()
{
  LPVOID  lp;
  const int size = 1000;
  
  // ������������ ����������� ������
  lp = VirtualAlloc(
      (LPVOID) 0x00890002, 
      size, 
      MEM_RESERVE | MEM_COMMIT, 
      PAGE_READWRITE);
  if(!lp)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  cout << "Virtual memory address: " << lp << endl;

  // ����������� ����������� ������
  if (!VirtualFree(lp, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }
  return 0;
}