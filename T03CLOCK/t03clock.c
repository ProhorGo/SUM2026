/* FILE NAME: t03clock.c
 * PROGRAMMER: VG4
 * DATE: 02.06.2026
 * PURPOSE: Arrows drawing.
 */

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* PI constant */
#define PI 3.14159265358979323846

/* Main window class name */
#define WND_CLASS_NAME "My SummerPractice Class Name"

/* Forward declaration */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  HWND hWnd;
  WNDCLASS wc;
  MSG msg;

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd = CreateWindow(WND_CLASS_NAME, "CGSG'SummerPractice'2026::Arrows", WS_OVERLAPPEDWINDOW,
    2560 * 1, 0, 1920, 1000,
    /* CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, */
    NULL, NULL, hInstance, NULL);

  /* ѕоказать и перерисовать окно */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* ÷икл обработки сообщений, пока не будет получено сообщение 'WM_QUIT' */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
} /* End of 'WinMain' function */

/* Arrow draw function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 *   - arrow draw angle:
 *       DOUBLE Angle;
 *   - arror center point coordinates:
 *       INT Xc, Yc;
 *   - arrow sizes:
 *       INT L, W;
 * RETURNS: None.
 */
VOID DrawArrow( HDC hDC, DOUBLE Alpha, INT Xc, INT Yc, INT L, INT W )
{
  INT i;
  POINT
    pts[] = {{0, 0}, {-W, W}, {0, L}, {W, W}},
    pts_res[sizeof(pts) / sizeof(pts[0])];
  INT N = sizeof(pts) / sizeof(pts[0]);

  for (i = 0; i < N; i++)
  {
    pts_res[i].x = Xc + (INT)(pts[i].x * cos(Alpha) + pts[i].y * sin(Alpha));
    pts_res[i].y = Yc + (INT)(pts[i].x * sin(Alpha) - pts[i].y * cos(Alpha));
  }
  Polygon(hDC, pts_res, N);
} /* End of 'DrawArrow' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  INT x, y;
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  DOUBLE t;
  BITMAP bm;
  CHAR Buf[102];
  HFONT hFnt, hOldFnt;
  RECT rc;
  SYSTEMTIME st;
  static INT W, H, Mode = 0;
  static HBITMAP hBm, hBmClockface;
  static HDC hMemDC, hMemDCClockface;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCClockface = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;

    hBmClockface = LoadImage(NULL, "cat.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(hMemDCClockface, hBmClockface);

    Rectangle(hMemDCClockface, 10, 10, 300, 20);
    return 0;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDC, RGB(0, 255, 0));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));

    /* Clear frame */
    Rectangle(hMemDC, 0, 0, W, H);

    /* Draw clockface */
    GetObject(hBmClockface, sizeof(bm), &bm);
    BitBlt(hMemDC, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight, hMemDCClockface, 0, 0, SRCCOPY);

    /* SetStretchBltMode(hMemDC, COLORONCOLOR); */
    /* StretchBlt(hMemDC, 0, 0, W, H, hMemDCClockface, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); */

    GetLocalTime(&st);

    DrawArrow(hMemDC, (st.wHour % 12) * 2 * PI / 12, W / 2, H / 2, 47, 18);
    DrawArrow(hMemDC, st.wMinute * 2 * PI / 60, W / 2, H / 2, 147, 18);
    DrawArrow(hMemDC, st.wSecond * 2 * PI / 60, W / 2, H / 2, 200, 18);
    SetDCPenColor(hMemDC, RGB(255, 0, 0));
    SetDCBrushColor(hMemDC, RGB(255, 0, 0));
    DrawArrow(hMemDC, (st.wSecond + st.wMilliseconds / 1000.0) * 2 * PI / 60, W / 2, H / 2, 220, 8);

    t = 0;

    y = (W > H ? H : W) / 8;
    hFnt =
      CreateFont(y, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, RUSSIAN_CHARSET,
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
        VARIABLE_PITCH | FF_SWISS, "");
    hOldFnt = SelectObject(hMemDC, hFnt);

    SetBkColor(hMemDC, RGB(220, 220, 180));
    SetBkMode(hMemDC, TRANSPARENT);
    SetTextColor(hMemDC, RGB(0, 0, 0));
    for (y = H / 2 - 1; y <= H / 2 + 1; y++)
      for (x = 300 - 1; x <= 300 + 1; x++)
        TextOut(hMemDC, x, y, Buf, sprintf(Buf, ">>> WiIO %d x %d ::врем€: %.3f <<<", W, H, t));
    SetTextColor(hMemDC, RGB(255, 255, 255));
    TextOut(hMemDC, 300, H / 2, Buf, sprintf(Buf, ">>> WiIO %d x %d ::врем€: %.3f <<<", W, H, t));

    rc.left = 0;
    rc.top = 0;
    rc.right = W;
    rc.bottom = H;
    SetTextColor(hMemDC, RGB(0, 0, 0));
    DrawText(hMemDC, Buf, sprintf(Buf, ">>> time <<<", 1, 2, 3),
      &rc, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);


    SelectObject(hMemDC, hOldFnt);
    DeleteObject(hFnt);

    hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_KEYDOWN:
    if (wParam == '1')
      Mode = 0;
    else if (wParam == '2')
      Mode = 1;
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure exit?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
      break;
    return 0;
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 't03clock.c' FILE */
