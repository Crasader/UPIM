
// pbSysTool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "pbSysTool.h"
#include "pbSysToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpbSysToolApp

BEGIN_MESSAGE_MAP(CpbSysToolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CpbSysToolApp ����

CpbSysToolApp::CpbSysToolApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CpbSysToolApp ����

CpbSysToolApp theApp;


// CpbSysToolApp ��ʼ��

BOOL CpbSysToolApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	//CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CpbSysToolDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
// 	if (pShellManager != NULL)
// 	{
// 		delete pShellManager;
// 	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



CString IntToStr(int nVal)
{
	CString strRet;
	char buff[10];

	_itoa(nVal, buff, 10);
	strRet = buff;
	return strRet;
}

CString LongToStr(long lVal)
{
	CString strRet;
	char buff[20];

	_ltoa(lVal, buff, 10);
	strRet = buff;
	return strRet;
}

CString ULongToStr(unsigned long ulVal)
{
	CString strRet;
	char buff[20];

	_ultoa(ulVal, buff, 10);
	strRet = buff;
	return strRet;

}

CString DblToStr(double dblVal, int ndigits)
{
	CString strRet;
	char buff[50];

	_gcvt(dblVal, ndigits, buff);
	strRet = buff;
	return strRet;
}

double StrToOleDateTime(CString str)
{
	COleDateTime time;
	CString syear,smonth,sday,shour,sminute,ssecond;
	INT year,month,day,hour,minute,second;
	if(str.GetLength() == 19)
	{
		syear = str.Mid(0,4);  year = StrToInt(syear);
		smonth = str.Mid(5,2); month = StrToInt(smonth);
		sday = str.Mid(8,2);   day = StrToInt(sday);
		shour = str.Mid(11,2); hour = StrToInt(shour);
		sminute = str.Mid(14,2); minute =StrToInt(sminute);
		ssecond = str.Mid(17,2); second = StrToInt(ssecond);
		time.SetDateTime(year,month,day,hour,minute,second);
	}
	return time.m_dt;
}


CString OleDateTimetoStr(double mdt,const char* pFormatstr)
{
	CString str=_T("");
	if (mdt>0)
	{
		COleDateTime time;
		time.m_dt = mdt;
		str = time.Format(pFormatstr);
	}
	return str;

}


CString TransToDispatch(int distype)
{
	CString str = (_T(""));
	switch (distype)
	{
	case DISPATCH_MAX_IDLETIME:
		str.Format(_T("������ʱ�����"));
		break;
	case DISPATCH_MIN_SESSIONTIME:
		str.Format(_T("��̻Ựʱ�����"));
		break;
	case DISPATCH_MAX_PRIORITY:
		str.Format(_T("������ȼ�����"));
		break;
	default:
		break;
	}
	return str;
}

int UnTransToDispatch(CString str)
{
	if(0 == strcmp(str,"������ʱ�����")) return DISPATCH_MAX_IDLETIME;
	if(0 == strcmp(str,"��̻Ựʱ�����")) return DISPATCH_MIN_SESSIONTIME;
	if(0 == strcmp(str,"������ȼ�����")) return DISPATCH_MAX_PRIORITY;
}

CString TransToTpRule(int distype)
{
	CString str = (_T(""));
	switch (distype)
	{
	case TP_TIME:
		str.Format(_T("ʱ��·��"));
		break;
	case TP_PROBLEM:
		str.Format(_T("����·��"));
		break;
	case TP_INTERFACE:
		str.Format(_T("�ӿ�·��"));
		break;
	case TP_CUSTOMERSERVICE:
		str.Format(_T("ָ���ͷ�·��"));
		break;
	case TP_OTHER:
		str.Format(_T("��չ·��"));
		break;
	default:
		break;
	}
	return str;
}

int UnTransToTpRule(CString str)
{
	if (0 == strcmp("ʱ��·��",str)) return TP_TIME;
	if (0 == strcmp("����·��",str)) return TP_PROBLEM;
	if (0 == strcmp("�ӿ�·��",str)) return TP_INTERFACE;
	if (0 == strcmp("ָ���ͷ�·��",str)) return TP_CUSTOMERSERVICE;
	if (0 == strcmp("��չ·��",str)) return TP_OTHER;
}

CString TransIntToStrTime(int ntime)
{
	CString strText=_T("");
	if (ntime>0)
	{
		int hour=0,minute=0,second=0;
		hour = ntime/10000;
		minute = (ntime/100)%100;
		second = ntime%100;
		strText.Format(_T("%02d:%02d:%02d"),hour ,minute,minute);
	}
	return strText;
}
const char* GetErrorStr(int nError)
{
	const char* error = NULL;
	switch(nError)
	{
	case eGCError_Success:
		error = "�ɹ�";
		break;
	case eGCError_DbCon:
		error = "û�п��õ����ݿ�����";
		break;
	case eGCError_DbExe:
		error = "���ݿ�ִ��ʧ��";
		break;
	case eGCError_DbOp:
		error = "���ݿ����ʧ��";
		break;
	case eGCError_Param:
		error = "�洢���̲�������";
		break;
	case eGCError_RsClose:
		error = "��¼���ѹر�";
		break;
	case eGCError_RsNULL:
		error = "��¼��Ϊ��";
		break;
	case eGCError_DbClose:
		error = "���ݿ�ر�";
		break;
	default:
		error = "δ����Ĵ�������";
		break;
	}
	return error;
}

CRect SetCtrlPos(int x,int y,int cx,int cy)
{
	CRect rc;
	POINT p;
	SIZE s;
	p.x = x;
	p.y = y;
	s.cx = cx;
	s.cy = cy;
	rc = CRect(p,s);
	return rc;
}

BOOL ConnectDataBase(CADODatabase *Db)
{
	LPDBCONFIG lpdbConfig = new DBCONFIG;	
	CHAR szHomePath[MAX_PATH],szCfgPath[MAX_PATH];
	GetModuleFileName( NULL, szHomePath, sizeof(szHomePath) );
	long nLen = strlen( szHomePath );
	for ( long loop=(nLen-1); loop>=0; loop-- )
	{
		if ( szHomePath[loop] == '\\' )
		{
			szHomePath[loop] = 0;
			break;
		}
	}
	nsprintf( szCfgPath, sizeof(szCfgPath), "%s\\pbSys.ini", szHomePath);
	lpdbConfig->dwConnTimeOut = GetPrivateProfileInt("dbconfig", "Conntimeout", 0, szCfgPath);
	GetPrivateProfileString("dbconfig", "DataSource", "",lpdbConfig->szDataSource,sizeof(lpdbConfig->szDataSource), szCfgPath);
	GetPrivateProfileString("dbconfig", "DataBase", "",lpdbConfig->szDataBase,sizeof(lpdbConfig->szDataBase), szCfgPath);
	GetPrivateProfileString("dbconfig", "UserName", "",lpdbConfig->szUserName,sizeof(lpdbConfig->szUserName), szCfgPath);
	GetPrivateProfileString("dbconfig", "Password", "",lpdbConfig->szPassword,sizeof(lpdbConfig->szPassword), szCfgPath);

	if(Db==NULL) return FALSE;
	Db->Close();
	CString	strConnect;
	strConnect.Format( "Provider=sqloledb;Data Source=%s;Network Library=DBMSSOCN;Initial Catalog=%s;",lpdbConfig->szDataSource, lpdbConfig->szDataBase);
	Db->SetConnectionTimeout(lpdbConfig->dwConnTimeOut);
	Db->Open( strConnect, lpdbConfig->szUserName, lpdbConfig->szPassword);
	delete lpdbConfig;
	return Db->IsOpen();
}