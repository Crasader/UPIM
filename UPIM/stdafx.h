#pragma once

//////////////////////////////////////////////////////////////////////////
// ��ͬ�汾�汾
//#define VER_UPIM_NORMAL		// ��ͨ��
//#define VER_UPIM_DLLMODE		// DLL�棬Ͷ��һ����ʹ�õĿͻ��ˣ��Ƿ�װ��DLL���ã���Ϊһ���������������
//#define VER_UPIM_ANALYS		// Ͷ�˰�
//#define VER_UPIM_ANALYS2		// Ͷ�˰�2(�����ĵ�1117�е�Ͷ�˶˵�½�İ汾��ͨ����¼��ֱ�Ӵ򿪵�½��)
//#define VER_UPIM_CLIENT		// ��ͨ��2(�����ĵ�1117�еĿͻ��˵�½�İ汾��ֻ��ͨ�������д��ε��ã�ֱ�Ӵ��޷��򿪡�)
//#define IM_EXE_TO_UP          // �궨�壺�ͻ��汾�ṩexe��UP�ͻ���ʹ�� �˺��VER_UPIM_CLIENTһ������ر� 
#define VER_UPIM_RONGYUN      // ���ƿͷ�ϵͳ
//////////////////////////////////////////////////////////////////////////
// �汾���ֻ�
#ifdef VER_UPIM_NORMAL
	#define VER_UPIM_NUMS 0
#endif
#ifdef VER_UPIM_DLLMODE
	#define VER_UPIM_NUMS 1
#endif
#ifdef VER_UPIM_ANALYS
	#define VER_UPIM_NUMS 2
#endif
#ifdef VER_UPIM_ANALYS2
	#define VER_UPIM_NUMS 3
#endif
#ifdef VER_UPIM_CLIENT
	#define VER_UPIM_NUMS 4
#endif
#ifdef VER_UPIM_RONGYUN
	#define VER_UPIM_NUMS 5
#endif

//////////////////////////////////////////////////////////////////////////
// ֻ��VER_UPIM_DLLMODEģʽ�£����Ƿ�װ��dllʹ�ã������ȫ��EXE����ģʽ
#ifdef VER_UPIM_DLLMODE
	#define _DLL_MODE		// ��װ��DLL�ӿڵ���
#else
	#define _EXE_MODE		// ����ʱ������ʾ��
#endif

// ������DLL
#define IM_EXPORT

#define __NEW_MODE		// ���ڽ�����绷����ʱ��ķְ�	
//#define _NEW_HEADER	// ʹ��UP������Э���ͷ

#define NOT_DISPLAY_ID_LIKE_MOBLIE_NUM // ����ʾID�����ֻ������

//////////////////////////////////////////////////////////////////////////

#define _USE_MFC
#define _RIBBONS_SUPPORT
//#define _DETECT_MEMORY_LEAK

#define _HTTPAPI1(api) "http://121.14.69.23:8004/API/"##api
#define _HTTPAPI2(api) "http://113.108.146.107:855/UserInfoService.svc/"##api
#define HTTPAPIUSERMANAGE(api)  _HTTPAPI1(api)
#define HTTPAPIUSERINFO(api)  _HTTPAPI2(api)

#include "../Socket/Common/Src/GeneralHelper.h"
#include "../UiLib/UIlib.h"
#include "../UiLib/Utils/WinImplBase.h"

#include "../Common/macro.h"
#include <afxcontrolbars.h>
#include "CBase64Coding.h"
// ����XML֧��
#include "TinyXML/tinyxml.h"
// ����sqlite֧��
#include "sqlite/DbSqlite.h"
// ����md5֧��
#include "md5.h"
// ����json֧��
#include "../Common/json/json.h"
using namespace Json;    //json�������ռ�

#ifndef NO_USING_DUILIB_NAMESPACE
using namespace DuiLib;
using namespace std;
#endif

#ifdef _DEBUG
#pragma comment(lib, "..\\UiLib\\lib\\DuiLib_d.lib")
#pragma comment(lib, "sqlite\\sqlite3d.lib")
#else
#pragma comment(lib, "..\\UiLib\\lib\\DuiLib.lib")
#pragma comment(lib, "sqlite\\sqlite3.lib")
#endif
#include "rcsdk.h"
#include "globalvar.h"
#include "Func.h"
#include "mmsystem.h"					//�����������
#include "txtutil.h"
using namespace epius;
#pragma comment(lib, "winmm.lib")

