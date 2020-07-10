listing 1
/* A minimal Windows 2000 skeleton. */

#include <windows.h>

LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);

char szWinName[] = "MyWin"; /* name of window class */

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, 
                   LPSTR lpszArgs, int nWinMode)
{
  HWND hwnd;
  MSG msg;
  WNDCLASSEX wcl;

  /* Define a window class. */
  wcl.cbSize = sizeof(WNDCLASSEX); 

  wcl.hInstance = hThisInst;     /* handle to this instance */
  wcl.lpszClassName = szWinName; /* window class name */
  wcl.lpfnWndProc = WindowFunc;  /* window function */
  wcl.style = 0;                 /* default style */

  wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); /* large icon */
  wcl.hIconSm = NULL; /* use small version of large icon */
  wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  /* cursor style */

  wcl.lpszMenuName = NULL; /* no class menu */
  wcl.cbClsExtra = 0;      /* no extra memory needed */
  wcl.cbWndExtra = 0; 

  /* Make the window background white. */
  wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 

  /* Register the window class. */
  if(!RegisterClassEx(&wcl)) return 0;

  /* Now that a window class has been registered, a window
     can be created. */
  hwnd = CreateWindow(
    szWinName, /* name of window class */
    "Windows 2000 Skeleton", /* title */
    WS_OVERLAPPEDWINDOW, /* window style - normal */
    CW_USEDEFAULT, /* X coordinate - let Windows decide */
    CW_USEDEFAULT, /* Y coordinate - let Windows decide */
    CW_USEDEFAULT, /* width - let Windows decide */
    CW_USEDEFAULT, /* height - let Windows decide */
    NULL,          /* no parent window */
    NULL,          /* no menu */
    hThisInst,     /* instance handle */
    NULL           /* no additional arguments */
  );

  /* Display the window. */
  ShowWindow(hwnd, nWinMode);
  UpdateWindow(hwnd);

  /* Create the message loop. */
  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg); /* translate keyboard messages */
    DispatchMessage(&msg);  /* return control to Windows 2000 */
  }
  return msg.wParam;
}

/* This function is called by Windows 2000 and is passed 
   messages from the message queue.
*/
LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message,
                            WPARAM wParam, LPARAM lParam)
{
  switch(message) {
    case WM_DESTROY: /* terminate the program */
      PostQuitMessage(0);
      break;
    default:
      /* Let Windows 2000 process any messages not specified in
         the preceding switch statement. */
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
}

listing 2
DESCRIPTION 'Skeleton Program'
EXETYPE WINDOWS
CODE PRELOAD MOVEABLE DISCARDABLE
DATA PRELOAD MOVEABLE MULTIPLE
HEAPSIZE 8192
STACKSIZE 8192
EXPORTS WindowFunc

