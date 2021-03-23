#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t domain_name[256] = L"\\\\";  // ��� �������
  wchar_t user_name[UNLEN];            // ��� ������������
  wchar_t old_password[PWLEN];         // ������ ������ ������������
  wchar_t new_password[PWLEN];         // ����� ������ ������������

  NET_API_STATUS  ret_status;  // ��� �������� �� �������

  printf("Input server or domain name: ");
  wscanf(L"%s", domain_name);    // ������ ��� ������

  printf("Input user name: ");
  wscanf(L"%s", user_name);      // ������ ��� ������������

  printf("Input old password: ");
  wscanf(L"%s", old_password);   // ������ ��� ������������

  printf("Input new password: ");
  wscanf(L"%s", new_password);   // ������ ��� ������������

  // �������� ������ ������������
  ret_status = NetUserChangePassword(
    domain_name,     // ��� ������
    user_name,       // ��� ������������
    old_password,    // ������ ������
    new_password);   // ����� ������

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user change password failed.\n");
    printf("Net API Status: %d\n", ret_status);

    return ret_status;
  }

  printf("The password was changed.\n");

  return 0;
}