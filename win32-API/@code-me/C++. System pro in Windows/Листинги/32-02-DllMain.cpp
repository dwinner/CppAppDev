#include <windows.h>
#include <iostream.h>

DWORD  dwTlsIndex;   // ������ ������������ ��������� ������ ������

// ������� �������
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
  BOOL  retVal = TRUE;   // ������������ ��������
  int    *pCount;        // ��������� �� �������

  switch (dwReason)
  {
  case DLL_PROCESS_ATTACH:   // �������� DLL
    // ������������ ��������� ������ �������
    dwTlsIndex = TlsAlloc();
    if (dwTlsIndex == -1)
    {
      cerr << "Tls allocation failed." << endl;
      retVal = FALSE;
    }
    break;
  case DLL_THREAD_ATTACH:    // �������� ������
    // ����������� ������ ��� �������
    pCount = new int(0);
    // ���������� ��������� � �������
    if (!TlsSetValue(dwTlsIndex, (LPVOID)pCount))
    {
      cerr << "Tls set value failed." << endl;
      retVal = FALSE;
    }
    break;
  case DLL_THREAD_DETACH:    // ���������� ������
    // �������� ��������� �� �������
    pCount = (int*)TlsGetValue(dwTlsIndex);
    // ���� ������, �� ������ ���������
    if (!pCount)
    {
      cerr << "Tls get value failed." << endl;
      retVal = FALSE;
    }
    // �����, ����������� ������
    else
      delete pCount;
    break;
  case DLL_PROCESS_DETACH:  // ���������� DLL
    // ����������� ��������� ������ ������
    if (!TlsFree(dwTlsIndex))
    {
      cerr << "Tls free failed." << endl;
      retVal = FALSE;
    }
    break;
  }

  return retVal;
}

extern "C" __declspec(dllexport) int Add(int n)
{
  int  *pCount;

  // �������� ��������� �� ��������� �������
  pCount = (int*)TlsGetValue(dwTlsIndex);
  if (!pCount)
  {
    cerr << "Tls get value failed." << endl;
    return GetLastError();
  }
  // ����������� �������� ��������
  *pCount += n;

  return *pCount;
}