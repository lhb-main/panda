#include <windows.h>
#include <stdio.h>

//窗口处理函数
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//线程处理函数
DWORD WINAPI PandaProc(LPVOID lpParam);