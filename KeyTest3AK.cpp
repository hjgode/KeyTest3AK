/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
    
****************************************************************************/
//
// KeyTest3AK.cpp : Defines the entry point for the application
//
#include "stdafx.h"
#include "log2file.h"
#include "registerHotkeys.h"

#ifdef WIN32_PLATFORM_PSPC
	#define USEGAPI
#endif
#ifdef _WIN32_WCE
	#undef USEGAPI
#endif

#ifdef USEGAPI
	#include ".\wm5\gx.h"
	#pragma comment (lib, ".\\wm5\\gx.lib")
//GAPI
GXKeyList g_gxkl;				// GX struct
#endif

//
// globals
//
BOOL g_bHaveButtons = FALSE;


//
// GetKeyName
//   this is just a look up function for all the possible VK codes
//
void GetKeyName(WPARAM wParam, PTSTR szOut)
{
	/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
	/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */
	if(wParam>=0x30 && wParam<=0x5A){
		wsprintf(szOut, L"VK_%c", wParam);
		return;
	}
	switch (wParam)
	{
	case VK_LBUTTON:
		wsprintf(szOut, TEXT("VK_LBUTTON 0x%0x"), wParam);
		break;
	case VK_RBUTTON:
		wsprintf(szOut, TEXT("VK_RBUTTON 0x%02x"), wParam);
		break;
	case VK_CANCEL :
		wsprintf(szOut, TEXT("VK_CANCEL 0x%02x"), wParam);
		break;
	case VK_MBUTTON:
		wsprintf(szOut, TEXT("VK_MBUTTON 0x%02x"), wParam);
		break;
	case VK_KANA		:
		wsprintf(szOut, TEXT("VK_KANA 0x%02x"), wParam);
		break;
	case VK_KANJI	:
		wsprintf(szOut, TEXT("VK_KANJI	 0x%02x"), wParam);
		break;
	case VK_CONVERT	 :
		wsprintf(szOut, TEXT("VK_CONVERT 0x%02x"), wParam);
		break;
	case VK_NOCONVERT	:
		wsprintf(szOut, TEXT("VK_NOCONVERT 0x%02x"), wParam);
		break;
		//case VK_EXTEND_BSLASH:
	case VK_OEM_102:
		wsprintf(szOut, TEXT("VK_EXTEND_BSLASH 0x%02x"), wParam);
		break;
	case VK_ADD:
		wsprintf(szOut, TEXT("VK_ADD 0x%02x"), wParam);
		break;
	case VK_APOSTROPHE		:
		wsprintf(szOut, TEXT("VK_APOSTROPHE 0x%02x"), wParam);
		break;
	case VK_APPS :
		wsprintf(szOut, TEXT("VK_APPS 0x%02x"), wParam);
		break;
	case VK_ATTN :
		wsprintf(szOut, TEXT("VK_ATTN 0x%02x"), wParam);
		break;
	case VK_BACK :
		wsprintf(szOut, TEXT("VK_BACK 0x%02x"), wParam);
		break;
	case VK_BACKQUOTE		:
		wsprintf(szOut, TEXT("VK_BACKQUOTE 0x%02x"), wParam);
		break;
	case VK_BACKSLASH		:
		wsprintf(szOut, TEXT("VK_BACKSLASH 0x%02x"), wParam);
		break;
	case VK_CAPITAL:
		wsprintf(szOut, TEXT("VK_CAPITAL 0x%02x"), wParam);
		break;
	case VK_CLEAR:
		wsprintf(szOut, TEXT("VK_CLEAR 0x%02x"), wParam);
		break;
	case VK_COMMA			:
		wsprintf(szOut, TEXT("VK_COMMA 0x%02x"), wParam);
		break;
	case VK_CONTROL:
		wsprintf(szOut, TEXT("VK_CONTROL 0x%02x"), wParam);
		break;
	case VK_CRSEL:
		wsprintf(szOut, TEXT("VK_CRSEL 0x%02x"), wParam);
		break;
		// some VK codes are repeated.
#if 0
	case VK_DBE_ALPHANUMERIC:
		wsprintf(szOut, TEXT("VK_DBE_ALPHANUMERIC 0x%02x"), wParam);
		break;
	case VK_DBE_CODEINPUT :
		wsprintf(szOut, TEXT("VK_DBE_CODEINPUT 0x%02x"), wParam);
		break;
	case VK_DBE_DBCSCHAR:
		wsprintf(szOut, TEXT("VK_DBE_DBCSCHAR 0x%02x"), wParam);
		break;
	case VK_DBE_DETERMINESTRING :
		wsprintf(szOut, TEXT("VK_DBE_DETERMINESTRING 0x%02x"), wParam);
		break;
	case VK_DBE_ENTERDLGCONVERSIONMODE:
		wsprintf(szOut, TEXT("VK_DBE_ENTERDLGCONVERSIONMODE 0x%02x"), wParam);
		break;
	case VK_DBE_ENTERIMECONFIGMODE:
		wsprintf(szOut, TEXT("VK_DBE_ENTERIMECONFIGMODE 0x%02x"), wParam);
		break;
	case VK_DBE_ENTERWORDREGISTERMODE :
		wsprintf(szOut, TEXT("VK_DBE_ENTERWORDREGISTERMODE 0x%02x"), wParam);
		break;
	case VK_DBE_FLUSHSTRING :
		wsprintf(szOut, TEXT("VK_DBE_FLUSHSTRING 0x%02x"), wParam);
		break;
	case VK_DBE_HIRAGANA:
		wsprintf(szOut, TEXT("VK_DBE_HIRAGANA 0x%02x"), wParam);
		break;
	case VK_DBE_KATAKANA:
		wsprintf(szOut, TEXT("VK_DBE_KATAKANA 0x%02x"), wParam);
		break;
	case VK_DBE_NOCODEINPUT :
		wsprintf(szOut, TEXT("VK_DBE_NOCODEINPUT 0x%02x"), wParam);
		break;
	case VK_DBE_NOROMAN :
		wsprintf(szOut, TEXT("VK_DBE_NOROMAN 0x%02x"), wParam);
		break;
	case VK_DBE_ROMAN :
		wsprintf(szOut, TEXT("VK_DBE_ROMAN 0x%02x"), wParam);
		break;
	case VK_DBE_SBCSCHAR:
		wsprintf(szOut, TEXT("VK_DBE_SBCSCHAR 0x%02x"), wParam);
		break;
#endif
	case VK_DECIMAL:
		wsprintf(szOut, TEXT("VK_DECIMAL 0x%02x"), wParam);
		break;
	case VK_DELETE :
		wsprintf(szOut, TEXT("VK_DELETE 0x%02x"), wParam);
		break;
	case VK_DIVIDE :
		wsprintf(szOut, TEXT("VK_DIVIDE 0x%02x"), wParam);
		break;
	case VK_DOWN :
		wsprintf(szOut, TEXT("VK_DOWN 0x%02x"), wParam);
		break;
	case VK_END:
		wsprintf(szOut, TEXT("VK_END 0x%02x"), wParam);
		break;
	case VK_EQUAL			:
		wsprintf(szOut, TEXT("VK_EQUAL 0x%02x"), wParam);
		break;
	case VK_EREOF:
		wsprintf(szOut, TEXT("VK_EREOF 0x%02x"), wParam);
		break;
	case VK_ESCAPE :
		wsprintf(szOut, TEXT("VK_ESCAPE 0x%02x"), wParam);
		break;
	case VK_EXECUTE:
		wsprintf(szOut, TEXT("VK_EXECUTE 0x%02x"), wParam);
		break;
	case VK_EXSEL:
		wsprintf(szOut, TEXT("VK_EXSEL 0x%02x"), wParam);
		break;
	case VK_F1 :
		wsprintf(szOut, TEXT("VK_F1 0x%02x"), wParam);
		break;
	case VK_F10:
		wsprintf(szOut, TEXT("VK_F10 0x%02x"), wParam);
		break;
	case VK_F11:
		wsprintf(szOut, TEXT("VK_F11 0x%02x"), wParam);
		break;
	case VK_F12:
		wsprintf(szOut, TEXT("VK_F12 0x%02x"), wParam);
		break;
	case VK_F13:
		wsprintf(szOut, TEXT("VK_F13 0x%02x"), wParam);
		break;
	case VK_F14:
		wsprintf(szOut, TEXT("VK_F14 0x%02x"), wParam);
		break;
	case VK_F15:
		wsprintf(szOut, TEXT("VK_F15 0x%02x"), wParam);
		break;
	case VK_F16:
		wsprintf(szOut, TEXT("VK_F16 0x%02x"), wParam);
		break;
	case VK_F17:
		wsprintf(szOut, TEXT("VK_F17 0x%02x"), wParam);
		break;
	case VK_F18:
		wsprintf(szOut, TEXT("VK_F18 0x%02x"), wParam);
		break;
	case VK_F19:
		wsprintf(szOut, TEXT("VK_F19 0x%02x"), wParam);
		break;
	case VK_F2 :
		wsprintf(szOut, TEXT("VK_F2 0x%02x"), wParam);
		break;
	case VK_F20:
		wsprintf(szOut, TEXT("VK_F20 0x%02x"), wParam);
		break;
	case VK_F21:
		wsprintf(szOut, TEXT("VK_F21 0x%02x"), wParam);
		break;
	case VK_F22:
		wsprintf(szOut, TEXT("VK_F22 0x%02x"), wParam);
		break;
	case VK_F23:
		wsprintf(szOut, TEXT("VK_F23 0x%02x"), wParam);
		break;
	case VK_F24:
		wsprintf(szOut, TEXT("VK_F24 0x%02x"), wParam);
		break;
	case VK_F3 :
		wsprintf(szOut, TEXT("VK_F3 0x%02x"), wParam);
		break;
	case VK_F4 :
		wsprintf(szOut, TEXT("VK_F4 0x%02x"), wParam);
		break;
	case VK_F5 :
		wsprintf(szOut, TEXT("VK_F5 0x%02x"), wParam);
		break;
	case VK_F6 :
		wsprintf(szOut, TEXT("VK_F6 0x%02x"), wParam);
		break;
	case VK_F7 :
		wsprintf(szOut, TEXT("VK_F7 0x%02x"), wParam);
		break;
	case VK_F8 :
		wsprintf(szOut, TEXT("VK_F8 0x%02x"), wParam);
		break;
	case VK_F9 :
		wsprintf(szOut, TEXT("VK_F9 0x%02x"), wParam);
		break;
	case VK_HELP :
		wsprintf(szOut, TEXT("VK_HELP 0x%02x"), wParam);
		break;
	case VK_HOME :
		wsprintf(szOut, TEXT("VK_HOME 0x%02x"), wParam);
		break;
	case VK_HYPHEN			:
		wsprintf(szOut, TEXT("VK_HYPHEN 0x%02x"), wParam);
		break;
	case VK_INSERT :
		wsprintf(szOut, TEXT("VK_INSERT 0x%02x"), wParam);
		break;
	case VK_LBRACKET			:
		wsprintf(szOut, TEXT("VK_LBRACKET 0x%02x"), wParam);
		break;
	case VK_LCONTROL :
		wsprintf(szOut, TEXT("VK_LCONTROL 0x%02x"), wParam);
		break;
	case VK_LEFT :
		wsprintf(szOut, TEXT("VK_LEFT 0x%02x"), wParam);
		break;
	case VK_LMENU:
		wsprintf(szOut, TEXT("VK_LMENU 0x%02x"), wParam);
		break;
	case VK_LSHIFT :
		wsprintf(szOut, TEXT("VK_LSHIFT 0x%02x"), wParam);
		break;
	case VK_LWIN :
		wsprintf(szOut, TEXT("VK_LWIN 0x%02x"), wParam);
		break;
	case VK_MENU :
		wsprintf(szOut, TEXT("VK_MENU 0x%02x"), wParam);
		break;
	case VK_MULTIPLY :
		wsprintf(szOut, TEXT("VK_MULTIPLY 0x%02x"), wParam);
		break;
	case VK_NEXT :
		wsprintf(szOut, TEXT("VK_NEXT 0x%02x"), wParam);
		break;
	case VK_NONAME :
		wsprintf(szOut, TEXT("VK_NONAME 0x%02x"), wParam);
		break;
	case VK_NUMLOCK:
		wsprintf(szOut, TEXT("VK_NUMLOCK 0x%02x"), wParam);
		break;
	case VK_NUMPAD0:
		wsprintf(szOut, TEXT("VK_NUMPAD0 0x%02x"), wParam);
		break;
	case VK_NUMPAD1:
		wsprintf(szOut, TEXT("VK_NUMPAD1 0x%02x"), wParam);
		break;
	case VK_NUMPAD2:
		wsprintf(szOut, TEXT("VK_NUMPAD2 0x%02x"), wParam);
		break;
	case VK_NUMPAD3:
		wsprintf(szOut, TEXT("VK_NUMPAD3 0x%02x"), wParam);
		break;
	case VK_NUMPAD4:
		wsprintf(szOut, TEXT("VK_NUMPAD4 0x%02x"), wParam);
		break;
	case VK_NUMPAD5:
		wsprintf(szOut, TEXT("VK_NUMPAD5 0x%02x"), wParam);
		break;
	case VK_NUMPAD6:
		wsprintf(szOut, TEXT("VK_NUMPAD6 0x%02x"), wParam);
		break;
	case VK_NUMPAD7:
		wsprintf(szOut, TEXT("VK_NUMPAD7 0x%02x"), wParam);
		break;
	case VK_NUMPAD8:
		wsprintf(szOut, TEXT("VK_NUMPAD8 0x%02x"), wParam);
		break;
	case VK_NUMPAD9:
		wsprintf(szOut, TEXT("VK_NUMPAD9 0x%02x"), wParam);
		break;
	case VK_OEM_CLEAR:
		wsprintf(szOut, TEXT("VK_OEM_CLEAR 0x%02x"), wParam);
		break;
	case VK_OFF:
		wsprintf(szOut, TEXT("VK_OFF 0x%02x"), wParam);
		break;
	case VK_PA1:
		wsprintf(szOut, TEXT("VK_PA1 0x%02x"), wParam);
		break;
	case VK_PAUSE:
		wsprintf(szOut, TEXT("VK_PAUSE 0x%02x"), wParam);
		break;
	case VK_PERIOD			:
		wsprintf(szOut, TEXT("VK_PERIOD 0x%02x"), wParam);
		break;
	case VK_PLAY :
		wsprintf(szOut, TEXT("VK_PLAY 0x%02x"), wParam);
		break;
	case VK_PRINT:
		wsprintf(szOut, TEXT("VK_PRINT 0x%02x"), wParam);
		break;
	case VK_PRIOR:
		wsprintf(szOut, TEXT("VK_PRIOR 0x%02x"), wParam);
		break;
	case VK_PROCESSKEY :
		wsprintf(szOut, TEXT("VK_PROCESSKEY 0x%02x"), wParam);
		break;
	case VK_RBRACKET			:
		wsprintf(szOut, TEXT("VK_RBRACKET	 0x%02x"), wParam);
		break;
	case VK_RCONTROL :
		wsprintf(szOut, TEXT("VK_RCONTROL 0x%02x"), wParam);
		break;
	case VK_RETURN :
		wsprintf(szOut, TEXT("VK_RETURN 0x%02x"), wParam);
		break;
	case VK_RIGHT:
		wsprintf(szOut, TEXT("VK_RIGHT 0x%02x"), wParam);
		break;
	case VK_RMENU:
		wsprintf(szOut, TEXT("VK_RMENU 0x%02x"), wParam);
		break;
	case VK_RSHIFT :
		wsprintf(szOut, TEXT("VK_RSHIFT 0x%02x"), wParam);
		break;
	case VK_RWIN :
		wsprintf(szOut, TEXT("VK_RWIN 0x%02x"), wParam);
		break;
	case VK_SCROLL :
		wsprintf(szOut, TEXT("VK_SCROLL 0x%02x"), wParam);
		break;
	case VK_SELECT :
		wsprintf(szOut, TEXT("VK_SELECT 0x%02x"), wParam);
		break;
	case VK_SEMICOLON		:
		wsprintf(szOut, TEXT("VK_SEMICOLON 0x%02x"), wParam);
		break;
	case VK_SEPARATOR:
		wsprintf(szOut, TEXT("VK_SEPARATOR 0x%02x"), wParam);
		break;
	case VK_SHIFT:
		wsprintf(szOut, TEXT("VK_SHIFT 0x%02x"), wParam);
		break;
	case VK_SLASH			:
		wsprintf(szOut, TEXT("VK_SLASH 0x%02x"), wParam);
		break;
	case VK_SNAPSHOT :
		wsprintf(szOut, TEXT("VK_SNAPSHOT 0x%02x"), wParam);
		break;
	case VK_SPACE:
		wsprintf(szOut, TEXT("VK_SPACE 0x%02x"), wParam);
		break;
	case VK_SUBTRACT :
		wsprintf(szOut, TEXT("VK_SUBTRACT 0x%02x"), wParam);
		break;
	case VK_TAB:
		wsprintf(szOut, TEXT("VK_TAB 0x%02x"), wParam);
		break;
	case VK_UP :
		wsprintf(szOut, TEXT("VK_UP 0x%02x"), wParam);
		break;
	case VK_ZOOM :
		wsprintf(szOut, TEXT("VK_ZOOM 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH1 :
		wsprintf(szOut, TEXT("APP_LAUNCH1 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH2 :
		wsprintf(szOut, TEXT("APP_LAUNCH2 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH3 :
		wsprintf(szOut, TEXT("APP_LAUNCH3 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH4 :
		wsprintf(szOut, TEXT("APP_LAUNCH4 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH5 :
		wsprintf(szOut, TEXT("APP_LAUNCH5 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH6 :
		wsprintf(szOut, TEXT("APP_LAUNCH6 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH7 :
		wsprintf(szOut, TEXT("APP_LAUNCH7 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH8 :
		wsprintf(szOut, TEXT("APP_LAUNCH8 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH9 :
		wsprintf(szOut, TEXT("APP_LAUNCH9 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH10:
		wsprintf(szOut, TEXT("APP_LAUNCH10 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH11:
		wsprintf(szOut, TEXT("APP_LAUNCH11 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH12:
		wsprintf(szOut, TEXT("APP_LAUNCH12 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH13:
		wsprintf(szOut, TEXT("APP_LAUNCH13 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH14:
		wsprintf(szOut, TEXT("APP_LAUNCH14 0x%02x"), wParam);
		break;
	case VK_APP_LAUNCH15:
		wsprintf(szOut, TEXT("APP_LAUNCH15 0x%02x"), wParam);
		break;
	default:
		wsprintf(szOut, TEXT("vk_unknown 0x%08x"), wParam);
		break;
  }
}


//
// CreateMenuBar
//   create the commandbar and add any menus and buttons to it you like
//   call AddAdornments to show close button which is only appropriate on H/PC devices
//
HWND CreateMenuBar(HWND hwnd, HWND hwndCB, BOOL bCreating)
{
	// always delete to avoid a leak
	if (hwndCB)
	{
		//Destroy MenuBar       
		DestroyWindow(hwndCB);
		hwndCB = NULL;
	}
	
	if (bCreating)
	{
		//Create a MenuBar
		SHMENUBARINFO mbi;
		memset(&mbi, 0, sizeof(SHMENUBARINFO));
		mbi.cbSize     = sizeof(SHMENUBARINFO);
		mbi.hwndParent = hwnd;
		mbi.nToolBarId = IDM_MAIN_MENU;
		mbi.hInstRes   = g_hinst;
		mbi.nBmpId     = 0;
		mbi.cBmpImages = 0;	
		
		SHCreateMenuBar(&mbi);
		if (!SHCreateMenuBar(&mbi))
			MessageBox(hwnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
		hwndCB = mbi.hwndMB;
	}
	
	return hwndCB;
	
}

//
// DoMenuCheckItem
void DoMenuCheckItem(UINT IDCTL){
	
	HMENU hm = SHGetSubMenu(g_hwndCB, IDM_MAIN_MENUITEM1);
	BOOL bRes;

	switch (IDCTL) {
	case ID_FILE_LOGTOFILE:
		if (fUseLog){
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		}
		else{
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
			//log2file
			newfile(L"\\KeyTest.txt");

			Add2Log(TEXT("Message\twParam\tlParam\tALT/SHFT/CTRL/CAP\n"),FALSE);

			MessageBox(g_hwnd, L"Logging to \\KeyTest.txt", L"Logging enabled", MB_OK | MB_TOPMOST | MB_SETFOREGROUND);
		}
		fUseLog = !fUseLog;
		break;
	case ID_AllKeys:
		if (fUseAllKeys){
			fUseAllKeys=FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		}
		else{
			fUseAllKeys=TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		bRes = AllKeys(fUseAllKeys);
		DEBUGMSG(1, (L"AllKeys() returned %i\n", bRes));
		break;
#ifdef USEGAPI
	case ID_USEGX:
		if (fUSEGX)
		{
			fUSEGX=FALSE;
			GXCloseInput();
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fUSEGX = TRUE;
			GXOpenInput();
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
#endif
	case ID_FILE_SHOW_WMKEYDOWN:
		if (fWM_KEYDOWN){
			fWM_KEYDOWN = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_KEYDOWN = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMCHAR:
		if (fWM_CHAR){
			fWM_CHAR = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_CHAR = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMKEYUP:
		if (fWM_KEYUP){
			fWM_KEYUP = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_KEYUP = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMLBUTTONDBLCLK:
		if (fWM_LBUTTONDBLCLK){
			fWM_LBUTTONDBLCLK = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_LBUTTONDBLCLK = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMLBUTTONDOWN:
		if (fWM_LBUTTONDOWN){
			fWM_LBUTTONDOWN = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_LBUTTONDOWN = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMLBUTTONUP:
		if (fWM_LBUTTONUP){
			fWM_LBUTTONUP = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_LBUTTONUP = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	case ID_FILE_SHOW_WMMOUSEMOVE:
		if (fWM_MOUSEMOVE){
			fWM_MOUSEMOVE = FALSE;
			CheckMenuItem(hm, IDCTL, MF_UNCHECKED);
		} else {
			fWM_MOUSEMOVE = TRUE;
			CheckMenuItem(hm, IDCTL, MF_CHECKED);
		}
		break;
	}
}

//
// HandleCommand
//   will return FALSE if handled
//
BOOL HandleCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int iRes;	
	// Parse the menu selections:
	switch (LOWORD(wParam))
	{
	case ID_FILE_SHOW_WMKEYDOWN:
	case ID_FILE_SHOW_WMCHAR:
	case ID_FILE_SHOW_WMKEYUP:
	case ID_FILE_SHOW_WMLBUTTONDBLCLK:
	case ID_FILE_SHOW_WMLBUTTONDOWN:
	case ID_FILE_SHOW_WMLBUTTONUP:
	case ID_FILE_SHOW_WMMOUSEMOVE:
		DoMenuCheckItem(LOWORD(wParam));
		return FALSE;
		break;
	case ID_AllKeys:
		DoMenuCheckItem(LOWORD(wParam));
		return FALSE;
		break;
	case ID_USEGX:
		DoMenuCheckItem(LOWORD(wParam));
		return FALSE;
		break;
	case ID_FILE_LOGTOFILE:
		DoMenuCheckItem(LOWORD(wParam));
		return FALSE;
		break;
#ifdef USEGAPI
	case ID_ACTION_SUSPENDGX:
		iRes = GXSuspend();
		DEBUGMSG(1, (L"# - > GXSuspend returned %i\n", iRes));
		return FALSE;
		break;
		
	case ID_ACTION_RESUMEGX:
		iRes = GXResume();
		DEBUGMSG(1, (L"# - > GXResume returned %i\n", iRes));
		return FALSE;
		break;
#endif
	case ID_ACTION_REGISTERHOTKEYS:
		iRes = regHotKeys(g_hwnd);
		DEBUGMSG(1, (L"# - > regHotKeys returned %i\n", iRes));
		return FALSE;
		break;

	case ID_ACTION_UNREGISTERFUNC1:
		iRes = unRegKeys();
		DEBUGMSG(1, (L"# - > unRegKeys returned %i\n", iRes));
		return FALSE;
		break;

	case ID_ACTION_CLEARLIST:
		if(ClearListView())
			DEBUGMSG(1, (L"ClearListView() OK\n"));
		else
			DEBUGMSG(1, (L"ClearListView() FAILED\n"));
		return FALSE;
		break;

	case IDM_EXIT:
		PostQuitMessage(0);
		return false;
		break;
	}
	return TRUE;
}

//
// Mesage handler for the About box.
//  since this is a dialog proc, return TRUE if it was indeed handled
//   this is backwards from a window proc
//
LRESULT CALLBACK About(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SHINITDLGINFO shidi;
		// Create a Done button and size it.
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hwnd;
		SHInitDialog(&shidi);
		return TRUE;
		
		
    case WM_COMMAND:
		if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
		{
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

