
// UPIM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CUPIMApp:
// �йش����ʵ�֣������ UPIM.cpp
//

#ifdef _EXE_MODE

class CUPIMApp : public CWinApp
{
public:
	CUPIMApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

public:
	HANDLE    m_hMutex ;     // �жϿͻ��汾�Ƿ�ֻ����һ��ʵ��
};

extern CUPIMApp theApp;

#endif