/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
	
****************************************************************************/
//
// file listview.cpp
// tried to make this somewhat generic isolates the listview interaction from the rest of the application
//
#include "stdafx.h"

extern void Add2Log(TCHAR *txt, BOOL bLogTime = TRUE);

// GLobal Variables
HWND				g_hwndLV = NULL;		// handle to the listview window
WNDPROC g_lpfnListView;

//flags to determine what key messages to log
BOOL fWM_KEYDOWN = TRUE;
BOOL fWM_KEYUP = TRUE;
BOOL fWM_CHAR = TRUE;
BOOL fWM_MOUSEMOVE = FALSE;
BOOL fWM_LBUTTONDOWN  = FALSE;
BOOL fWM_LBUTTONDBLCLK = FALSE;
BOOL fWM_LBUTTONUP = FALSE;
BOOL fWM_RBUTTONDOWN = FALSE;
BOOL fWM_RBUTTONUP = FALSE;
BOOL fWM_RBUTTONDBLCLK = FALSE;

BOOL fUSEGX = FALSE;

BOOL fUseLog = FALSE;

BOOL fUseAllKeys = FALSE;

enum KEYFLAGS{
	NONE=0,
	ALT=1,
	CTRL=2,
	SHIFT=4,
	CAP=8,
	NUM=16,
};

BYTE getKeyStates(){
	BYTE keyFlags = NONE;

	//SHORT		LMENU_keyState	=GetKeyState(VK_LMENU); //SHORT = two bytes
	//SHORT		RMENU_keyState	=GetKeyState(VK_RMENU);

	//SHORT		LSHIFT_keyState	=GetKeyState(VK_LSHIFT);
	//SHORT		RSHIFT_keyState	=GetKeyState(VK_RSHIFT);

	//SHORT		LCTRL_keyState	=GetKeyState(VK_LCONTROL);
	//SHORT		RCTRL_keyState	=GetKeyState(VK_RCONTROL);

	SHORT		MENU_keyState	=GetKeyState(VK_MENU);	//0xFFFE (11111110)=> pressed
	SHORT		SHIFT_keyState	=GetKeyState(VK_SHIFT); //0x0001 (00000001)=> toggled
	SHORT		CTRL_keyState	=GetKeyState(VK_CONTROL);
	SHORT		CAP_keyState	=GetKeyState(VK_CAPITAL);
	SHORT		NUM_keyState	=GetKeyState(VK_NUMLOCK);

	//NKDbgPrintfW(L"LMENU_keyState:  %i\n",   LMENU_keyState);
	//NKDbgPrintfW(L"RMENU_keyState:  %i\n",   RMENU_keyState);
	//NKDbgPrintfW(L"LSHIFT_keyState: %i\n",   LSHIFT_keyState);
	//NKDbgPrintfW(L"RSHIFT_keyState: %i\n",   RSHIFT_keyState);
	//NKDbgPrintfW(L"LCTRL_keyState:  %i\n",   LCTRL_keyState);
	//NKDbgPrintfW(L"RCTRL_keyState:  %i\n",   RCTRL_keyState);

	NKDbgPrintfW(L"MENU_keyState:  %i\n",   MENU_keyState);
	NKDbgPrintfW(L"SHIFT_keyState: %i\n",   SHIFT_keyState);
	NKDbgPrintfW(L"CTRL_keyState:  %i\n",   CTRL_keyState);
	NKDbgPrintfW(L"CAP_keyState:   %i\n",   CAP_keyState);
	NKDbgPrintfW(L"NUM_keyState:   %i\n",   NUM_keyState);

	/*
	If the high-order bit is 1, the key is down; otherwise, it is up.
	If the low-order bit is 1, the key is toggled. A key, such as the CAPS LOCK key, is toggled if it is turned on. 
	The key is off and untoggled if the low-order bit is 0. A toggle key's indicator light (if any) on the keyboard 
	will be on when the key is toggled, and off when the key is untoggled.
	*/
	const SHORT KEY_PRESSED_MASK = 0xFFFE; //if key is pressed mask => -1
	const SHORT KEY_TOGGLED_MASK = 0x0001; //if key is pressed mask => +1

	//BOOL bLMENU = LMENU_keyState & KEY_PRESSED_MASK;
	//BOOL bRMENU = RMENU_keyState & KEY_PRESSED_MASK;

	//BOOL bLSHIFT = LSHIFT_keyState & KEY_PRESSED_MASK;
	//BOOL bRSHIFT = RSHIFT_keyState & KEY_PRESSED_MASK;

	//BOOL bLCTRL = LCTRL_keyState & KEY_PRESSED_MASK;
	//BOOL bRCTRL = RCTRL_keyState & KEY_PRESSED_MASK;

	BOOL bMENU = (MENU_keyState & KEY_PRESSED_MASK) == KEY_PRESSED_MASK;
	BOOL bSHIFT = (SHIFT_keyState & KEY_PRESSED_MASK) == KEY_PRESSED_MASK;
	BOOL bCTRL = (CTRL_keyState & KEY_PRESSED_MASK) == KEY_PRESSED_MASK;

	BOOL bCAP, bNUM;
	(CAP_keyState==1 || CAP_keyState==-1)?bCAP=TRUE:bCAP=FALSE;
	(NUM_keyState==1 || NUM_keyState==-1)?bNUM=TRUE:bNUM=FALSE;
	//BOOL bCAP = (CAP_keyState & KEY_PRESSED_MASK) == KEY_PRESSED_MASK;
	//BOOL bNUM = (NUM_keyState & KEY_PRESSED_MASK) == KEY_PRESSED_MASK;

	//NKDbgPrintfW(L"LMENU %i\t", bLMENU);
	//NKDbgPrintfW(L"RMENU %i\t", bRMENU);
	//NKDbgPrintfW(L"LSHIFT %i\t", bLSHIFT);
	//NKDbgPrintfW(L"RSHIFT %i\t", bRSHIFT);
	//NKDbgPrintfW(L"LCTRL %i\t", bLCTRL);
	//NKDbgPrintfW(L"RCTRL %i\n", bRCTRL);

	NKDbgPrintfW(L"MENU  0x%04x\t", bMENU);
	NKDbgPrintfW(L"SHIFT 0x%04x\t", bSHIFT);
	NKDbgPrintfW(L"CTRL  0x%04x\t", bCTRL);
	NKDbgPrintfW(L"CAP   0x%04x\t", bCAP);
	NKDbgPrintfW(L"NUM   0x%04x\n", bNUM);

	if(bMENU)
		keyFlags|=ALT;
	if(bSHIFT)
		keyFlags|=SHIFT;
	if(bCTRL)
		keyFlags|=CTRL;
	if(bCTRL)
		keyFlags|=CTRL;
	if(bCAP)
		keyFlags|=CAP;

	return keyFlags;
}

BOOL ClearListView(){
	HWND		hwndLV = g_hwndLV;
	return ListView_DeleteAllItems(hwndLV);
}

// AddMessageToLV
//   adds an item to the listview g_hwndLV
//   the item will be a WM_KEYDOWN, WM_KEYUP, or WM_CHAR message.
//
BOOL AddMessageToLV(PTSTR szMsg, WPARAM wParam, LPARAM lParam, BOOL bCHAR, BYTE flags)
{
	LVITEM 		lvi;
	TCHAR		szOut[100];
	HWND		hwndLV = g_hwndLV;
	
	//
	// set up the LVITEM structure
	//
	memset(&lvi, 0, sizeof(LVITEM));
	
	lvi.mask = LVIF_TEXT | LVIF_STATE;

	//
	// in subitem 0 lives the message name
	//
	wsprintf(szOut, TEXT("%s"), szMsg);
	lvi.pszText		= szOut;  // we'll just reset szOut each time
	lvi.cchTextMax	= MAX_ITEMLEN;
	int iItem = ListView_InsertItem(g_hwndLV, &lvi);
	int iSubItem = 0;
	
	//log2file
	Add2Log(szOut, false);
	Add2Log(L"\t", false);

	if (iItem == -1)
		MessageBox(g_hwnd, TEXT("Listview Insert Failed"), TEXT("Insert"), MB_OK);
	
	//
	// in subitem 1 lives the wParam
	//
	iSubItem++;
	// looks nicer to convert the WM_CHAR messages
	if (!bCHAR)
		GetKeyName(wParam, szOut); //get the keyname
	else if (!lstrcmp(szMsg, TEXT("CHAR")))
		wsprintf(szOut, TEXT("%c(0x%02x)"), wParam, wParam);
	else 
		wsprintf(szOut, TEXT("%x"), wParam);
	
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, szOut);
	//log2file
	Add2Log(szOut, false);
	Add2Log(L"\t", false);
	
	//
	// in subitem 2 lives the lParam
	//
	iSubItem++;
	wsprintf(szOut, TEXT("%x"), lParam);
	//log2file
	Add2Log(szOut, false);
	//Add2Log(L"\r\n", false);
	
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, szOut);
	
	//
	// subItem 3 = ALT SHIFT CTRL
	//
	wsprintf(szOut, L"\t");
	iSubItem++;
	if((flags&ALT)==ALT)
		wcscat(szOut, TEXT("1"));
	else
		wcscat(szOut, TEXT("0"));
	wcscat(szOut, L"/");
	if((flags&SHIFT)==SHIFT)
		wcscat(szOut, TEXT("1"));
	else
		wcscat(szOut, TEXT("0"));
	wcscat(szOut, L"/");
	if((flags&CTRL)==CTRL)
		wcscat(szOut, TEXT("1"));
	else
		wcscat(szOut, TEXT("0"));
	wcscat(szOut, L"/");
	if((flags&CAP)==CAP)
		wcscat(szOut, TEXT("1"));
	else
		wcscat(szOut, TEXT("0"));
	wcscat(szOut, L"/");
	if((flags&NUM)==NUM)
		wcscat(szOut, TEXT("1"));
	else
		wcscat(szOut, TEXT("0"));

	//log2file
	Add2Log(szOut, false);
	Add2Log(L"\r\n", false);
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, szOut);

	//
	// it is good practice to ensure visible for all inserted items
	//
	ListView_EnsureVisible(hwndLV, lvi.iItem, FALSE);
	InvalidateRect(g_hwndLV, NULL, TRUE);
	UpdateWindow(g_hwndLV);

	//
	// don't run out of space in the listview
	//
	int iCnt = ListView_GetItemCount(g_hwndLV);
	if (iCnt > 200)
		for (int iDelete = iCnt; iDelete > 100; iDelete--)
			ListView_DeleteItem(g_hwndLV, iDelete);

	return TRUE;
}

//
// Handle Input Messages
//
BOOL HandleInputMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg) 
	{
	case WM_SYSKEYDOWN:
		if (fWM_KEYDOWN) return AddMessageToLV(TEXT("SYSKEYDOWN"), wParam, lParam, FALSE, getKeyStates());
		return FALSE;
	case WM_SYSKEYUP:
		if (fWM_KEYDOWN) return AddMessageToLV(TEXT("SYSKEYDOWN"), wParam, lParam, FALSE, getKeyStates());
		return FALSE;
	case WM_KEYDOWN:
		if (fWM_KEYDOWN) return AddMessageToLV(TEXT("KEYDOWN"), wParam, lParam, FALSE, getKeyStates());
		return FALSE;
	case WM_KEYUP:
		if (fWM_KEYUP) return AddMessageToLV(TEXT("KEYUP"), wParam, lParam, FALSE, getKeyStates());
		return FALSE;
	case WM_CHAR:
		if (fWM_CHAR) return AddMessageToLV(TEXT("CHAR"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_MOUSEMOVE:
		if (fWM_MOUSEMOVE) return AddMessageToLV(TEXT("MOUSEMOVE"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_LBUTTONDOWN:
		if (fWM_LBUTTONDOWN) return AddMessageToLV(TEXT("LDOWN"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_LBUTTONDBLCLK:
		if (fWM_LBUTTONDBLCLK) return AddMessageToLV(TEXT("LDBL"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_LBUTTONUP:
		if (fWM_LBUTTONUP) return AddMessageToLV(TEXT("LUP"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_RBUTTONDOWN:
		if (fWM_RBUTTONDOWN) return AddMessageToLV(TEXT("RDOWN"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_RBUTTONUP:
		if (fWM_RBUTTONUP) return AddMessageToLV(TEXT("RUP"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	case WM_RBUTTONDBLCLK:
		if (fWM_RBUTTONDBLCLK) return AddMessageToLV(TEXT("RDBL"), wParam, lParam, TRUE, getKeyStates());
		return FALSE;
	}
	return FALSE;
}
//
// dialog proc for the listview
//  being a dialog procedure, return TRUE for messages handled
//
LRESULT CALLBACK ListviewProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (HandleInputMessages(msg, wParam, lParam))
		return TRUE;
	
	switch (msg)
	{
	case WM_SETFOCUS:
		// set the focus back to the the control losing the focus
		SetFocus(g_hwnd);
		return 0;
		
	default:
		return CallWindowProc((WNDPROC)g_lpfnListView, hwnd, msg, wParam, lParam);
	}
	
	return 0;
}

//
// create the listview and resize it to available screen size
// when bCreating is false, destroy the listview
//
HWND CreateListview(HWND hwndParent, BOOL bCreating)
{
	LVCOLUMN 	lvc;
	TCHAR		szOut[100];
	INT			iRet;
	HWND 		hwndLV = g_hwndLV;
	RECT		rc;
	
	// get rid of old one to avoid a leak
	if (hwndLV)
	{
		ShowWindow(hwndLV, SW_HIDE);
		DestroyWindow(hwndLV);
		hwndLV = NULL;
	}
	
	if (bCreating)
	{
		GetClientRect(hwndParent, &rc);
		
		// create the listview
		// it is a child of the main window in report view which the user cannot sort
		hwndLV = CreateWindow(WC_LISTVIEW, TEXT("ListItem"), 
			WS_CHILD | LVS_EDITLABELS | LVS_REPORT | LVS_NOSORTHEADER | WS_VISIBLE | WS_HSCROLL, 
			0, 0, rc.right, rc.bottom - MENU_HEIGHT, 
			hwndParent, NULL, g_hinst, NULL); 
		
		
		if (NULL == hwndLV) 
			return NULL; 
		
		// setup headers
		lvc.mask		= LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		lvc.fmt			= 0;
		lvc.cx			= 75;
		lvc.cchTextMax	= 0;
		lvc.iSubItem	= 0;
		
		lvc.pszText		= szOut;
		lvc.iImage		= 0;
		lvc.iOrder		= 0;
		
		// need to add columns in order
		
		// add column for message
		wsprintf(szOut, TEXT("Message"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);
		
		// add column for wParam
		lvc.iSubItem++;
		wsprintf(szOut, TEXT("wParam"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);
		
		// add column for lParam
		lvc.iSubItem++;
		wsprintf(szOut, TEXT("lParam"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);
		
		// add column for lParam
		lvc.iSubItem++;
		wsprintf(szOut, TEXT("ALT/SHFT/CTRL/CAP"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);

		// Subclass the list view so that we can set the focus back to
		// the process list view if the user should select anything in the
		// thread list view.
		g_lpfnListView = (WNDPROC)SetWindowLong(hwndLV,GWL_WNDPROC,(LONG)ListviewProc);
		
		
	}
	
	// this return value should be used to set g_hwndLV
	return hwndLV;
}

