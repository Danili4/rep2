#include "common.h"
#include <commctrl.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"comctl32.lib")
static LPCWSTR szWndClass1=L"WndClass1";
static LPCWSTR szWndClass2=L"WndClass2";
static wchar_t szText[16][80]={0};
static wchar_t szText1[80]=L"";
double m=0;
HINSTANCE hInst;
int CmdShow;
static int n;
HWND **hTable;
LRESULT CALLBACK AboutProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	InitCommonControls();
	HWND hWnd=Window(szWndClass1,(LPCWSTR)L"Win32 Application",WndProc,1024,540,hInstance,nCmdShow);
	CmdShow=nCmdShow;
	hInst=hInstance;
	HMENU hMenu1=CreateMenu();
	HMENU hSubMenu1=CreateMenu();
	HMENU hSubMenu2=CreateMenu();
	Menu(hMenu1,hSubMenu1,1,L"&Help",4);
	SubMenu(hSubMenu1,2,L"&About",5);
	Menu(hMenu1,hSubMenu2,3,L"&File",4);
	SubMenu(hSubMenu2,4,L"&Exit",4);
	SubMenu(hSubMenu2,5,L"&Open File",9);
	SetMenu(hWnd,hMenu1);
	HWND hEdit=EditBox(hWnd,ES_LEFT,L"",25,25,50,20);
	HWND hStatic=Text(hWnd,SS_RIGHT,L"S",10,25,10,20);
	HWND hEdit1=EditBox(hWnd,ES_LEFT,L"",25,60,50,20);
	HWND hStatic1=Text(hWnd,SS_RIGHT,L"η",10,60,10,20);
	HWND hButton=CreateWindowEx(0,L"BUTTON",L"Языки",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								25,100,60,20,hWnd,0,hInstance,0);
	HWND hButton1=CreateWindowEx(0,L"BUTTON",L"α",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								85,100,60,20,hWnd,0,hInstance,0);
	HWND hButton2=CreateWindowEx(0,L"BUTTON",L"K",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								145,100,60,20,hWnd,0,hInstance,0);
	HWND hButton3=CreateWindowEx(0,L"BUTTON",L"μ",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								205,100,60,20,hWnd,0,hInstance,0);
	HWND hButton4=CreateWindowEx(0,L"BUTTON",L"",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								265,100,20,20,hWnd,0,hInstance,0);
	HWND hButton5=CreateWindowEx(0,L"BUTTON",L"1",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								265,120,20,20,hWnd,0,hInstance,0);
	HWND hButton6=CreateWindowEx(0,L"BUTTON",L"2",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								265,140,20,20,hWnd,0,hInstance,0);
	HWND hButton7=CreateWindowEx(0,L"BUTTON",L"3",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								265,160,20,20,hWnd,0,hInstance,0);
	HWND hButton8=CreateWindowEx(0,L"BUTTON",L"4",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								265,180,20,20,hWnd,0,hInstance,0);
	HWND hButton9=CreateWindowEx(0,L"BUTTON",L"Вычислить",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								90,25,80,20,hWnd,(HMENU)6,hInstance,0);

	hTable=new HWND* [4];
	for (int i=0;i<4;i++)
	{
		hTable[i]=new HWND [4];
	}
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
	{
		hTable[i][j]=EditBox(hWnd,ES_LEFT|WS_BORDER|ES_AUTOHSCROLL,L"",25+(60*j),120+(20*i),60,20);
	}

	

	UpdateWindow(hWnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnregisterClass(szWndClass1,hInst);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,
							WPARAM wParam,LPARAM lParam)
{
	HWND hAboutWnd;
	switch(msg)
	{
		case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
		case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 4:
		SendMessage(hWnd,WM_CLOSE,0,0);
		break;
		case 2:
		hAboutWnd=Window(szWndClass2,(LPCWSTR)L"About",
						AboutProc,480,540,hInst,CmdShow);
		break;
		case 6:
		{
		Edit_GetLine(hTable[0][0],0,szText[0],79);
		Edit_GetLine(hTable[1][0],0,szText[4],79);
		Edit_GetLine(hTable[2][0],0,szText[8],79);
		Edit_GetLine(hTable[3][0],0,szText[12],79);
		m=_wtof(szText[0]);
		n=swprintf(szText1,L"%f",m);
		Edit_SetText(hTable[0][1],szText1);
		}
		break;
		}
		return 0;
		break;
		default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
		break;
	}
	return 0;
}

LRESULT CALLBACK AboutProc(HWND hWnd,UINT msg,
							WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CLOSE:
		DestroyWindow(hWnd);
		UnregisterClass(szWndClass2,hInst);
		break;
		
		default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
		break;
	}
	return 0;
}

