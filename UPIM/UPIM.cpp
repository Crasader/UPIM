
// UPIM.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "UPIM.h"
#include "MyClient.h"
#include "LoginDlg.h"
#include "UI/MainFrame.h"
#include "MainPort.h"
#include "Func.h"
#include "LoadDllFunc.h"

#ifdef _EXE_MODE
BEGIN_MESSAGE_MAP(CUPIMApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CUPIMApp::CUPIMApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	m_hMutex = NULL ; 
}

CUPIMApp theApp;

//////////////////////////////////////////////////////////////////////////
// Create Dump File
#include <dbghelp.h>  
#pragma comment(lib,  "dbghelp.lib")

LONG WINAPI MyExptFilter(EXCEPTION_POINTERS *pExptInfo)  
{  
	LONG ret = EXCEPTION_CONTINUE_SEARCH;  
	TCHAR szExePath[MAX_PATH] = {0};  
	if(::GetModuleFileName(NULL, szExePath, MAX_PATH) > 0)  
	{  
		int ch = _T('\\');  
		*_tcsrchr(szExePath, ch) = _T('\0');  

		CString strDumpFileName ;
		strDumpFileName.Format("\\log\\%s_Dump.dmp", g_config.szRunTime);
		_tcscat(szExePath, strDumpFileName);  
	}  

	// �������ʱ����д�����Ŀ¼�µ�MyDump.dmp�ļ�  
	HANDLE hFile = ::CreateFile(szExePath, GENERIC_WRITE,   
		FILE_SHARE_WRITE, NULL, CREATE_NEW,   
		FILE_ATTRIBUTE_NORMAL, NULL );  
	if(hFile != INVALID_HANDLE_VALUE)  
	{  
		MINIDUMP_EXCEPTION_INFORMATION exptInfo;  
		exptInfo.ThreadId = ::GetCurrentThreadId();  
		exptInfo.ExceptionPointers = pExptInfo;  

		BOOL bOK = ::MiniDumpWriteDump(::GetCurrentProcess(),  
			::GetCurrentProcessId(),   
			hFile, MiniDumpNormal,  
			&exptInfo, NULL, NULL);  
		if(bOK)  
			ret = EXCEPTION_EXECUTE_HANDLER;  
	}  

	return ret;  
} 

//////////////////////////////////////////////////////////////////////////

BOOL CUPIMApp::InitInstance()
{
	CWinApp::InitInstance();

	HINSTANCE hInstance = GetModuleHandle(NULL);
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	LoadConfig();				// ���������ļ�

#ifdef IM_EXE_TO_UP
	// �ͻ���̳е���ȫ��ʿ�������������ʱ��Ҫ��ֻ������IMһ��
	// ������������ 
	if( 4 == VER_UPIM_NUMS )
	{
		// ϵͳ���е�exeĿ¼����
		CString strHomePath = _T("") ;
		strHomePath.Format("%s" ,g_config.szHomePath) ; 
		if( strHomePath.Right(1) != "\\")
			strHomePath+="\\" ;

		CString tempMutexStr  = _T("") ;
		tempMutexStr = strHomePath + "UPIM_kh.exe" ; 
		tempMutexStr.Replace("\\" ," ") ; 
		// �ͻ���̳е���ȫ��ʿ�������������ʱ��Ҫ��ֻ������IMһ��
		// ������������ 
		m_hMutex = CreateMutex(NULL ,FALSE ,UPIM_CLIENT_MUTEX) ; 
		DWORD iRet = GetLastError() ; 
		if( m_hMutex == NULL ||iRet == ERROR_ALREADY_EXISTS)
		{
			//::MessageBox(NULL ,_T("һ��Ŀ¼����ֻ������һ���ó���"),_T("��ʾ") ,MB_OK|MB_ICONERROR) ; 
			// ϵͳ����ʵ�� 
			CloseHandle(m_hMutex) ; 
			m_hMutex = NULL ;
			return FALSE ; 
		}
	}
#endif 
	// ���������������exe��ģʽ������Ҫ�жϴ��������ֱ�Ӵ��޷�����
#ifdef VER_UPIM_CLIENT
	//////////////////////////////////////////////////////////////////////////
	// ��󣺽�ĵ������������ٴ�	
	// ��󣺻���Ͷ��
	// ���ڿͻ�exe����ģʽ����Ҫ��δ����� ���û���/�г���
	//CCommandLineInfo cmdInfo;//����������
	//ParseCommandLine(cmdInfo);//����������
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	//if (!ProcessShellCommand(cmdInfo)) //��������ʱ�������ĵ�
	//	return FALSE;
#ifndef IM_EXE_TO_UP
	COPYSTRARRAY(g_loginname, g_config.szLoginName/*"laifuwei"*/); 
	g_nMarket = g_config.dwMarket;
#else 
	DWORD t1 = GetTickCount() ; 
	USER_LOG("UP�������ʱ��:%d" ,t1 );
	// wuchao add at 20160322  UP����IM���̣� UP���û����������������û�����¼  
	// ���������ж�ȡUP���������û���
	// �������Ĳ�����ʽΪ�� "dir"username#nMarketID  wuchao modify at 20160418 
	CString strCommand = ::GetCommandLine() ; 
	USER_LOG("UP������������IM����%s" ,strCommand) ;

	int index = strCommand.ReverseFind('\"') ;
	if(index == -1 )
	{
		USER_LOG("����UP���������û�������") ; 
		return FALSE ; 
	}
	USER_LOG("\"���ֵ�λ�ã�%d" ,index);

	// ���û������г�ID��������username#nMarketID
	int strCommandLength = strCommand.GetLength() ; 
	CString strNameMarket = strCommand.Right(strCommandLength - index - 1 ) ;
	strNameMarket.Trim() ; 

	CString strUserName ;  // �û��� 
	CString strUserID ;    // �û�ID  
	CString strMarketID ;  // �г����� 
	
	USER_LOG("strNameMarket��%s" ,strNameMarket) ; 
	// ����#�ų��ֵ�λ�� 
	int nNetIndex = strNameMarket.Find('#') ; // #���ֵ�λ��
	if( nNetIndex == -1 )
	{
		USER_LOG("û���г����� ����UP��ȫ��ʿ��InvestAdviserView.cpp 1282��") ;
		return FALSE ; 
	}
	USER_LOG("#���ֵ�λ��:%d" ,nNetIndex) ; 

	AfxExtractSubString(strUserName,(LPCTSTR)strNameMarket ,0,'#') ;
	AfxExtractSubString(strUserID,(LPCTSTR)strNameMarket ,1,'#') ;
	AfxExtractSubString(strMarketID,(LPCTSTR)strNameMarket ,2,'#') ; 

	if( !strUserName.IsEmpty())
		USER_LOG("�û���%s",strUserName) ;
	else
	{
		USER_LOG("�޷���ȡ�û���") ;
		return FALSE ; 
	}
	if( !strUserID.IsEmpty())
	{
		USER_LOG("�û�ID %s" ,strUserID) ; 
	}
	else
	{
		USER_LOG("�޷���ȡ�û���") ;
		return FALSE ; 
	}
	if( !strMarketID.IsEmpty())
		USER_LOG("�г�����%s",strMarketID) ;
	else
	{
		USER_LOG("�޷���ȡ�г�����") ;
		return FALSE ; 
	}

	
	COPYSTRARRAY(g_loginname, strUserName.GetBuffer());
	COPYSTRARRAY(g_khID, strUserID.GetBuffer()) ; 

	USER_LOG("g_loginname = %s " ,g_loginname) ;
	USER_LOG("g_khID = %s " ,g_khID) ;

	// wuchao add at 20160418  
	// ����UP���������û������г�ID  
	int nMarkeID = atoi(strMarketID.GetBuffer()) ;

	if( nMarkeID == 3 )
		g_nMarket = 3 ; 
	else 
		g_nMarket = g_config.dwMarket; 
#endif 
	
#endif // VER_UPIM_CLIENT

	//////////////////////////////////////////////////////////////////////////
	LPTOP_LEVEL_EXCEPTION_FILTER pPrevFilter =  ::SetUnhandledExceptionFilter(MyExptFilter);  
	if(pPrevFilter != NULL)  
		_tprintf(_T("Previous exception filter exists.\n"));  
	else  
		_tprintf(_T("No Previous exception filter.\n")); 
	//////////////////////////////////////////////////////////////////////////

	InitRichEditCom();			// COM����
	LoadDLLFunc();				// ����DLL

	CShellManager *pShellManager = new CShellManager;
	SetRegistryKey(_T("UPIM"));
	InitMainFrame();

	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();
	
 	if (pShellManager != NULL){	delete pShellManager;}


	return FALSE;
}

int CUPIMApp::ExitInstance()
{
	::CoUninitialize();
	::OleUninitialize();
	if( m_hMutex )
	{
		ReleaseMutex(m_hMutex) ; 
		CloseHandle(m_hMutex) ; 
		m_hMutex = NULL ; 
	}
	UnLoadDLLFunc();		// ж��DLL
	UnInitRichEditCom();	// ж��COM
	StopConnect();			// �Ͽ�����
	
	return CWinApp::ExitInstance();
}

#endif // _EXE_MODE