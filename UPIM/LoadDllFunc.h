#pragma once
#include "StdAfx.h"

// ���ؽ�ͼdll�е�PupupDialog�ӿ�
typedef void (*IUPIM_PupupDialog)(HWND m_hwnd);
extern IUPIM_PupupDialog	IUPIM_PupupDialog_;
extern HMODULE	II_mod;

extern BOOL LoadDLLFunc();
extern void UnLoadDLLFunc();