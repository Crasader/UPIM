
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WS03//_WIN32_WINNT_WINXP
#endif

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#define _USE_MFC
#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
	
#define _RIBBONS_SUPPORT
#define _DETECT_MEMORY_LEAK
#define _CRT_SECURE_NO_DEPRECATE 

#define LOG_FILTER      // ����Э�����־���ƺ�
#define IP_WHITELIST    // �Ƿ�������������
#define KICKMAN			// �Ƿ񵥵��¼
#define __NEW_MODE		// ���ڽ�����绷����ʱ��ķְ�	
//#define _NEW_HEADER	// ʹ��UP������Э���ͷ

// ����LOG֧�� 
#define _USE_LOG_
#include "Serverlog.h"
#include "CBase64Coding.h"

// ����socket֧��
#include "../Socket/Common/Src/GeneralHelper.h"
#include "ado2.h"
#include "IniFile.h"

// ����json֧��
#include "../Common/json/json.h"
using namespace Json;    //json�������ռ�

#include "../Common/macro.h"
#include "struct.h"

#include "../Common/protocol.h"
#include "TabCtrl/TabCtrl.h"
#include "Func.h"

#ifdef _DEBUG
	#define _HOST(s)         "http://upia."##s##"/api/live/"
	#define HOST(s)          _HOST(s)
#else
	#define _HOST(s)         "http://upia."##s##"/api/live/"
	#define HOST(s)          _HOST(s)
#endif

#pragma warning(disable : 4786)	// too long identifiers.
#pragma warning(disable : 4996)