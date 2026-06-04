/* FILE NAME: t02arrow.c
 * PROGRAMMER: VG4
 * DATE: 02.06.2026
 * PURPOSE: Arrows drawing.
 */

#include <windows.h>
#include <time.h>
#include <math.h>

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
 *   - mouse cursor position in window coordinate system:
 *       POINT *Ms;
 *   - arror center point coordinates:
 *       INT Xc, Yc;
 *   - arrow sizes:
 *       INT L, W;
 * RETURNS: None.
 */
VOID DrawArrow( HDC hDC, POINT *Ms, INT Xc, INT Yc, INT L, INT W )
{
  INT
    i,
    dx = Ms->x - Xc,
    dy = Ms->y - Yc;
  DOUBLE
    len = sqrt(dx * dx + dy * dy),
    sine = dy / len,
    cosine = dx / len,
    alpha = atan2(-cosine, sine);
  INT x = Xc + (INT)(dx * L / len), y = Yc + (INT)(dy * L / len);
  POINT
    pts[] = {{0, 0}, {-W, W}, {0, L}, {W, W}},
    pts_res[sizeof(pts) / sizeof(pts[0])];
  INT N = sizeof(pts) / sizeof(pts[0]);


  for (i = 0; i < N; i++)
  {
    pts_res[i].x = Xc + (INT)(pts[i].x * cos(alpha) - pts[i].y * sin(alpha));
    pts_res[i].y = Yc + (INT)(pts[i].x * sin(alpha) + pts[i].y * cos(alpha));
  }

  Polygon(hDC, pts_res, N);

  MoveToEx(hDC, Xc, Yc, NULL);
  LineTo(hDC, x, y);
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
  static INT W, H, Mode = 0;
  static HBITMAP hBm;
  static HDC hMemDC;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;
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
    Rectangle(hMemDC, 0, 0, W, H);

    t = 8 * (DOUBLE)clock() / CLOCKS_PER_SEC;
    pt.x = W / 2 + (INT)(sin(t) * W / 2);
    pt.y = H / 2 + (INT)(sin(2 * t) * H / 2);
    ClientToScreen(hWnd, &pt);
    SetCursorPos(pt.x, pt.y);


    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    if (Mode == 0)
    {
      srand(30);
      for (y = 0; y < 300; y++)
      {
        SetDCPenColor(hMemDC, RGB(rand() & 255, rand() & 255, rand() & 255));
        SetDCBrushColor(hMemDC, RGB(rand() & 255, rand() & 255, rand() & 255));
        DrawArrow(hMemDC, &pt, rand() % W, rand() % H, 147, 18);
      }
    }
    else if (Mode == 1)
    {
      srand(30);
      SetDCPenColor(hMemDC, RGB(rand() & 255, rand() & 255, rand() & 255));
      SetDCBrushColor(hMemDC, RGB(rand() & 255, rand() & 255, rand() & 255));
      for (y = 0; y < H; y += 1 + 30)
        for (x = 0; x < W; x += 1 + 30)
          DrawArrow(hMemDC, &pt, x, y, 47, 8);
    }

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

/* END OF 't02arrow.c' FILE */
