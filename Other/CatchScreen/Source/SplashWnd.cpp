/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��Splash.cpp
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ�������������Splash����ģ���ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-11-24   9��00   ��ΰ
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"  
//#include "..\\resource.h"  
//#include "..\\INCLUDE\\Splash.h" 
#include "..\\resource.h"  
#include "..\\include\\Splashwnd.h"  
#include "..\\CPHDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


BOOL CSplashWnd::c_bShowSplashWnd;
CSplashWnd* CSplashWnd::c_pSplashWnd;

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CSplashWnd
*  ��������     :���캯��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CSplashWnd::CSplashWnd()
{
	//��time(1)�в��ŵ�FALSH�ļ�
	m_flashFile1 = _T("");
	//��time(1)�в��ŵ�FALSH�ļ�
	m_flashFile2 = _T("");
   //��ǰҪ���ŵ�time ID��
	m_timeID = 1;
  //����FLASHʱ�Ƿ��������������̼����˳�FALSH
	m_bKeyControl = TRUE;

}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :~CSplashWnd
*  ��������     :��������
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CSplashWnd::~CSplashWnd()
{
	// �����̬����ָ��
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :EnableSplashScreen
*  ��������     :ʹSplash������Ļ��Ч
*  �����������	:
*    BOOL bEnable������ΪTRUE��ʾ��Ч��������Ч
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :ShowSplashScreen
*  ��������     :��ʾSplash������Ļ����
*  �����������	:
*    CString flashfile1: Ҫ���ŵ�flash�ļ�1
*    CString flashfile2: Ҫ���ŵ�flash�ļ�2
*    INT timeID        : ���ĸ�TIME�̺߳��д�flash�ļ�1
*    BOOL isCloseMainFrm :������FLASH���Ƿ�ر�������
*    CWnd* pParentWnd  ��Splash��������ĸ�����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CSplashWnd::ShowSplashScreen(CString flashfile1, CString flashfile2/* = _T("")*/, INT timeID/* = 1*/, BOOL isKeyControl /*= TRUE*/, 
								  BOOL isCloseMainFrm /*=FALSE*/, CWnd* pParentWnd/* = NULL*/)
{
	
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// ����һ���µ�splash���ڲ������������.

	c_pSplashWnd = new CSplashWnd;
	c_pSplashWnd->m_flashFile1 = flashfile1;
	c_pSplashWnd->m_flashFile2 = flashfile2;
    c_pSplashWnd->m_timeID = timeID;
    c_pSplashWnd->m_bKeyControl = isKeyControl;
	c_pSplashWnd->m_isCloseMainWnd = isCloseMainFrm;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PreTranslateAppMessage
*  ��������     :�õ�Ӧ�ó������Ϣ������
*  �����������	:
*   MSG* pMsg����Ϣָ��
*  ���ر���˵�� :����TRUE��ʾ��Ϣ����ɹ�������ʧ��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// ���������м�������������splash��Ļ.
	if(c_pSplashWnd->m_bKeyControl)
	{
		if (pMsg->message == WM_KEYDOWN ||
			pMsg->message == WM_SYSKEYDOWN ||
			pMsg->message == WM_LBUTTONDOWN ||
			pMsg->message == WM_RBUTTONDOWN ||
			pMsg->message == WM_MBUTTONDOWN ||
			pMsg->message == WM_NCLBUTTONDOWN ||
			pMsg->message == WM_NCRBUTTONDOWN ||
			pMsg->message == WM_NCMBUTTONDOWN)
		{
			c_pSplashWnd->HideSplashScreen();
			return TRUE;	
		}
	}
	else 
	{
			if (pMsg->message == WM_RBUTTONDOWN)
			{
				c_pSplashWnd->HideSplashScreen();
				return TRUE;	
			}

	}
	return FALSE;	
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Create
*  ��������     :
*  �����������	:
*    CWnd* pParentWnd��Splash��������ĸ�����
*  ���ر���˵�� :����TRUE��ʾ�����ɹ��������ʾ����ʧ��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CSplashWnd::Create( CWnd* pParentWnd)
{
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, 800, 600, pParentWnd->GetSafeHwnd(), NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :HideSplashScreen
*  ��������     :����Splash��Ļ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CSplashWnd::HideSplashScreen()
{
	//�����������ͬʱ�������Ի��򴰿�.
	if(c_pSplashWnd->m_isCloseMainWnd)
	{
		DestroyWindow();
		AfxGetMainWnd()->DestroyWindow();
	}
	//����������ڲ��������Ի��򴰿�.
	else
	{
		DestroyWindow();
		AfxGetMainWnd()->UpdateWindow();
	}




}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PostNcDestroy()
*  ��������     :����Splash��������ʱ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CSplashWnd::PostNcDestroy()
{
	delete this;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnCreate
*  ��������     :����������ʱ���޸Ĵ������͵Ȳ���������Splash����ʾʱ��
*  �����������	:
*   LPCREATESTRUCT lpCreateStruct���������ͽṹ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ھ���
	CenterWindow();

   //����Flash�ؼ�����

    m_startflash.Create (NULL,WS_CHILD|WS_VISIBLE,CRect(0, 0, 800, 600),
		                this, 1024);
    
	//������ʾ��һ��Flash����
 	SetTimer (1, 0, NULL);
	//������ʾ�ڶ���Flash����(�ݲ���)
    //SetTimer (2, 12000, NULL);
	//ͬʱ����֡��¼
    SetTimer (3, 2000, NULL);
	CRect m_rect;
    GetClientRect (&m_rect );
   
    //ʹflash������ʾ���ӵ�������    
	m_startflash.MoveWindow (&m_rect);

	return 0;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnPaint()
*  ��������     :����Splash��������
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnTimer
*  ��������     :��ʱ�����ڿ��������������ʾʱ��
*  �����������	:
*   UINT nIDEvent����ʱ�������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CSplashWnd::OnTimer(UINT nIDEvent)
{
  CCPHDlg * maindlg = (CCPHDlg *)AfxGetMainWnd();  
  
  char *a=new char [512];
  GetCurrentDirectory (100,a);
  CString  *s=new CString(a);

  //���ŵ�һ��flash�ļ�
  if (nIDEvent ==1)
  {	
	  m_startflash.LoadMovie (0, *s+CString("\\") + m_flashFile1);
	  m_startflash.SetLoop(FALSE); 
	  m_startflash.Play();
	  KillTimer (1);
  }
  //���ŵڶ���flash�ļ�(�ݲ���)
  if (nIDEvent==2)
  {    
	  m_startflash.StopPlay ();
	  m_startflash.LoadMovie(0, *s+CString("\\") + m_flashFile2);
      m_startflash.Play();
  
      KillTimer (2);
 	  HideSplashScreen();
  }
  //����splash����
  if(nIDEvent==3)
  {	
	  INT num = m_startflash.CurrentFrame();
	  //�����ǹرմ���FLASH
	  if(m_isCloseMainWnd)
	  {
	    if(num >= 79)
		  {
	        
	         //HideSplashScreen();
             KillTimer (3);
			 delete a;
			 delete s;
			 return;
			 
		  }
	  }
	  //���������FLASH
	 else if(num >= 170)
	 {  
		 KillTimer (3);	
         ShowWindow(SW_HIDE);
	     
	 }


  }
  delete a;
  delete s;
  CWnd ::OnTimer (nIDEvent );

}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PreCreateWindow
*  ��������     :����Splash��������������ǰ�޸Ĵ��ڵ�����
*  �����������	:
*   CREATESTRUCT& cs�����ڵ����ͽṹ��
*  ���ر���˵�� : ����TRUE��ʾ�޸ĳɹ�
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CSplashWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
//		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOWTEXT), NULL);
    ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOWTEXT), NULL);
	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetFlashFileName
*  ��������     :����Splash��������������ǰ�޸Ĵ��ڵ�����
*  �����������	:
*   CString filename1:�ڵ�һ�׶β��ŵ�Flash�ļ���
*   CString filename2:�ڵڶ��׶β��ŵ�Flash�ļ���(����Ϊ��)
*  ���ر���˵�� : 
*  �㷨����		:
*  ����˵��     :������Ϊ��̬���ã��ú��������ã�����Ϊ��̬����splash����ʱ���ɵ���
*--------------------------------------------------------------------------------
*/
void CSplashWnd::SetFlashFileName(CString filename1, CString filename2 /* = NULL*/)
{
   m_flashFile1 = filename1;
   m_flashFile2 = filename2;	
}
