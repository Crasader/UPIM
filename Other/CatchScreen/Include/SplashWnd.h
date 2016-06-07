/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��Splash.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ�������������Splash����ͷ�ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-11-24   9��00   
*
* 
*/
/*ʹ�÷���:
1.��Ӧ���������ģ���м�����룬��ʵ������Splash����
  ������Spalsh���з�װ�˶����ļ�������Ҫ������Ӧ�࣬ʵ�ֶ�ָ̬���ļ�
  //��װʱ��swflash.ocx�ļ�������windows\system·����
	TCHAR szDir [MAX_PATH];
	::GetSystemDirectory (szDir, MAX_PATH);
	//TRACE("Windows ϵͳĿ¼Ϊ%s\n", szDir);
    CString syspath = szDir;
    syspath = syspath + _T("\\swflash.ocx");
    
	//ע��flash�Ŀؼ�
	HMODULE	hmod=LoadLibrary (syspath);
	FARPROC  p=GetProcAddress (hmod,"DllRegisterServer");
	(*p)();

//	OnRegocx("swflash.ocx") ;
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}

2. ��Ҫʹ��Splash��������ĺ�����ֻ��������һ��
        //���������ŵĵ�һ��Splash�ļ���,���Ų��ŵĵڶ���Splash�ļ���,���ĸ�TIME�̺߳��д�flash�ļ�1,
       //       ������FLASH���Ƿ�ر�������,Splash��������ĸ�����
    CString swfFile = g_strAppPath + "\\UseRes\\startup.swf";
	CSplashWnd::ShowSplashScreen(swfFile, _T(""), 1, TRUE, FALSE, this);	

3.��2�п���Ҫ����һ���������ö��������������Ա㵽�������ʱ�Զ��رմ���










*/
/////////////////////////////////////////////////////////////////////////////

#ifndef _SPLASH_SCRN_
#define _SPLASH_SCRN_

#include "shockwaveflash.h"
/////////////////////////////////////////////////////////////////////////////
/*
*����:CShockwaveFlash
*˵������ʾSplash�����ļ�������
*�����¼��
*
*/

class CSplashWnd : public CWnd
{
// Construction
protected:
	CSplashWnd();

// Attributes:
public:

   //Flash�ؼ��������
   CShockwaveFlash  m_startflash;

// Operations
public:
	static void EnableSplashScreen(BOOL bEnable = TRUE);
	static void ShowSplashScreen(CString flashfile1, CString flashfile2 = _T(""), 
		                         INT timeID = 1, BOOL isKeyControl = TRUE, BOOL isCloseMainFrm = FALSE, 
								 CWnd* pParentWnd = NULL);
	static BOOL PreTranslateAppMessage(MSG* pMsg);
	void SetFlashFileName(CString filename1, CString filename2 = _T(""));

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:

	~CSplashWnd();
	virtual void PostNcDestroy();

protected:
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	static BOOL c_bShowSplashWnd;
	static CSplashWnd* c_pSplashWnd;

// Generated message map functions
protected:
	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
 	CString m_flashFile1;
 	CString m_flashFile2;
	INT m_timeID;
	BOOL m_bKeyControl;
	BOOL m_isCloseMainWnd;
};


#endif
