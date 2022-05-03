// UNTITLED.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

//indexes of the entry menu buttons
#define IDB_Start_Btn 1
#define IDB_Exit_Btn 2
#define IDB_Title_Btn 3
#define IDB_About_Btn 4
#define IDB_Rules_Btn 5

// Global Variables:
bool Drawing_Active = false;
Head_Engine Engine;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	Common::Setup_Colors();

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_UNTITLED, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_UNTITLED));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UNTITLED));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = Common::BG_Brush;//17, 46, 37
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_UNTITLED);//NULL
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	//Creation of the main window rectangle
	RECT window_rect;
	window_rect.left = 0;
	window_rect.top = 0;
	window_rect.right = 621;
	window_rect.bottom = 585;

	//Relaying current window to the size we need to
	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, TRUE);

	//Creation of the main window
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		0, 0, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, 0, 0, hInstance, 0);

	if (hWnd == 0)
		return FALSE;

	//Engine initialization
	Engine.Init_Engine(hWnd);

	///////////////////////////////////// ENTRY BUTTONS /////////////////////////////////////////////

	HWND Start_Btn = CreateWindow( 
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"START",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		265,         // x position 
		250,         // y position 
		90,        // Button width
		40,        // Button height
		hWnd,     // Parent window
		(HMENU)IDB_Start_Btn,       // Menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	HWND Exit_Btn = CreateWindow(L"BUTTON", L"EXIT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
		265, 400, 90, 40, hWnd, (HMENU)IDB_Exit_Btn, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	HWND About_Btn = CreateWindow(L"BUTTON", L"ABOUT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
		265, 350, 90, 40, hWnd, (HMENU)IDB_About_Btn, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	HWND Rules_Btn = CreateWindow(L"BUTTON", L"RULES", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		265, 300, 90, 40, hWnd, (HMENU)IDB_Rules_Btn, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	HWND Title_Btn = CreateWindow(L"BUTTON", L"UNTITLED", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 
		265, 200, 90, 40, hWnd, (HMENU)IDB_Title_Btn, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDB_Start_Btn:
			Drawing_Active = true;
			ShowWindow(GetDlgItem(hWnd, 1), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, 2), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, 3), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, 4), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, 5), SW_HIDE);
			break;
		case IDB_Exit_Btn:
			DestroyWindow(hWnd);
			break;
		case IDB_About_Btn:

			BeginPaint(hWnd, nullptr);

			MessageBox(NULL, L"This program was made by Yevgeny Dobrovolskiy.\nStudent of PPK, speciality 121 \"Software Engineering\"\nUNTITLED, Version 1.0 \nCopyright (c) 2022",
				L"About", MB_ICONINFORMATION | MB_OK);

			InvalidateRect(hWnd, NULL, FALSE);

			EndPaint(hWnd, nullptr);
			UpdateWindow(hWnd);
			break;
		case IDB_Rules_Btn:

			BeginPaint(hWnd, nullptr);

			MessageBox(NULL, L"To start the game, you need to click on the \"Start\" button\nThe control is carried out with the keys 'A' and 'D', \nwhen they are pressed, the platform moves left / right. \nWhen you press the spacebar, the ball shoots. \nIt can be reflected from walls and blocks. \nBlocks can collapse and out of them there are different bonuses.\nIf the ball flew out of the platform, then the game ends.",
				L"Rules", MB_ICONINFORMATION | MB_OK);

			InvalidateRect(hWnd, NULL, FALSE);

			EndPaint(hWnd, nullptr);
			UpdateWindow(hWnd);
			break;
		default:
			UpdateWindow(hWnd);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;


	case WM_PAINT:
	{
		if(Drawing_Active){
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...		

			//////////		THAT THING IS DEFINITELY MAIMED		//////////

			if (Engine.Game_Done == true) {
				Engine.Draw_Ending(hdc, ps.rcPaint);
				InvalidateRect(hWnd, NULL, FALSE);
				UpdateWindow(hWnd);
				Sleep(7000);
				DestroyWindow(hWnd);
			}
			else if (Engine.Game_Over == true) {
				Engine.Draw_GameOver(hdc, ps.rcPaint);
				InvalidateRect(hWnd, NULL, FALSE);
				UpdateWindow(hWnd);
				Sleep(7000);
				DestroyWindow(hWnd);
			}
			else Engine.Draw_Frame(hdc, ps.rcPaint);

			//////////////////////////////////////////////////////////////

			EndPaint(hWnd, &ps);
			ReleaseDC(hWnd, hdc);
		}
	}
	break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			return Engine.On_Key(KT_Left, NULL, hWnd, true);
			break;
		case VK_RIGHT:
			return Engine.On_Key(KT_Right, NULL, hWnd, true);
			break;
		case VK_SPACE:
			return Engine.On_Key(KT_Space, NULL, hWnd, true);
			break;
		case VK_ESCAPE:
			return Engine.On_Key(KT_Escape, NULL, hWnd, true);
			break;
		case 0x41:
			return Engine.On_Key(KT_None, Button_A, hWnd, true);
			break;
		case 0x44:
			return Engine.On_Key(KT_None, Button_D, hWnd, true);
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam) {
		case VK_LEFT:
			return Engine.On_Key(KT_Left, NULL, hWnd, false);
			break;
		case VK_RIGHT:
			return Engine.On_Key(KT_Right, NULL, hWnd, false);
			break;
		case VK_SPACE:
			return Engine.On_Key(KT_Space, NULL, hWnd, false);
			break;
		case VK_ESCAPE:
			return Engine.On_Key(KT_Escape, NULL, hWnd, false);
			break;
		case 0x41:
			return Engine.On_Key(KT_None, Button_A, hWnd, false);
			break;
		case 0x44:
			return Engine.On_Key(KT_None, Button_D, hWnd, false);
			break;
		}
		break;
	case WM_CREATE:
		/*HBITMAP hImage = (HBITMAP)LoadImage(NULL, L"guibg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HWND hImageView = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 00, 500, 600, hWnd, (HMENU)IMAGE_VIEW, GetModuleHandle(NULL), NULL);
		SendMessage(hImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);*/
		break;

	case WM_TIMER:
		if (wParam == Timer_ID)
			return Engine.On_Timer();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
