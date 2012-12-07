#include "common.h"
#include "eval.h"
#include <commctrl.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"comctl32.lib")
static LPCWSTR szWndClass1=L"WndClass1";
static wchar_t szText[14][80]={0};
static wchar_t szText1[80]=L"";
double s=0;			double alpha[4]={0};	double k[4]={0};	double mu[4]={0};
double V[4]={0};	double T[4]={0};		HINSTANCE hInst;	double h=0;
int CmdShow;		HWND hEdit;				static int n;		HWND hEdit1;
HWND **hTable;		HWND **hTable1;
int Eval();
LRESULT CALLBACK AboutProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	InitCommonControls();
	HWND hWnd=Window(szWndClass1,(LPCWSTR)L"Оценка программных характеристик алгоритмов",
	WndProc,500,300,hInstance,nCmdShow);
	CmdShow=nCmdShow;hInst=hInstance;HMENU hMenu1=CreateMenu();
	HMENU hSubMenu2=CreateMenu();Menu(hMenu1,hSubMenu2,3,L"&File",4);
	SubMenu(hSubMenu2,4,L"&Exit",4);SetMenu(hWnd,hMenu1);
	hEdit=EditBox(hWnd,ES_LEFT,L"",25,25,50,20);
	HWND hStatic=Text(hWnd,SS_RIGHT,L"S",10,25,10,20);
	hEdit1=EditBox(hWnd,ES_LEFT,L"",25,60,50,20);
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
								5,100,20,20,hWnd,0,hInstance,0);
	HWND hButton5=CreateWindowEx(0,L"BUTTON",L"1",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								5,120,20,20,hWnd,0,hInstance,0);
	HWND hButton6=CreateWindowEx(0,L"BUTTON",L"2",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								5,140,20,20,hWnd,0,hInstance,0);
	HWND hButton7=CreateWindowEx(0,L"BUTTON",L"3",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								5,160,20,20,hWnd,0,hInstance,0);
	HWND hButton8=CreateWindowEx(0,L"BUTTON",L"4",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								5,180,20,20,hWnd,0,hInstance,0);
	HWND hButton9=CreateWindowEx(0,L"BUTTON",L"Вычислить",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								90,25,80,20,hWnd,(HMENU)6,hInstance,0);
	HWND hButton10=CreateWindowEx(0,L"BUTTON",L"V,Кб",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								265,100,60,20,hWnd,0,hInstance,0);
	HWND hButton11=CreateWindowEx(0,L"BUTTON",L"T,ч",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								325,100,60,20,hWnd,0,hInstance,0);
	HWND hButton12=CreateWindowEx(0,L"BUTTON",L"m",WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
								385,100,60,20,hWnd,0,hInstance,0);

	hTable=new HWND* [4];for (int i=0;i<4;i++)
	{
		hTable[i]=new HWND [4];
	}
	for(int i=0;i<4;i++)for(int j=0;j<4;j++)
	{
		hTable[i][j]=EditBox(hWnd,ES_LEFT|WS_BORDER|ES_AUTOHSCROLL,L"",25+(60*j),120+(20*i),60,20);
	}
	hTable1=new HWND* [4];for (int i=0;i<4;i++)
	{
		hTable1[i]=new HWND [3];
	}
	for(int i=0;i<4;i++)for(int j=0;j<3;j++)
	{
		hTable1[i][j]=EditBox(hWnd,ES_LEFT|WS_BORDER|ES_AUTOHSCROLL,L"",265+(60*j),120+(20*i),60,20);
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
		case 6:
		Eval();
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
int Eval()
{
	Edit_GetLine(hEdit,0,szText[12],79);
	Edit_GetLine(hEdit1,0,szText[13],79);
	s=_wtof(szText[12]);
	h=_wtof(szText[13]);
	Edit_GetLine(hTable[0][1],0,szText[0],79);
	Edit_GetLine(hTable[0][2],0,szText[1],79);
	Edit_GetLine(hTable[0][3],0,szText[2],79);
	Edit_GetLine(hTable[1][1],0,szText[3],79);
	Edit_GetLine(hTable[1][2],0,szText[4],79);
	Edit_GetLine(hTable[1][3],0,szText[5],79);
	Edit_GetLine(hTable[2][1],0,szText[6],79);
	Edit_GetLine(hTable[2][2],0,szText[7],79);
	Edit_GetLine(hTable[2][3],0,szText[8],79);
	Edit_GetLine(hTable[3][1],0,szText[9],79);
	Edit_GetLine(hTable[3][2],0,szText[10],79);
	Edit_GetLine(hTable[3][3],0,szText[11],79);
	alpha[0]=_wtof(szText[0]);	alpha[1]=_wtof(szText[3]);
	alpha[2]=_wtof(szText[6]);	alpha[3]=_wtof(szText[9]);
	k[0]=_wtof(szText[1]);		k[1]=_wtof(szText[4]);
	k[2]=_wtof(szText[7]);		k[3]=_wtof(szText[10]);
	mu[0]=_wtof(szText[2]);		mu[1]=_wtof(szText[5]);
	mu[2]=_wtof(szText[8]);		mu[3]=_wtof(szText[11]);
	for(int i=0;i<4;i++)
	{
	double etaTwo = 0;	double annTwo = 0;
	double ann = 0;		double etaOne = 0;
	etaTwo = etaTwoRecognition(h, k[i]);
	annTwo = annTwoRecognition(alpha[i], etaTwo, mu[i], 0.01, 10.0);
	ann = annRecognition(annTwo, alpha[i]);
	etaOne = etaOneRecognition(annTwo, alpha[i], 0.01, 10.0);
	V[i] = vRecognition(ann, etaOne, etaTwo);
	T[i] = tRecognition(V[i], mu[i], s);
	}
	for(int i=0;i<4;i++)
		{
			n=swprintf(szText1,L"%.4f",(V[i])/(1024*8));
			Edit_SetText(hTable1[i][0],szText1);
			n=swprintf(szText1,L"%.4f",(V[i])/3000);
			Edit_SetText(hTable1[i][2],szText1);
		}
	for(int i=0;i<4;i++)
		{
			n=swprintf(szText1,L"%.4f",(T[i])/3600);
			Edit_SetText(hTable1[i][1],szText1);
		}	
	return 0;
}