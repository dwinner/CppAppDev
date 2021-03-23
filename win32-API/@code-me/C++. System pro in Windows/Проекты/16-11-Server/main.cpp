#include <windows.h>
#include <iostream.h>
#include <string.h>

int main()
{
  HANDLE   hNamedPipe;
  SECURITY_ATTRIBUTES sa;    // атрибуты безопасности
  SECURITY_DESCRIPTOR sd;    // дескриптор безопасности
  
  // инициализаци€ атрибутов безопасности
  sa.nLength = sizeof(sa);
  sa.bInheritHandle = FALSE;   // дескриптор канала ненаследуемый
  // инициализируем дескриптор безопасности
  InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
  // разрешаем доступ к именованному каналу всем пользовател€м
  SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
  sa.lpSecurityDescriptor = &sd;

  // создаем именованный канал дл€ чтени€ и записи
  hNamedPipe = CreateNamedPipe(
    "\\\\.\\pipe\\demo_pipe",      // им€ канала
    PIPE_ACCESS_DUPLEX,    // читаем из канала и пишем в канал
    PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронна€ передача сообщений
    1,         // максимальное количество экземпл€ров канала 
    0,         // размер выходного буфера по умолчанию
    0,         // размер входного буфера по умолчанию
    INFINITE,  // клиент ждет св€зь бесконечно долго
    &sa        // доступ дл€ всех пользователей
    );
  // провер€ем на успешное создание
  if (hNamedPipe == INVALID_HANDLE_VALUE)
  {
    cerr << "Create named pipe failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to exit.";
    cin.get();
    
    return 0;
  }
  
  // ждем, пока клиент св€жетс€ с каналом
  cout << "The server is waiting for connection with a client." << endl;
  if(!ConnectNamedPipe(
    hNamedPipe,  // дескриптор канала
    NULL         // св€зь синхронна€
    ))
  {
    cerr << "Connect named pipe failed." << endl
      << "The last error code: "<<GetLastError() << endl;
    CloseHandle(hNamedPipe);
    cout << "Press any key to exit.";
    cin.get();
    
    return 0;
  }
  // завершаем процесс
  cout << "Press any key to exit.";
  cin.get();
  // закрываем дескриптор канала 
  CloseHandle(hNamedPipe);
  
  return 0;
}