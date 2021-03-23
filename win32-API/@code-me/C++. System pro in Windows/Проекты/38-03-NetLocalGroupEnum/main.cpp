#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  DWORD  entries_read;           // ���������� ���������
  DWORD  total_entries;          // ��������� ���������
  LOCALGROUP_INFO_1  *buf_ptr = NULL;  // ����� ������ ��� ������
  NET_API_STATUS  ret_status;    // ��� �������� �� �������

  // ����������� ��������� ������
  ret_status = NetLocalGroupEnum(
    NULL,                // ��������� ���������
    1,                   // �������� ��� ������ � �����������
    (LPBYTE*)&buf_ptr,   // ��������� �� ����� ������ ��� ������    
    MAX_PREFERRED_LENGTH,  // ����� ������ �� ����������
    &entries_read,       // ��������� �� ���������� ���������
    &total_entries,      // ��������� �� ��������� ���������
    NULL);
  // ��������� ���������� �������
  if (ret_status != NERR_Success)
  {
    printf("Net local group enumeration failed.\n");
    NetApiBufferFree(buf_ptr);   // ����������� ����� ��� ������ 

    return ret_status;
  }

  printf("Local groups enumeration:\n");
  // ������� �� ������� ����� ��������� ����� � �����������
  for (DWORD i = 0; i < entries_read; ++i)
  {
    wprintf(L"Name: %s\n", buf_ptr[i].lgrpi1_name);
    wprintf(L"Comment: %s\n", buf_ptr[i].lgrpi1_comment);
  }

  NetApiBufferFree(buf_ptr);     // ����������� ����� ��� ������

  return 0;
}