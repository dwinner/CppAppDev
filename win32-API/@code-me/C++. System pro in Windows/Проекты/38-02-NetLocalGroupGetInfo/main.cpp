#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";    // ��� �������
  wchar_t  group_name[GNLEN];            // ��� ��������� ������
  LOCALGROUP_INFO_1  *buf_ptr = NULL;    // ����� ������ ��� ������
  NET_API_STATUS    ret_status;          // ��� �������� �� �������

  printf("Input server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a name for the local group: ");
  wscanf(L"%s", group_name);         // ������ ��� ������

  // �������� ���������� � ��������� ������
  ret_status = NetLocalGroupGetInfo(
    server_name,           // ��� �������
    group_name,            // ��� ������
    1,                     // �������� ��� ������ � �����������
    (LPBYTE*)&buf_ptr);    // ��������� �� ����� ������ ��� ������
  // ��������� ���������� �������
  if (ret_status != NERR_Success)
  {
    printf("Net local group get info failed.\n");
    NetApiBufferFree(buf_ptr);  // ����������� ����� ��� ������ 

    return ret_status;
  }

  // ������� �� ������� ��� ��������� ������ � �����������
  wprintf(L"Local group name: %s\n", buf_ptr->lgrpi1_name);
  wprintf(L"Comment: %s\n", buf_ptr->lgrpi1_comment);

  NetApiBufferFree(buf_ptr);     // ����������� ����� ��� ������

  return 0;
}