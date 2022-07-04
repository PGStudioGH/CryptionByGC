#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

int CheckFullScreen()
{
	DWORD FS;
	GetConsoleDisplayMode(&FS);
	return FS;
}

void createWindow(int cols, int lines)
{
	if (cols < 1) cols = 1;
	else if (cols > 999) cols = 999;

	if (lines < 1) lines = 1;
	else if (lines > 99) lines = 99;

	char str[28];
	sprintf_s(str, "@mode con cols=%d lines=%d", cols, lines);
	system(str);

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int horizontal = desktop.right;

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	HMENU hMenu = GetSystemMenu(consoleWindow, 0);
	DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
	DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
	DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);

	CONSOLE_FONT_INFOEX fontInfo;
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &fontInfo);
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.FontWeight = FW_NORMAL;
	fontInfo.FontFamily = FF_DONTCARE;

	if (horizontal < 800)
	{
		fontInfo.dwFontSize.X = 8;
		fontInfo.dwFontSize.Y = 12;
	}
	else {
		fontInfo.dwFontSize.X = 18;
		fontInfo.dwFontSize.Y = 24;
	}

	wcscpy(fontInfo.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &fontInfo);
}