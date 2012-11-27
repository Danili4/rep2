#include "common.h"

HWND Window(LPCWSTR szWindowClass,LPCWSTR szTitle,LRESULT (CALLBACK *pWndProc)(HWND,UINT,WPARAM,LPARAM),
			int width,int height,HINSTANCE hInstance,int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wcex;
	memset(&wcex,0,sizeof(wcex));
	wcex.cbSize=sizeof(wcex);
	wcex.style=CS_HREDRAW|CS_VREDRAW;
	wcex.lpfnWndProc=pWndProc;
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;
	wcex.hInstance=hInstance;
	wcex.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wcex.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground=(HBRUSH)GetSysColorBrush(0);
	wcex.lpszMenuName=NULL;
	wcex.lpszClassName=szWindowClass;
	wcex.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	if(!RegisterClassEx(&wcex))	
		MessageBox(NULL,(LPCWSTR)L"RegisterClassEx fail!",
					(LPCWSTR)L"Error",MB_OK);
	hWnd=CreateWindowEx(0,szWindowClass,szTitle,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,CW_USEDEFAULT,
						width,height,NULL,NULL,
						hInstance,NULL);	
	if(!hWnd)	
		MessageBox(NULL,(LPCWSTR)L"CreateWindow fail!",
					(LPCWSTR)L"Error",MB_OK);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

HWND EditBox(HWND hWnd,DWORD dwStyle,LPCWSTR lpszText,int x,int y,
			int width,int height)
{
 HWND hEdit=CreateWindowEx(0,(LPCWSTR)L"EDIT",NULL,
			dwStyle|WS_CHILD|WS_VISIBLE,x,y,width,height,
			hWnd,0,0,0);
 SendMessage(hEdit,WM_SETTEXT,0,(LPARAM)lpszText);
 return hEdit;
}

HWND Text(HWND hWnd,DWORD dwStyle,LPCWSTR lpszText,int x,int y,
			int width,int height)
{
 HWND hText=CreateWindowEx(0,(LPCWSTR)L"STATIC",lpszText,
			dwStyle|WS_CHILD|WS_VISIBLE,x,y,width,height,
			hWnd,0,0,0);
  return hText;
}

void Menu(HMENU hMenu,HMENU hSubMenu,UINT wID,LPWSTR dwTypeData,UINT cch)
{
	MENUITEMINFO mii;
	memset(&mii,0,sizeof(mii));
	mii.cbSize=sizeof(mii);
	mii.fType=MFT_STRING;
	mii.fMask=MIIM_ID|MIIM_STRING|MIIM_DATA|
	MIIM_SUBMENU;
	mii.wID=wID;
	mii.dwTypeData=dwTypeData;
	mii.cch=cch;
	mii.hSubMenu=hSubMenu;
	InsertMenuItem(hMenu,0,TRUE,&mii);
}

void SubMenu(HMENU hSubMenu,UINT wID,LPWSTR dwTypeData,UINT cch)
{
	MENUITEMINFO mii;
	memset(&mii,0,sizeof(mii));
	mii.cbSize=sizeof(mii);
	mii.fType=MFT_STRING;	
	mii.fMask=MIIM_ID|MIIM_STRING|MIIM_DATA;
	mii.wID=wID;
	mii.dwTypeData=dwTypeData;
	mii.cch=cch;
	InsertMenuItem(hSubMenu,0,TRUE,&mii);
}