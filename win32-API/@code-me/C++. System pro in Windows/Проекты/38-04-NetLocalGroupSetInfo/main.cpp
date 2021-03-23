#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";    // ��� �������
  wchar_t  old_name[GNLEN];        // ������ ��� ��������� ������
  wchar_t  new_name[GNLEN];        // ����� ��� ��������� ������
  wchar_t comment[MAXCOMMENTSZ];   // ����� �����������

  LOCALGROUP_INFO_0 group_info_0;  // ���������� �� ����� ������
  LOCALGROUP_INFO_1 group_info_1;  // �������� ����� ������

  NET_API_STATUS    ret_status;    // ��� �������� �� �������

  printf("Input a server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", old_name);         // ������ ��� ������

  printf("Input a new name for the group: ");
  wscanf(L"%s", new_name);         // ������ ����� ��� ������

  // ������������� ����� ����� � ���������
  group_info_0.lgrpi0_name = new_name;

  // �������� ��� ������
  ret_status = NetLocalGroupSetInfo(
    server_name,       // ��� �������
    old_name,          // ��� ������
    0,                 // ����� ��� ������
    (LPBYTE)&group_info_0,  // ����� ���������� � ������
    NULL);             // �������������� ���������� ���
  // ��������� ���������� �������
  if (ret_status != NERR_Success)
  {
    printf("Net local group set name failed.\n");

    return ret_status;
  }
  printf("Local group name was changed.\n");

  printf("Input group comments: ");
  getwchar();          // ������� �����
  _getws(comment);     // ������ ����������� � ������������
  // ������������� ����� �����������
  group_info_1.lgrpi1_comment = comment;

  // �������� �������� ������
  ret_status = NetLocalGroupSetInfo(
    server_name,       // ��� �������
    new_name,          // ��� ������
    1,                 // �������� ��� ������ � �����������
    (LPBYTE)&group_info_1,  // ����� �������� ������
    NULL);             // �������������� ���������� ���
  // ��������� ���������� �������
  if (ret_status != NERR_Success)
  {
    printf("Net local group set info failed.\n");

    return ret_status;
  }
  printf("Local group comment was changed.\n");

  return 0;
}