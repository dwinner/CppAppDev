#include <windows.h>
#include <stdio.h>

volatile UINT count;
volatile BOOL flag = TRUE;

void thread()
{
  while(flag)
  {
    count++;
    printf("count = %u\n", count);
    Sleep(500);
  }
}

int main()
{
  HANDLE hThread;
  DWORD IDThread;

  HANDLE hProcess;     // дескриптор процесса
  HANDLE hToken;       // дескриптор маркера доступа
  HANDLE hDuplicate;   // дескриптор дубликата маркера доступа

  DWORD dwRetCode;     // код возврата

  // запускаем поток
  hThread = CreateThread(
    NULL,          // защита по умолчанию
    0,             // размер стека по умолчанию
    (LPTHREAD_START_ROUTINE)thread,  // адрес программы потока
    NULL,          // параметров нет
    CREATE_SUSPENDED,    // подвешенное состояние потока
    &IDThread);    // идентификатор потока
  if (hThread == NULL)
  {
    printf("Create thread failed.\n");
    return GetLastError();
  }

  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();
  
  // получаем маркер доступа потока
  if (!OpenProcessToken(
    hProcess,          // дескриптор процесса
    TOKEN_DUPLICATE,   // дублирование маркера доступа
    &hToken))          // дескриптор маркера
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // дублируем маркер доступа
  if (!DuplicateToken(
    hToken,                  // маркер доступа
    SecurityImpersonation,   // уровень замещения
    &hDuplicate))            // адрес дубликата маркера доступа
  {
    dwRetCode = GetLastError();
    printf( "Duplicate token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // устанавливаем замещающий маркер доступа для потока
  if (!SetThreadToken(
    &hThread,      // адрес дескриптора потока
    hDuplicate))   // дубликат маркера доступа
  {
    dwRetCode = GetLastError();
    printf( "Set thread token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  printf("Press any key to exit.\n");

  // возобновляем поток
  ResumeThread(hThread);

  // ждем команду на завершение потока
  getchar();

  flag = FALSE;    // завершить поток

  CloseHandle(hThread);
  CloseHandle(hToken);

  return 0;
}