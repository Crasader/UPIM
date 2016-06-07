#include "StdAfx.h"
#include "IMExport.h"
#include "globalvar.h"
#include "UPIM.h"
#include "LoadDllFunc.h"
#include "MainPort.h"
#include "MyThread.h"

#ifdef _DLL_MODE

// ����IM����֮ǰ ��ҪINIT
BOOL UEXP_Init(const char *PubDir, const char *PriDir, const char *CfgFile)
{
	OutputDebugString("UEXP_Init begin\r\n");
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	//////////////////////////////////////////////////////////////////////////

	// ����dll��ȫ����Դ����ʹ�ã�����ʹ��GetModuleHandle(NULL)���õ����ǵ��ô�DLL��exe����Դ
	g_hInstance = AfxGetInstanceHandle();
	CPaintManagerUI::SetInstance(g_hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	LoadConfig();				// ���������ļ�

	//winxp�У��ڴ˴�InitRichEditCom�Ļ����ں���ʹ��com������ᱨ0x800401f0(CoInitialize has not been called)
	//InitRichEditCom();			// COM����
	
	LoadDLLFunc();				// ����DLL
	InitConnect();				// ���ӷ�����

	// Ϊ�˱���duilib�еĽ����GetMessage��ȡ���߳��е���Ϣ�������µ��߳������н������
 	g_pCreateThread = AfxBeginThread(RUNTIME_CLASS(CMyThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
 	g_pCreateThread->m_bAutoDelete = FALSE;
	g_pCreateThread->ResumeThread();

	return TRUE;
}

// �ⲿ���õ�
// �ر�
BOOL UEXP_Uninit()
{
	OutputDebugString("UEXP_Uninit begin\r\n");
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	//////////////////////////////////////////////////////////////////////////

	UnLoadDLLFunc();		// ж��DLL
	UnInitRichEditCom();	// ж��COM
	StopConnect();			// �Ͽ�����

	if (g_TGChatDialog)
	{
		g_TGChatDialog->OnExit();
		g_TGChatDialog = NULL;
	}
	if (g_pCreateTG1)
	{
		g_pCreateTG1->OnExit();
		g_pCreateTG1 = NULL;
	}
	if (g_pCreateTG2)
	{
		g_pCreateTG2->OnExit();
		g_pCreateTG2 = NULL;
	}

	if (g_pFrame)
	{
		if (g_pFrame->pLoginDialog)
		{
			if (!g_pFrame->bLoginDialogClosed)
				g_pFrame->pLoginDialog->OnExit();
		}
		g_pFrame->OnExit();
		g_pFrame = NULL;
	}

	// �߳��˳�
	if((NULL != g_pCreateThread) && (NULL != g_pCreateThread->m_hThread))
	{
		BOOL bPost = ::PostThreadMessage(g_pCreateThread->m_nThreadID, WM_MYTHREAD_DELALL, 0, 0);
		if(::WaitForSingleObject(g_pCreateThread->m_hThread, 500) == WAIT_OBJECT_0)
		{
			delete g_pCreateThread;
			g_pCreateThread = NULL;
		}
// 		g_pCreateThread->PostThreadMessage(WM_QUIT, 0, 0);
// 		WaitForSingleObject(g_pCreateThread->m_hThread, INFINITE);
// 		delete g_pCreateThread;
// 		g_pCreateThread = NULL;
	}

	CPaintManagerUI::SetCloseFlag(true);
	CPaintManagerUI::Term();

	return TRUE;
}

// ���õ�¼����
void UEXP_SetLoginType(long nUserType, HWND parent, long lFeedBackMsg, long nFlag /* = IMFLAG_INDEPENT|IMFLAG_NOHQ */, long Reserved /* = 0 */)
{
	OutputDebugString("UEXP_SetLoginType begin\r\n");
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	//////////////////////////////////////////////////////////////////////////
	USER_LOG("UEXP_SetLoginType %d,%p,%d,%d", nUserType, parent, lFeedBackMsg, nFlag);

	//g_nUserType:enum EUSERTYPE
	g_nUserType = nUserType;
	g_hVessel = parent;
	g_hFeedBackMsg = lFeedBackMsg;
	g_bIndepend = (nFlag & IMFLAG_INDEPENT) ? 1 : 0;
	g_nHQ = (nFlag & IMFLAG_HQ) ? 1 : 0;

	// �Ȼ���MIAN������ʼ��Ϣѭ��
 //	::PostThreadMessage(g_pCreateThread->m_nThreadID, WM_MYTHREAD_INITMAIN, 0, 0);
}

// ��¼�ӿ� 
BOOL UEXP_Login(long nMode, char Khh[51], char YYBInfo[51], char SSOCode[255], long Reserved /* = 0 */)
{
	OutputDebugString("UEXP_Login begin\r\n");
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	
	//////////////////////////////////////////////////////////////////////////
	USER_LOG("UEXP_Login %d,%s,%s",nMode, Khh, YYBInfo);
	if(!g_bIndepend && !g_hVessel) return FALSE;

	strncpy(g_loginname, Khh, strlen(Khh));
	g_MyClient.m_strUserid = g_loginname;

	//g_nLoginMode:enum EIMLOGINMODE
	g_nLoginMode = nMode;

	// ֪ͨ�̻߳���
	::PostThreadMessage(g_pCreateThread->m_nThreadID, WM_MYTHREAD_CREATE, 0, 0);

	return TRUE;
}

// ������֯���ڴ�С
void UEXP_Resize()
{
	OutputDebugString("UEXP_Resize begin\r\n");
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	//////////////////////////////////////////////////////////////////////////
	if (g_UIMessageLoopStart == FALSE)
	{
		OutputDebugString("UEXP_Resize ERROR !!!!!!\r\n");
		return;
	}

	if (g_TGChatDialog)
	{
  		g_TGChatDialog->UISetInitSize();
		g_TGChatDialog->PostMessage(UM_USER_UISETINITSIZE, 0, 0);
	}

	return;
}

// ����������
void UEXP_ChangeChat(DWORD roomid)
{
	OutputDebugString("UEXP_ChangeChat begin\r\n");
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	//////////////////////////////////////////////////////////////////////////
	if (g_TGChatDialog)
		g_TGChatDialog->ChangeChatRoom(roomid);
	else
		g_dwRoomID = roomid;
}

#endif