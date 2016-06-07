#pragma once
#include "afxwin.h"

/*
 * CMyThread�������������̶߳Ի������.
 * Щ���������DLL�У�Ƕ��UP�ͻ���ʱʹ�ã�ʹ����Ϣѭ����Ӱ�첻�����̵߳���Ϣ��
 */
#define WM_MYTHREAD_INITMAIN	WM_USER + 6000
#define WM_MYTHREAD_CREATE		WM_USER + 6001
#define WM_MYTHREAD_DELALL		WM_USER + 6002
#define WM_MYTHREAD_RESIZE		WM_USER + 6003
#define WM_MYTHREAD_CLOSE		WM_USER + 6004

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread);
public:
	CMyThread(void);
	~CMyThread(void);

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL CreateDlg();
	BOOL Resize();
	BOOL ChangeRoom();
	BOOL Init();
	BOOL InitMain();
};

