#include "stdafx.h"
#include "LoadDllFunc.h"
#include "globalvar.h"

IUPIM_PupupDialog	IUPIM_PupupDialog_ = NULL;
HMODULE	II_mod = NULL;

BOOL LoadDLLFunc()
{
	char dllpath[MAX_PATH],filename_ImageTool[MAX_PATH];
#ifdef _DEBUG
	sprintf(dllpath,"%s\\", g_config.szHomePath);
	sprintf(filename_ImageTool,"%s\\CatchScreend.dll", g_config.szHomePath);
#else
	sprintf(dllpath,"%s\\", g_config.szHomePath);
	sprintf(filename_ImageTool,"%s\\CatchScreen.dll", dllpath);
#endif
	if(!II_mod)
	{
		char PathPre[MAX_PATH] = {0};
		GetCurrentDirectory(MAX_PATH, PathPre);

		SetCurrentDirectory(dllpath);
		II_mod = AfxLoadLibrary(filename_ImageTool);

		// ����Ǳ�UP�ͻ��˵��õģ���Ҫ��·�����û�ȥ�������Ӱ��UP�ͻ��˵Ĺ���
		SetCurrentDirectory(PathPre);
		if(!II_mod)	
			return FALSE;

		IUPIM_PupupDialog_ = ( IUPIM_PupupDialog ) ::GetProcAddress(II_mod, "PupupDialog");
	}
	if( !IUPIM_PupupDialog_ )
		return FALSE;

	return TRUE;
}

void UnLoadDLLFunc()
{
	if(II_mod)
	{
		AfxFreeLibrary(II_mod);
		II_mod = NULL;
	}
}