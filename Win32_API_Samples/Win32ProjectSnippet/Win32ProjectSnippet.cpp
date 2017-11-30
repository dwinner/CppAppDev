// Win32ProjectSnippet.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32ProjectSnippet.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // current instance
TCHAR szTitle[MAX_LOADSTRING]; // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ const HINSTANCE hInstance,
                            _In_opt_                            HINSTANCE hPrevInstance,
                            _In_                            LPTSTR lpCmdLine,
                            _In_                            const int nCmdShow)
{
   UNREFERENCED_PARAMETER(hPrevInstance);
   UNREFERENCED_PARAMETER(lpCmdLine);

   // TODO: Place code here.
   MSG msg;
   HACCEL hAccelTable;

   // Initialize global strings
   LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   LoadString(hInstance, IDC_WIN32PROJECTSNIPPET, szWindowClass, MAX_LOADSTRING);
   MyRegisterClass(hInstance);

   // Perform application initialization:
   if (!InitInstance(hInstance, nCmdShow))
   {
      return FALSE;
   }

   hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECTSNIPPET));

   // Main message loop:
   while (GetMessage(&msg, nullptr, 0, 0))
   {
      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }

   return static_cast<int>(msg.wParam);
}

/**
 * \brief Registers the window class
 * \param hInstance 
 * \return 
 */
ATOM MyRegisterClass(const HINSTANCE hInstance)
{
   WNDCLASSEX wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);

   wcex.style = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc = WndProc;
   wcex.cbClsExtra = 0;
   wcex.cbWndExtra = 0;
   wcex.hInstance = hInstance;
   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECTSNIPPET));
   wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
   wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
   wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECTSNIPPET);
   wcex.lpszClassName = szWindowClass;
   wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

   return RegisterClassEx(&wcex);
}

/**
 * \brief Saves instance handle and creates main window
 * \details In this function, we save the instance handle in a global variable and create and display the main program window
 * \param hInstance 
 * \param nCmdShow 
 * \return TRUE, if window has been successfully created, FALSE - otherwise
 */
BOOL InitInstance(HINSTANCE hInstance, const int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass,
      szTitle,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      0,
      CW_USEDEFAULT,
      0,
      NULL,
      NULL,
      hInstance,
      NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/**
 * \brief Processes messages for the main window
 * \details
 *    WM_COMMAND	- process the application menu
 *    WM_PAINT	- Paint the main window
 *    WM_DESTROY	- post a quit message and return
 * \param hWnd Window descriptor
 * \param message Message 
 * \param wParam 
 * \param lParam 
 * \return LRESULT
 */
LRESULT CALLBACK WndProc(HWND hWnd, const UINT message, WPARAM wParam, const LPARAM lParam)
{
   int wmId, wmEvent;
   PAINTSTRUCT ps;
   HDC hdc;

   switch (message)
   {
   case WM_COMMAND:
      wmId = LOWORD(wParam);
      wmEvent = HIWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
      case IDM_ABOUT:
         DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
         break;
      case IDM_EXIT:
         DestroyWindow(hWnd);
         break;
      default:
         return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;

   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      // TODO: Add any drawing code here...
      EndPaint(hWnd, &ps);
      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;

   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }

   return 0;
}

/**
 * \brief Message handler for about box
 * \param hDlg Dialog descriptor
 * \param message Message
 * \param wParam w-param
 * \param lParam l-param
 * \return TRUE or FALSE
 */
INT_PTR CALLBACK About(const HWND hDlg, const UINT message, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   switch (message)
   {
   case WM_INITDIALOG:
      return static_cast<INT_PTR>(TRUE);

   case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
      {
         EndDialog(hDlg, LOWORD(wParam));
         return static_cast<INT_PTR>(TRUE);
      }
      break;

   default: return static_cast<INT_PTR>(FALSE);
   }

   return static_cast<INT_PTR>(FALSE);
}
