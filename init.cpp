/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
	This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
	
****************************************************************************/
//
// init.cpp
// handles the creation logic and should be shared from project to project as much as possible
//
#include "stdafx.h"

#include "Commctrl.h"
#pragma comment (lib, "Commctrl.lib")

#ifdef WIN32_PLATFORM_PSPC
	//#define USEGAPI
	#include <gx.h>
	#pragma comment (lib, "gx.lib")
#endif

#ifdef USEGAPI
	#include ".\wm5\gx.h"
	#pragma comment (lib, ".\\wm5\\gx.lib")
//GAPI
extern GXKeyList g_gxkl;				// GX struct
#endif

extern int newfile(TCHAR *filename);

//
// globals initialized by init.cpp
//
HWND			g_hwndCB 			= NULL;
HWND 			g_hwnd 				= NULL;
HINSTANCE 		g_hinst				= NULL;

// start hibernated forces the commandbar to be created during WM_ACTIVATE message
BOOL			g_bHibernated		= TRUE; // starting hibernated

//
// MyRegisterClass
// common operation to register a basic class with only a class name being different
//
ATOM MyRegisterClass(LPTSTR szClassName)
{
	WNDCLASS wc;
	
    wc.style			= 0;
    wc.lpfnWndProc		= (WNDPROC) MainWndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= g_hinst;
    wc.hIcon			= LoadIcon(g_hinst, MAKEINTRESOURCE(IDI_ICON));
    wc.hCursor			= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szClassName;
	
	return RegisterClass(&wc);
}

//
// MainWndProc
// Window Procedure for application window with menu
//
BOOL CALLBACK MainWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HandleInputMessages(msg, wParam, lParam);
	
	switch (msg)
	{
	case WM_CREATE:
		g_hwndCB = CreateMenuBar(hwnd, g_hwndCB, TRUE);
		
		// if a menubar is present
		{
			RECT rc;
			GetWindowRect(hwnd, &rc);
			rc.bottom -= MENU_HEIGHT;
			if (g_hwndCB)
				MoveWindow(hwnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
		}
		g_hwndLV = CreateListview(hwnd, TRUE);
		MessageBox(hwnd, L"Please select the message(s) you would like to track", L"Open File menu first!", MB_OK);
		
		break;
		
	case WM_COMMAND:
		// HandleCommand returns FALSE when handled
		if (HandleCommand(hwnd, wParam, lParam))
			return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
		
	case WM_HOTKEY:
		SetForegroundWindow(hwnd);
		AddMessageToLV(TEXT("HOTKEY"), wParam, lParam, FALSE, getKeyStates());
		break;
		
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
		
	case WM_DESTROY:
#ifdef USEGAPI
		GXCloseInput();	
#endif
		PostQuitMessage(0);
		break;
		
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	return 0;
}

// 
// Are we running?
//  this may need to be expanded to use a named mutex depending on the criticalness of you initialization code
// 
HWND AreWeRunning(LPCTSTR szClassName)
{
	return FindWindow(szClassName, NULL);
}

//
// Init Instance function
//
BOOL InitInstance (int CmdShow, LPTSTR szWindowName, LPTSTR szClassName)
{
	//
	//Ensures that the InkControl common control dynamic-link library (DLL) is loaded. 
	// load listview interface
	//
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof (INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);
	
	
	//
	// create the class and window
	//   the main window is always full screen - only the child windows resize
	//
	MyRegisterClass(szClassName);
	g_hwnd = CreateWindow(szClassName, szWindowName, 
						  WS_VISIBLE,
						  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
						  NULL, NULL, g_hinst, NULL);
	
	
	if (!g_hwnd)	
		return FALSE;
/*
#ifdef USEGAPI
	//GAPI init
	int iRet;
	iRet = GXOpenInput();
	g_gxkl = GXGetDefaultKeys(GX_NORMALKEYS);
#endif
*/
	return TRUE;
}


//
// WinMain
//
int WINAPI WinMain(HINSTANCE 	hInstance,
                   HINSTANCE 	hPrevInstance,
                   LPWSTR     	lpCmdLine,
                   int        	CmdShow)
{
	MSG 	msg;
	HWND 	hwndOld = NULL;	
	TCHAR	szClassName[MAX_LOADSTRING];			// class name
	TCHAR	szWindowName[MAX_LOADSTRING];			// window name
	
	g_hinst = hInstance;
	
	LoadString(g_hinst, IDS_CLASSNAME,	 szClassName, 	MAX_LOADSTRING);
	LoadString(g_hinst, IDS_WINDOWNAME,	 szWindowName, 	MAX_LOADSTRING);
	
	if (hwndOld = AreWeRunning(szClassName))
	{
		SetForegroundWindow(hwndOld);    
		return 0;
	}
	
	//
	// no we are not running
	//  initialize the controls and create the main window
	//
	if (!InitInstance(CmdShow, szWindowName, szClassName))
	{
		return (FALSE);
	}
	
	//
	// message loop
	//
	while (GetMessage(&msg, NULL, 0,0) == TRUE)
	{
		// å =
		// PeekMessage: msg=0x100, wP=0x0000000c, lP=0x00000001
		// PeekMessage: msg=0x102, wP=0x000000e5, lP=0x00000001
		// PeekMessage: msg=0x101, wP=0x0000000c, lP=0xc0000001

		DEBUGMSG(1, (L"GetMessage::PeekMessage:          msg=0x%0x, wP=0x%08x, lP=0x%08x\r\n", msg.message, msg.wParam, msg.lParam));
		TranslateMessage (&msg);
		DEBUGMSG(1, (L"   TranslateMessage::PeekMessage: msg=0x%0x, wP=0x%08x, lP=0x%08x\r\n", msg.message, msg.wParam, msg.lParam));
		DispatchMessage (&msg);
	}
/*
GetMessage::PeekMessage:          msg=0x100, wP=0x0000000c, lP=0x00000001
   TranslateMessage::PeekMessage: msg=0x100, wP=0x0000000c, lP=0x00000001

GetMessage::PeekMessage:          msg=0x102, wP=0x000000c5, lP=0x00000001
   TranslateMessage::PeekMessage: msg=0x102, wP=0x000000c5, lP=0x00000001

GetMessage::PeekMessage:          msg=0x101, wP=0x0000000c, lP=0x80000001
   TranslateMessage::PeekMessage: msg=0x101, wP=0x0000000c, lP=0x80000001
*/
	
	return (msg.wParam);
}

