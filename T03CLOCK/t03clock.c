#include <stdio.h>
#include <windows.h>
#define WND_CLASS_NAME "cgsg209"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstanse, 
                   CHAR *CmdLine, INT ShowCmd )
{
  HWND hWnd;
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

  hWnd = CreateWindow(WND_CLASS_NAME, "SummerPractice2026", WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 500, 300, NULL, NULL, hInstance, NULL);
 
  CreateWindow("BUTTON", "Press me...", WS_CHILD | WS_VISIBLE,
    10, 10, 100, 30, hWnd, (HMENU)123, hInstance, NULL);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);       
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
                                        /*
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Message,
                              WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hBm; 
  static HDC clock;
  static BITMAP bm;
  POINT pt;
  SYSTEMTIME st;
  static BOOL is_select = FALSE;

  switch (Message)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 100, NULL);
    clock = LoadImage(NULL, "clockface.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    BitBlt(hDC, 0, 0, W, H, clock, 0, 0, SRCCOPY);
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    
    GetObject(clock, sizeof(BITMAP), &bm);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);11
    return 0;
  case WM_TIMER:
    GetObject(clock, sizeof(BITMAP), &bm);
    SelectObject(hMemDC, hBm);
    
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_COMMAND:
    if (LOWORD(wParam) == 123)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0; 
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    
    SetDCBrushColor(hDC, RGB(30, 155, 155));
    //Rectangle(hDC, H, 100, 300, 200);
    if (is_select)
      SelectObject(hDC, GetStockObject(NULL_BRUSH));
    else
      SelectObject(hDC, GetStockObject(WHITE_BRUSH));     

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "close?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return 0;
    break;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteObject(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Message, wParam, lParam);
}*/      
/*
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Message,
                              WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hBm;
  static HBITMAP bm;
  
  switch (Message)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 100, NULL);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    hBm = LoadImage(NULL, "cloackface.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    Ellipse(hMemDC, 0, 0, W / 2, H / 2);
    Ellipse(hMemDC, W / 2, H / 2, W, H);
    return 0;
  case WM_TIMER:

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_LBUTTONDOWN:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0; 
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteObject(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Message, wParam, lParam);
}                                */

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Message,
                              WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hclockBuf;
  static HBITMAP hclock;
  
  switch (Message)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hclock = (BITMAP)LoadImage(NULL, "cloackface.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    
    GetObject(clock, sizeof(BITMAP), &bm);
    SelectObject(hclock, hBm);

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_LBUTTONDOWN:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0; 
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteObject(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Message, wParam, lParam);
}