#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" ) // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";    // имя сервера
  wchar_t user_name[UNLEN];              // имя пользователя
  wchar_t user_password[PWLEN];          // пароль пользователя
  wchar_t user_comment[256];             // комментарии о пользователе
  USER_INFO_1    ui;                     // информация о пользователе
  NET_API_STATUS  ret_status;            // код возврата из функции

  printf("Input server name: ");
// формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input user name: ");   // читаем имя пользователя
  wscanf(L"%s", user_name);      // читаем имя пользователя
  ui.usri1_name = user_name;     // устанавливаем имя пользователя

  printf("Input user password: ");
  wscanf(L"%s", user_password);      // читаем пароль пользователя
  ui.usri1_password = user_password; // устанавливаем пароль пользователя

  ui.usri1_priv = USER_PRIV_USER;  // обычный пользователь
  ui.usri1_home_dir = NULL;        // домашнего каталога нет

  printf("Input user comment: ");
  getwchar();                      // очищаем поток
  _getws(user_comment);            // читаем комментарии о пользователе
  ui.usri1_comment = user_comment; // устанавливаем комментарии

  ui.usri1_flags = UF_SCRIPT;    // исполнять скрипт при входе пользователя в систему
  ui.usri1_script_path = NULL;   // пока файл со скриптом не определяем

  // добавляем пользователя
  ret_status = NetUserAdd(
    server_name,     // имя сервера
    1,               // уровень информации 1
    (LPBYTE)&ui,     // адрес информации о пользователе
    NULL);           // индексирования в структуре данных нет

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user add failed.\n");
    printf("Error code: %u\n", ret_status);

    return ret_status;
  }
  printf("The user is added.\n");

  return 0;
}