/* Goncharov Prohor, 09-3, 01.06.2026 */

#include <stdio.h>
#include <windows.h>
#define WND_CLASS_NAME "cgsg209"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstanse, 
                   CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

  wc.style = 0;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpfnWndProc = MyWindowFunc;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "error", "ERROR", MB_ICONERROR | MB_OK);
    return 0;
  }

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);       
    DispatchMessage(&msg);
  }


  MessageBox(NULL, "aaa", "Okno", MB_OK);
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
  case WM_DESTROY:
    PostMessage(NULL, WM_QUIT, 0, 0);
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  }
  return 30;
}