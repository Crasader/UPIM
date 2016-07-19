#include "StdAfx.h"
#include "MyClient.h"
#include "UI/MainFrame.h"
#include "globalvar.h"
#include "Func.h"
#include "MainPort.h"
#include "UI/Utils.h"
#include "LoadDllFunc.h"
#include "ProcessAns.h"


//////////////////////////////////////////////////////////////////////////



// 123 obaby
//D68r3cXNJdPlfh+M6ZPP2JT7jnHE1PkWabGAI6ucwXMdSkCkEROlK+uzUIJg7eldTQWTUC7Cz3QquJIcbJf2eA==

// 123456 lhl
//SZyqhQM1O/w2QWCZhVwD+ZT7jnHE1PkWabGAI6ucwXMdSkCkEROlK2fa/qIUfCWE7ZMKLlfpXe67XJ7NU3FRPQ==
// ��ʼ����
VOID InitConnect()
{
#ifdef VER_UPIM_RONGYUN
	CString strUserFolder = "";
	strUserFolder.Format("%s\\UPIMUser\\", g_config.szHomePath);
	CreateDirectory(strUserFolder, NULL);
	CHAR szUserDir[MAX_PATH] = {0};
	nsprintf(szUserDir, sizeof(g_config.szUserDir), "%s\\UPIMUser", g_config.szHomePath);
	WCHAR * IMPath = Utf8ToUnicode(szUserDir);
	g_RongCloudDll.m_pInitClient("pgyu6atqyliru", "IM.WINFORM", "deviceId",IMPath,IMPath); //vnroth0krxiwo
	delete IMPath;
	g_RongCloudDll.m_pSetDeviceInfo("Apple", "iPhone 6 Simulator", "8.1.1", "WIFI", "");
	//char szToken[] = {"SZyqhQM1O/w2QWCZhVwD+ZT7jnHE1PkWabGAI6ucwXMdSkCkEROlK2fa/qIUfCWE7ZMKLlfpXe67XJ7NU3FRPQ==" };
	g_RongCloudDll.m_pConnect(g_strToken, (ConnectAckListenerCallback)&connectCallback,false);//g_strToken

	g_RongCloudDll.m_pRegisterMessageType("RC:TxtMsg", 3);
	//ͼƬ��Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:ImgMsg", 3);
	//ͼ����Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:VcMsg", 3);
	//λ����Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:LBSMsg", 3);
	//�����ϵ����Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:ContactNtf", 3);
	//��ʾ����С������֪ͨ��Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:InfoNtf", 3);
	//����֪ͨ��Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:ProfileNtf", 3);
	//ͨ������֪ͨ��Ϣ
	g_RongCloudDll.m_pRegisterMessageType("RC:CmdNtf", 3);

	//������Ϣ����
	g_RongCloudDll.m_pSetMessageListener(message_callback);

	//���������쳣����
	g_RongCloudDll.m_pSetExceptionListener(exception_callback);

#else
	if (g_MyClient.m_bConnect)			//��������ӣ�����
		return;
	g_MyClient.InitClient();
	int nMainSvr = g_config.nMainHost;
	CString strAddress = g_config.aHostCfg[nMainSvr].szSVRIP;
	USHORT usPort = (USHORT)g_config.aHostCfg[nMainSvr].dwSVRPORT;

	BOOL bConnect = g_MyClient.StartClient(strAddress, usPort, FALSE);
	if (bConnect)
	{
		g_MyClient.m_bConnect = TRUE;
		USER_LOG("Socket Connect OK! [ConnID:%d]", g_MyClient.m_Client.GetConnectionID());
	}
	
#endif
	return;
}

// ������
VOID ReConnect()
{
	if (!g_MyClient.m_bMainWndClose)
	{
		// �����¼�ɹ����������ص�¼
		if (g_MyClient.m_bLoginSuccess)
		{
			g_MyClient.InitClient();
			int nMainSvr = g_config.nMainHost;
			CString strAddress = g_config.aHostCfg[nMainSvr].szSVRIP;
			USHORT usPort = (USHORT)g_config.aHostCfg[nMainSvr].dwSVRPORT;

			if (g_MyClient.m_strUserid.IsEmpty())
			{
				::MessageBox(NULL, _T("IM�������ʧ�ܣ��������µ�¼�ͻ��ˣ�"), _T("��ʾ"), MB_OK);
				return;
			}

			BOOL bConnect = g_MyClient.StartClient(strAddress, usPort, FALSE);
			if (bConnect)
			{
				USER_LOG("Socket ReConnect OK:%d", g_MyClient.m_Client.GetConnectionID());
				g_MyClient.SendReconnentReq();
				g_MyClient.m_bConnect = TRUE;
			//	g_pFrame->PostMessage(UM_USER_ONLINE, 0, 0);
			}
		}
	}
	return;
}

// ����richedit��gif֧��
VOID InitRichEditCom()
{
	USER_LOG("InitRichEditCom Start!");

	CString strFileName = "";
	strFileName.Format("%s\\IMGOle.dll", g_config.szHomePath);
	BOOL bRet = DllRegisterServer(strFileName);	// ע��COM���
	if (!bRet)
	{
		USER_LOG("IMGOle ERROR - path [%s]", strFileName);
		::MessageBox(NULL, _T("COM���ע��ʧ�ܣ�Ӧ�ó����޷���ɳ�ʼ��������"), _T("��ʾ"), MB_OK);
		return;
	}

	BOOL bAfxInitRichEdit = ::AfxInitRichEdit();
	HRESULT hrCoInitialize = ::CoInitialize(NULL);
	if (FAILED(hrCoInitialize)) 
	{
		USER_LOG("CoInitialize ERROR - [%s]", HrToMessage(hrCoInitialize));
		::MessageBox(NULL, _T("CoInitializeʧ�ܣ�Ӧ�ó����޷���ɳ�ʼ��������"), _T("��ʾ"), MB_OK);
		return;
	}

	HRESULT hrOleInitialize = ::OleInitialize(NULL);
	if (FAILED(hrOleInitialize))
	{
		USER_LOG("OleInitialize ERROR - [%s]", HrToMessage(hrOleInitialize));
		::MessageBox(NULL, _T("OleInitializeʧ�ܣ�Ӧ�ó����޷���ɳ�ʼ��������"), _T("��ʾ"), MB_OK);
		return;
	}
	Gdiplus::Status gdistatus = GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);	// ��ʼ��GDI+
	HMODULE g_hRichEditDll = ::LoadLibrary(_T("Riched20.dll"));		// ����RichEdit�ؼ�DLL

	return;
}

// ж��
VOID UnInitRichEditCom()
{
	::CoUninitialize();
	::OleUninitialize();

 	if (g_hRichEditDll != NULL)					// ж��RichEdit�ؼ�DLL
 		::FreeLibrary(g_hRichEditDll);
 
 	Gdiplus::GdiplusShutdown(g_gdiplusToken);	// ����ʼ��GDI+
}

// ��¼
VOID LoginIN()
{
	InitConnect();				// ���ӷ�����
	g_MyClient.SetClientInfo(eUser_Broker);
	g_MyClient.SendCheckPwdReq("3150", "21218cca77804d2ba1922c33e0151105", eLogin_Emp);
	
//	g_MyClient.SetClientInfo(eUser_Client);
//	g_MyClient.SendCheckPwdReq("069000000412", STR_NOCHECKPWD, eLogin_Client);
}

// ֹͣ
VOID StopConnect()
{
#ifndef VER_UPIM_RONGYUN
	g_MyClient.m_bMainWndClose = TRUE;
	g_MyClient.StopClient();
#endif
	return;
}

// ��ʼ�����ڣ�����������
VOID InitMainFrame()
{
	if (g_pFrame)
		return;
	g_pFrame = new MainFrame();
	if( g_pFrame == NULL ) return;
	// �ͻ� 
	if(VER_UPIM_NUMS == 4 )
	{
		g_pFrame->Create(NULL,_T("UPIM 2015"), WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0, 0, 600, 800);
	}
	else if (5 == VER_UPIM_NUMS)
		g_pFrame->Create(NULL,_T("UPIM 2016"), WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0, 0, 600, 800);
	else 
	{
		// ����ʦ�������汾 
		g_pFrame->Create(NULL,_T("UPIM_FXS 2015"), WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0, 0, 600, 800);
	}
 	g_pFrame->CenterWindow();

// 	//////////////////////////////////////////////////////////////////////////
// 	if (g_pFrame)
// 	{
// #ifdef VER_UPIM_ANALYS2
// 		g_pFrame->UpdateMyselfInfo(&g_selfunit, "����");
// 		g_pFrame->PostMessage(UM_USER_SETSELFINFO, 0, 0);
// #elif defined VER_UPIM_RONGYUN
// 		g_pFrame->UpdateMyselfInfo(&g_selfunit, "����");
// 		g_pFrame->PostMessage(UM_USER_SETSELFINFO, 0, 0);
// #else
// 		g_pFrame->UpdateMyselfInfo(&g_selfunit, "UPIM");
// 		g_pFrame->PostMessage(UM_USER_SETSELFINFO, 0, 0);
// #endif // VER_UPIM_ANALYS2
// 	}

	g_pFrame->StartLogin();

	return;
}

// �򿪸�ĳ�˵ĻỰ����
VOID OpenChatWnd(CString strUID, int nType)
{
	if (!g_pFrame)
		InitMainFrame();
	memset(g_szOpenUID, 0, sizeof(g_szOpenUID));
	strncpy(g_szOpenUID, strUID, strUID.GetLength());
	g_pFrame->PostMessage(UM_USER_OPENWND, (WPARAM)nType, (LPARAM)0);
	return;
}