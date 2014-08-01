#include <windows.h>
 
#ifndef VK_MEDIA_NEXT_TRACK
#define VK_MEDIA_NEXT_TRACK	0xB0
#endif
#ifndef VK_MEDIA_PREV_TRACK
#define VK_MEDIA_PREV_TRACK	0xB1
#endif
#ifndef VK_MEDIA_STOP
#define VK_MEDIA_STOP	0xB2
#endif
#ifndef VK_MEDIA_PLAY_PAUSE
#define VK_MEDIA_PLAY_PAUSE	0xB3
#endif
 
/**
 * 2011, zaak404@gmail.com
 */
 
HINSTANCE hInst;
TCHAR szTitle[] = "ATKMEDIA";
TCHAR szWindowClass[] = "ATKMEDIA";
 
ATOM MRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
//int main(int argc, char** argv)
//{
//	HINSTANCE hInstance = 0;
//    HINSTANCE hPrevInstance = 0;
//    LPTSTR    lpCmdLine = 0;
//    int       nCmdShow = SW_SHOWNORMAL;
 
	MSG msg;
 
	MRegisterClass(hInstance);
 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
 
	return (int) msg.wParam;
}
 
ATOM MRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
 
	wcex.cbSize = sizeof(WNDCLASSEX);
 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= 0;
	wcex.hbrBackground	= 0;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= 0;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
 
	return RegisterClassEx(&wcex);
}
 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
 
   hInst = hInstance; // Store instance handle in our global variable
 
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
 
   if (!hWnd)
   {
      return FALSE;
   }
 
   //ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);
 
   return TRUE;
}
 
#define ATKMEDIA_MESSAGE				  0x0917
#define ATKMEDIA_PLAY                     0x0002
#define ATKMEDIA_STOP                     0x0003
#define ATKMEDIA_PREV                     0x0005
#define ATKMEDIA_NEXT                     0x0004
 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
 
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
 
		switch (wmId)
		{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
 
		case ATKMEDIA_MESSAGE:
 
			switch(wmEvent)
			{
			case ATKMEDIA_PLAY:
				keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);
				break;
			case ATKMEDIA_STOP:
				keybd_event(VK_MEDIA_STOP, 0, 0, 0);
				break;
			case ATKMEDIA_NEXT:
				keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0);
				break;
			case ATKMEDIA_PREV:
				keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0);
				break;
			}
 
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
