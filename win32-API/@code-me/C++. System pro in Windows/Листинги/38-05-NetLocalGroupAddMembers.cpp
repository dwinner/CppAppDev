#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";      // ��� �������
  wchar_t group_name[GNLEN];               // ��� ��������� ������
  wchar_t user_name[UNLEN];                // ��� ������������
  LOCALGROUP_MEMBERS_INFO_3  member_info;  // ���������� � ����� ������

  NET_API_STATUS  ret_status;      // ��� �������� �� �������

  printf("Input server name: ");
  // ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);         // ������ ��� ������

  printf("Input a domain name: ");
  wscanf(L"%s", user_name);          // ������ ��� ������

  wcscat(user_name, L"\\");          // ������������ ������ '\'

  printf("Input a user name: ");
  // ������ ��� ������������
  wscanf(L"%s", user_name + wcslen(user_name));

  // ������������� ���������� � ������������
  member_info.lgrmi3_domainandname = user_name;

  // ��������� ������������ � ��������� ������
  ret_status = NetLocalGroupAddMembers(
    server_name,           // ��� �������
    group_name,            // ��� ������
    3,                     // ������� ����������
    (LPBYTE)&member_info,  // ��� ������� ������
    1);                    // ��������� ������ ����� ������
  if (ret_status != NERR_Success)
  {
    printf("Ret status: %d\n", ret_status);
    printf("Net local group add members failed.\n");

    return ret_status;
  }

  printf("The member is added.\n");

  return 0;
}