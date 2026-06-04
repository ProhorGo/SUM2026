/* Goncharov Prohor, 09-3, 03.06.2026 */


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
  return 0;
}
                     
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Message,
                              WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  SYSTEMTIME st;
  char Buf[100];
  static INT W, H;
  static BOOL is_select = FALSE;
  switch (Message)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    return 0;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_COMMAND:
    if (LOWORD(wParam) == 123)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (LOWORD(wParam) == 124)
    {
      DWORD style = GetWindowLong(hWnd, GWL_STYLE);

      if (style & WS_MAXIMIZE)
        ShowWindow(hWnd, SW_NORMAL);  
      else
        ShowWindow(hWnd, SW_MAXIMIZE);
    }
    else if (LOWORD(wParam) == 125)
    {
      DWORD state = SendMessage((HWND)lParam, BM_GETSTATE, 0, 0);

      is_select = !!(state & BST_CHECKED);
      if (is_select)
        SendMessage((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
      else
        SendMessage((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
      InvalidateRect(hWnd, NULL, FALSE);
    }
    return 0; 
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    //
    SetDCBrushColor(hDC, RGB(30, 155, 155));
    Rectangle(hDC, 100, 100, 300, 200);
    if (is_select)
      SelectObject(hDC, GetStockObject(NULL_BRUSH));
    else
      SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(255, 0, 0));

    Ellipse(hDC, 0, 0, W, H);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SetDCPenColor(hDC, RGB(30, 155, 155));
    Ellipse(hDC, pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);



    GetLocalTime(&st);
    TextOut(hDC, 130, 30, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond));
    EndPaint(hWnd, &ps);
    return 0;
  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "close?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return 0;
    break;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 30, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Message, wParam, lParam);
}