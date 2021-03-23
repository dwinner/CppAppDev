#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t domain_name[256] = L"\\\\";  // имя сервера
  wchar_t user_name[UNLEN];            // имя пользователя
  wchar_t old_password[PWLEN];         // старый пароль пользователя
  wchar_t new_password[PWLEN];         // новый пароль пользователя

  NET_API_STATUS  ret_status;  // код возврата из функции

  printf("Input server or domain name: ");
  wscanf(L"%s", domain_name);    // читаем имя домена

  printf("Input user name: ");
  wscanf(L"%s", user_name);      // читаем имя пользователя

  printf("Input old password: ");
  wscanf(L"%s", old_password);   // читаем имя пользователя

  printf("Input new password: ");
  wscanf(L"%s", new_password);   // читаем имя пользователя

  // изменяем пароль пользователя
  ret_status = NetUserChangePassword(
    domain_name,     // имя домена
    user_name,       // имя пользователя
    old_password,    // старый пароль
    new_password);   // новый пароль

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user change password failed.\n");
    printf("Net API Status: %d\n", ret_status);

    return ret_status;
  }

  printf("The password was changed.\n");

  return 0;
}