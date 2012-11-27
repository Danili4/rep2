#ifndef _COMMON_H
#define _COMMON_H
#include <windows.h>

HWND Window(LPCWSTR szWindowClass,LPCWSTR szTitle,
			LRESULT (CALLBACK *pWndProc)(HWND,UINT,WPARAM,LPARAM),
			int width,int height,HINSTANCE hInstance,int nCmdShow);
HWND EditBox(HWND hWnd,DWORD dwStyle,LPCWSTR lpszText,int x,int y,
			int width,int height);
HWND Text(HWND hWnd,DWORD dwStyle,LPCWSTR lpszText,int x,int y,
			int width,int height);
void Menu(HMENU hMenu,HMENU hSubMenu,UINT wID,LPWSTR dwTypeData,UINT cch);
void SubMenu(HMENU hSubMenu,UINT wID,LPWSTR dwTypeData,UINT cch);
#endif