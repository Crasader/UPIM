#include "StdAfx.h"
#include "MyThread.h"
#include "MainPort.h"

//////////////////////////////////////////////////////////////////////////
// CMyThread
IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread(void)
{
}

CMyThread::~CMyThread(void)
{
}

BOOL CMyThread::InitInstance()
{
	return TRUE;
}

int CMyThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
END_MESSAGE_MAP()


// CMyThread ��Ϣ�������
BOOL CMyThread::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MYTHREAD_CREATE)
	{
		CreateDlg();
	}
	else if (pMsg->message == WM_MYTHREAD_DELALL)
	{
		PostQuitMessage(0);
	}
	else if (pMsg->message == WM_MYTHREAD_RESIZE)
	{
		Resize();
	}
	else if (pMsg->message == WM_MYTHREAD_INITMAIN)
	{
		InitMain();
	}

	return CWinThread::PreTranslateMessage(pMsg);
}

BOOL CMyThread::Resize()
{
	if (g_TGChatDialog)
		g_TGChatDialog->UISetInitSize();
	if (g_pCreateTG1)
		g_pCreateTG1->UISetInitSize();
	if (g_pCreateTG2)
		g_pCreateTG2->UISetInitSize();

	return TRUE;
}

BOOL CMyThread::ChangeRoom()
{
	return TRUE;
}

BOOL CMyThread::Init()
{
	CPaintManagerUI::SetCloseFlag(false);
	g_UIMessageLoopStart = TRUE;
	CPaintManagerUI::MessageLoop();

	return TRUE;
}

BOOL CMyThread::InitMain()
{
	if (!g_pFrame)
	{
		g_pFrame = new MainFrame();
		if( g_pFrame == NULL ) 
			return FALSE;

		g_pFrame->PostMessage(UM_UI_MESSAGELOOP, 0, 0);
	}
	return TRUE;
}

BOOL CMyThread::CreateDlg()
{
	InitRichEditCom();			// COM����
	// ����ͻ���δ��
	if (!g_pFrame)
	{
		// �Ƕ������ڣ������ڱ��ͻ��˵��õ����
		if (!g_bIndepend)
		{
			g_pFrame = new MainFrame();
			if( g_pFrame == NULL ) return FALSE;

			g_pFrame->Create(NULL, UPIM_SOFT_NAME, WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0, 0, 600, 800);
			if (g_pFrame)
			{
				g_pFrame->PostMessage(UM_UI_MESSAGELOOP, 0, 0);

				g_pFrame->StartLogin();		// LoginIN();
				g_pFrame->ShowWindow(false);
			}

			//////////////////////////////////////////////////////////////////////////
			CRect rectInit(0, 0, 0, 0);
			if(g_hVessel)	
				::GetClientRect(g_hVessel, &rectInit);

			FriendListItemInfo	myself_info_1;
			FriendListItemInfo	myself_info_2;
			if (!g_TGChatDialog)
			{
				g_TGChatDialog = new ChatDialog("", 0, myself_info_1, myself_info_2, eDIALOG_ChatTG);
				if( g_TGChatDialog)
				{
					//����child��˵��������top most���ڣ���SetWindowPos����Ҳ��û�õġ�
					g_TGChatDialog->Create(g_hVessel, "", WS_CHILD|WS_VISIBLE, NULL, rectInit);
					g_TGChatDialog->UISetInitSize();
				}

				//////////////////////////////////////////////////////////////////////////
				// ѡ�����ʦ
				g_pCreateTG1 = new CGeneralDialog("", 0, eCreate_TG1, _T(""));
				if( g_pCreateTG1)
				{
					g_pCreateTG1->Create(g_hVessel, "", WS_CHILD, NULL,  0, 0, 600, 800);
					g_pCreateTG1->ShowWindow(false);
					g_pCreateTG1->UISetInitSize();
				}

				//////////////////////////////////////////////////////////////////////////
				// ����û�з���ʦ
				g_pCreateTG2 = new CGeneralDialog("", 0, eCreate_TG2, _T(""));
				if( g_pCreateTG2 )
				{
					g_pCreateTG2->Create(g_hVessel, "", WS_CHILD, NULL,  0, 0, 600, 800);
					g_pCreateTG2->ShowWindow(false);
					g_pCreateTG2->UISetInitSize();
				}
			}
		}
	}
	return TRUE;
}