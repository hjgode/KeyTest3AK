/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

****************************************************************************/
//
// prototoypes defined in listview.cpp
//
BOOL				ClearListView();
BYTE				getKeyStates();
BOOL 				AddMessageToLV(PTSTR szMsg, WPARAM wParam, LPARAM lParam, BOOL bCHAR, BYTE flags);
LRESULT CALLBACK 	ListviewProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND 				CreateListview(HWND hwndParent, BOOL bCreating);
BOOL				HandleInputMessages(UINT message, WPARAM wParam, LPARAM lParam);

//
// globals defined in listview.cpp
//
extern HWND				g_hwndLV;	// handle to the listview window


