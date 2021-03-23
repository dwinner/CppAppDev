#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  DWORD  entries_read;           // количество элементов
  DWORD  total_entries;          // нумерация элементов
  LOCALGROUP_INFO_1  *buf_ptr = NULL;  // адрес буфера для данных
  NET_API_STATUS  ret_status;    // код возврата из функции

  // перечисляем локальные группы
  ret_status = NetLocalGroupEnum(
    NULL,                // локальный компьютер
    1,                   // получаем имя группы и комментарий
    (LPBYTE*)&buf_ptr,   // указатель на адрес буфера для данных    
    MAX_PREFERRED_LENGTH,  // длина буфера по требованию
    &entries_read,       // указатель на количество элементов
    &total_entries,      // указатель на нумерацию элементов
    NULL);
  // проверяем завершение функции
  if (ret_status != NERR_Success)
  {
    printf("Net local group enumeration failed.\n");
    NetApiBufferFree(buf_ptr);   // освобождаем буфер для данных 

    return ret_status;
  }

  printf("Local groups enumeration:\n");
  // выводим на консоль имена локальных групп и комментарии
  for (DWORD i = 0; i < entries_read; ++i)
  {
    wprintf(L"Name: %s\n", buf_ptr[i].lgrpi1_name);
    wprintf(L"Comment: %s\n", buf_ptr[i].lgrpi1_comment);
  }

  NetApiBufferFree(buf_ptr);     // освобождаем буфер для данных

  return 0;
}