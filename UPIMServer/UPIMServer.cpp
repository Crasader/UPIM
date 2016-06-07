
// UPIMServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "UPIMServer.h"
#include "MainFrm.h"

#include "UPIMServerDoc.h"
#include "UPIMServerView.h"

// CUPIMServerApp
BEGIN_MESSAGE_MAP(CUPIMServerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CUPIMServerApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
END_MESSAGE_MAP()


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
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		CString strTime = _T("");
		strTime.Format("%04d_%02d_%02d_%02d%02d%02d%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		strDumpFileName.Format("\\log\\%s_Dump.dmp",strTime);
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
// CUPIMServerApp ����


CUPIMServerApp::CUPIMServerApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("UPIMServer.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CUPIMServerApp ����

CUPIMServerApp theApp;


// CUPIMServerApp ��ʼ��

BOOL CUPIMServerApp::InitInstance()
{
	CWinAppEx::InitInstance();


	SetErrorMode(1|2);

	LPTOP_LEVEL_EXCEPTION_FILTER pPrevFilter =  ::SetUnhandledExceptionFilter(MyExptFilter);  
	if(pPrevFilter != NULL)  
		_tprintf(_T("Previous exception filter exists.\n"));  
	else  
		_tprintf(_T("No Previous exception filter.\n")); 

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("UPIMSEVER_1.0.3.1_1"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MYMENU,
		RUNTIME_CLASS(CUPIMServerDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CUPIMServerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

// CUPIMServerApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CUPIMServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CUPIMServerApp �Զ������/���淽��

void CUPIMServerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CUPIMServerApp::LoadCustomState()
{
}

void CUPIMServerApp::SaveCustomState()
{
}


// CUPIMServerApp ��Ϣ�������
int CUPIMServerApp::ExitInstance()
{
	return CWinAppEx::ExitInstance();
}