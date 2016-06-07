
// pbSysTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <vector>

// CpbSysToolApp:
// �йش����ʵ�֣������ pbSysTool.cpp
//


extern CString	DblToStr(double dblVal, int ndigits = 20);
extern CString	IntToStr(int nVal);
extern CString	LongToStr(long lVal);
extern CString	ULongToStr(unsigned long ulVal);
extern double   StrToOleDateTime(CString str);
extern CString  OleDateTimetoStr(double mdt,const char* pFormatstr);
extern CString  TransToDispatch(int distype);
extern int      UnTransToDispatch(CString);
extern CString  TransToTpRule(int distype);
extern int      UnTransToTpRule(CString);
extern CString  TransIntToStrTime(int ntime);
extern const char* GetErrorStr(int nError);
extern CRect    SetCtrlPos(int x,int y,int cx,int cy);
extern BOOL     ConnectDataBase(CADODatabase *Db);

const int COLLUMSIZE = 20;
const int USERID_SIZE = 32;
const int CTRLHEIGHT = 25;
const int EDITHEIGHT = 20;
const int LEFTINCREMENT = 30;
const int TOPINCREMENT  = 20;
const int VINCREMENT = 5;     //���¼��
const int HINCREMENT = 10;    //���Ҽ��
const int GRIDHEIGHT = 25;

typedef struct tagDBCONFIG
{
	DWORD	dwConnTimeOut;				// ���ݿ����ӳ�ʱ
	CHAR	szDataSource[32];			// ����Դ
	CHAR	szDataBase[32];				// ���ݿ�
	CHAR	szUserName[32];				// ���ݿ��û�
	CHAR	szPassword[32];				// ���ݿ�����
}DBCONFIG,*LPDBCONFIG;


enum{
	TP_TIME = 1,
	TP_PROBLEM,
	TP_INTERFACE,
	TP_CUSTOMERSERVICE,
	TP_OTHER
};
enum
{
	DISPATCH_MAX_IDLETIME = 1,
	DISPATCH_MIN_SESSIONTIME,
	DISPATCH_MAX_PRIORITY
};


enum E_GROUPCHAT_ERROR
{
	eGCError_NoDefine = -9999,		// δ����Ĵ�������
	eGCError_Success = 0,			// �ɹ�
	eGCError_DbCon = -1,			// û�п��õ����ݿ�����	 
	eGCError_DbExe = -2,			// ���ݿ�ִ��ʧ��
	eGCError_DbOp = -3,				// ���ݿ����ʧ��
	eGCError_Param = -4,            // �洢���̲�������
	eGCError_RsClose = -7,			// ��¼���ѹر�
	eGCError_RsNULL = -8,			// ��¼��Ϊ��
	eGCError_DbClose = -9           // ���ݿ�ر�
};

enum combo_operation{
	PUBLIC = 1
	,INCODE
	,TP
	,PUBLIC_TP_RELATION
	,TP_INCODE_RELATION
	,DISPATCH_RELATION
};

enum btn_operation{
	BTN_ADD = 1
	,BTN_MODIFY
	,BTN_DELETE
};
enum proctype{
	PUBLIC_ADD                          = PUBLIC<<BTN_ADD
	,PUBLIC_ADD_INCODE                  = INCODE<<BTN_ADD
	,PUBLIC_ADD_TP                      = TP<<BTN_ADD
	,PUBLIC_ADD_RELATION                = PUBLIC_TP_RELATION<<BTN_ADD
	,PUBLIC_ADD_TP_INCODE_RELATION      = TP_INCODE_RELATION<<BTN_ADD
	,PUBLIC_ADD_DISPATCH_RELATION       = DISPATCH_RELATION<<BTN_ADD
	,PUBLIC_MODIFY                      = PUBLIC<<(BTN_MODIFY*2)
	,PUBLIC_MODIFY_INCODE				= INCODE<<(BTN_MODIFY*2)
	,PUBLIC_MODIFY_TP					= TP<<(BTN_MODIFY*2)
	,PUBLIC_MODIFY_RELATION             = PUBLIC_TP_RELATION<<(BTN_MODIFY*2)
	,PUBLIC_MODIFY_TP_INCODE_RELATION	= TP_INCODE_RELATION<<(BTN_MODIFY*2)
	,PUBLIC_MODIFY_DISPATCH_RELATION	= DISPATCH_RELATION<<(BTN_MODIFY*2)
	,PUBLIC_DELETE                      = PUBLIC<<(BTN_DELETE*3)
	,PUBLIC_DELETE_INCODE				= INCODE<<(BTN_DELETE*3)
	,PUBLIC_DELETE_TP					= TP<<(BTN_DELETE*3)
	,PUBLIC_DELETE_TP_INCODE_RELATION	= TP_INCODE_RELATION<<(BTN_DELETE*3)
	,PUBLIC_DELETE_DISPATCH_RELATION	= DISPATCH_RELATION<<(BTN_DELETE*3)
};


class CpbSysToolApp : public CWinApp
{
public:
	CpbSysToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CpbSysToolApp theApp;