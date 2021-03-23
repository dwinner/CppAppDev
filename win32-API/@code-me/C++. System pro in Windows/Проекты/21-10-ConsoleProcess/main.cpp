#include <windows.h>
#include <iostream.h>

int main(int argc, char *argv[])
{
  char c;
  char  answer[] = "This is an answer.";
  HANDLE  hWrite, hRead;   // события для синхронизации
  char  WriteEvent[] = "WriteEvent";
  char  ReadEvent[] = "ReadEvent";
  char  *v;      // для адреса виртуальной памяти

  // открываем события
  hWrite = OpenEvent(EVENT_MODIFY_STATE, FALSE, WriteEvent);
  hRead = OpenEvent(EVENT_MODIFY_STATE, FALSE, ReadEvent);

  // преобразуем параметр в адрес
  v = (char*)atoi(argv[1]);
  // выводим сообщение
  cout <<  v << endl;

  // ждем разрешения на запись
  WaitForSingleObject(hWrite, INFINITE);
  // записываем ответ
  strcpy(v, "This is an answer.");
  // разрешаем чтение
  SetEvent(hRead);

  // закрываем дескрипторы
  CloseHandle(hWrite);
  CloseHandle(hRead);

  // ждем команды на завершение
  cout << "Input any char to exit: ";
  cin >> c;
  
  return 0;
}