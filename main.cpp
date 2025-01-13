#include <windows.h>
#include "Cube.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

std::vector <Cube*> cubes;

VOID OnPaint(HDC hdc){
   Gdiplus::Graphics graphics(hdc);
   graphics.SetSmoothingMode(Gdiplus::SmoothingModeNone);
   for (int i = 0; i < cubes.size(); i++){
      cubes[i]->render(graphics);
      cubes[i]->spin(5);
   }
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR argument, INT iCmdShow)
{
   AllocConsole();
   freopen("CONOUT$", "w", stdout);
   HWND                          hWnd;
   MSG                           msg;
   WNDCLASS                      wndClass;
   Gdiplus::GdiplusStartupInput  gdiplusStartupInput;
   ULONG_PTR                     gdiplusToken;

   // Initialize GDI+.
   Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");

   RegisterClass(&wndClass);

   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Rotating Cube"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters


   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   FreeConsole();
   for (int i = 0; i < cubes.size(); i++){
      delete cubes[i];
   }
   Gdiplus::GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;

   switch(message)
   {
   case WM_PAINT:{
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);

      EndPaint(hWnd, &ps);
      return 0;
   }
   case WM_CREATE:
      SetTimer(hWnd, 1, 8, NULL); // Timer with 16 ms interval
      return 0;

   // Handle the timer
   case WM_TIMER:
      InvalidateRect(hWnd, NULL, TRUE); // Trigger repaint
      return 0;

   case WM_LBUTTONDOWN: {
      // Extract x and y coordinates from lParam
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      Cube* cube = new Cube(Gdiplus::PointF(x, y));
      cubes.push_back(cube);
   }

      return 0;

   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
      
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc