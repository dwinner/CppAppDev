#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  wchar_t  group_name[GNLEN];          // ��� ��������� ������
  wchar_t comment[MAXCOMMENTSZ];       // ����������� � ������
  LOCALGROUP_INFO_1  group_info;       // ���������� � ������
  NET_API_STATUS ret_status;           // ��� �������� �� �������

  printf("Input server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a name for the local group: ");
  wscanf(L"%s", group_name);           // ������ ��� ������
  group_info.lgrpi1_name = group_name;   // ������������� ����� ����� � ���������

  
  printf("Input group comments: ");
  getwchar();              // ������� �����
  _getws(comment);         // ������ ����������� � ��������� ������
  group_info.lgrpi1_comment = comment;   // ������������� �����������

  // ������� ��������� ������
  ret_status = NetLocalGroupAdd(
    server_name,           // ��� �������
    1,                     // ������� ������� ������
    (LPBYTE)&group_info,   // ��� ������ � �����������
    NULL);                 // ���������� ������ �� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net local group add failed.\n");

    return ret_status;
  }

  printf("The group is created.\n");

  return 0;
}