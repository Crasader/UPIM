/**
*   ViewBig.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ�ַŴ������ͼƬ�鿴����
*======================================================
*   �汾
*   Revision 1.0	2002/11/25    	  ʵ�ַŴ�鿴������
*/

#include "stdafx.h"
#include "..\\PaintDlg.h"
#include "..\\INCLUDE\\ViewBig.h"
#include "..\\INCLUDE\\GALLERYDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Ӧ�ó�������·��,��"c:\cph\"
extern  CString g_strAppPath;        
extern  IniPaintSet g_stuPaintSet;

/////////////////////////////////////////////////////////////////////////////
// CViewBig

CViewBig::CViewBig()
{
	m_pDib = new CDib();
	m_srcDib = new CDib();
	m_BigFrameDib = new CDib();

	m_strViewFileName = _T("");
	m_bBig = FALSE;

	//Ĭ��Ϊ�����߿�
	m_bFocus = FALSE;

	//Ĭ��û�д�����н��� 
	INT m_nIndex = 0;     
	
	// δ���߿�
	m_bDrawedFrm = FALSE;
	//��һ����ʾ
	m_bFirstView = TRUE;  
	
}

CViewBig::~CViewBig()
{
	if(m_pDib)
	{
		delete m_pDib;
		m_pDib = NULL;
	}

	if(m_srcDib)
	{
		delete m_srcDib;
		m_srcDib = NULL;
	}

	if(m_BigFrameDib)
	{
		delete m_BigFrameDib;
		m_BigFrameDib = NULL;
	}
}


BEGIN_MESSAGE_MAP(CViewBig, CWnd)
	//{{AFX_MSG_MAP(CViewBig)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewBig message handlers

int CViewBig::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	
	return 0;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	OnPaint
*  ��������		:	����ˢ�´�����
*  �����������	:	
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:   
*--------------------------------------------------------------------------------
*/
void CViewBig::OnPaint() 
{
	CPaintDC dc(this); 
	
	CRect rect;
	GetClientRect(&rect);

	CGALLERYDlg * pdlg = (CGALLERYDlg *)GetParent(); 


	m_srcDib->Load(m_strViewFileName); 
	if(m_strViewFileName != "")
	{  
		if(m_pDib)
			delete m_pDib;
		m_pDib = m_srcDib->Clone();
	}
	else
		return;

	//��һ����ʾȫ��9��ͼ�� 
	if(m_bFirstView)
	{
		m_pDib->ChangeImageSize(160,120);
		m_pDib->Display(&dc, 0, 0); 
        m_bFirstView = FALSE;
		m_bBig = FALSE;
		return;
	}
	if(m_bBig && m_bFocus)
	{
		rect.SetRect(0, 0, 592, 458);

	    CString faceFile = g_strAppPath + "\\UseRes\\face_frm.bmp";
		m_BigFrameDib->Load(faceFile); 
		CPoint point1;
		point1.x = 36;
		point1.y = 36;
		m_BigFrameDib->MergeDib(m_srcDib->GetHandle(), point1);
		 
		//��ʾ֮ǰ����������8������
	    ::PostMessage(GetParent()->GetSafeHwnd(), UWM_GETPREPICTURE, (long)this, 2);	
		m_BigFrameDib->Display(&dc, 0, 0); 
        this->MoveWindow(16, 58, 592 + 16, 458 +58,TRUE);
        m_bBig = TRUE;
	  //MoveWindow(&rect, TRUE);
 	}
	//������ʾͼ��
	else
	{   m_bBig = FALSE;
		m_pDib->ChangeImageSize(160,120);

			 TRACE("��ǰѡ��%d\n", m_nIndex);	
	  switch(m_nIndex)
		 {	

		  case 0:
			  {
				if(pdlg->GetPageNum() > 0)
					SetWindowPos(NULL, CRectRECT_IMG0.left ,CRectRECT_IMG0.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 1:
			  {	
				 if(pdlg->GetPageNum() > 1)
					SetWindowPos(NULL, CRectRECT_IMG1.left ,CRectRECT_IMG1.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 2:
			  {
				 if(pdlg->GetPageNum() > 2)
					SetWindowPos(NULL, CRectRECT_IMG2.left ,CRectRECT_IMG2.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 3:
			  {
				 if(pdlg->GetPageNum() > 3)
					SetWindowPos(NULL, CRectRECT_IMG3.left ,CRectRECT_IMG3.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 4:
			  {
				 if(pdlg->GetPageNum() > 4)
					SetWindowPos(NULL, CRectRECT_IMG4.left ,CRectRECT_IMG4.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 5:
			  {
				if(pdlg->GetPageNum() > 5)
					SetWindowPos(NULL, CRectRECT_IMG5.left ,CRectRECT_IMG5.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 6:
			  {
				if(pdlg->GetPageNum() > 6)
					SetWindowPos(NULL, CRectRECT_IMG6.left ,CRectRECT_IMG6.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 7:
			  {
				if(pdlg->GetPageNum() > 7)
					SetWindowPos(NULL, CRectRECT_IMG7.left ,CRectRECT_IMG7.top,160,120, SWP_SHOWWINDOW);
				break;
			  }
		  case 8:
			  {
				if(pdlg->GetPageNum() > 8)
					SetWindowPos(NULL, CRectRECT_IMG8.left ,CRectRECT_IMG8.top,160,120, SWP_SHOWWINDOW);
				break;
			  }

		  default:
			  break;
		 }//end switch

         m_pDib->Display(&dc, 0, 0); 
	}
     
	//������Ϣ����������֪ͨ�ƶ����嵽ָ��λ��
    // ::PostMessage(GetParent()->GetSafeHwnd(), UWM_GETPREPICTURE, (long)this, 1);		
	// Do not call CWnd::OnPaint() for painting messages
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	SetViewBitmap
*  ��������		:	���õ�ǰ����Ҫ��ʾ��ͼ��
*  �����������	:	CString strfile	 -  ͼ���ļ���
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:   
*--------------------------------------------------------------------------------
*/
void CViewBig::SetViewBitmap(CString strfile)
{
   m_strViewFileName = strfile;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	OnLButtonDown
*  ��������		:	������������Ϣ���ڴ˻���ǰ���ڵı߿�
*  �����������	:	UINT nFlags
*					CPoint point	-	��ǰ�����
*  ���ر���˵�� :	void
*  �㷨����		:	����ͼƬʱ��ͼƬ��Χ���ϱ߿�
*  ����˵�� 	:   ʹ��������ͼƬ���н���
*--------------------------------------------------------------------------------
*/
void CViewBig::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//�Ե�����ͼƬ��Χ���߿�
    m_bFocus = TRUE;
	if(!m_bBig)
    DrawFrame(TRUE);

	//������Ϣ�����Ի���֪ͨȡ������8������Ľ���״̬
    ::PostMessage(GetParent()->GetSafeHwnd(), UWM_GETPREPICTURE, (long)this, 0);

	CWnd::OnLButtonDown(nFlags, point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	SetBig
*  ��������		:	���õ�ǰ�����Ƿ�Ҫ�����ʾ
*  �����������	:	BOOL isBig	-	�Ƿ������ʾͼƬ
*  ���ر���˵�� :	void
*  �㷨����		:	
*  ����˵�� 	: 
*--------------------------------------------------------------------------------
*/
void CViewBig::SetBig(BOOL isBig)
{
  m_bBig = isBig;

}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	SetPrePos
*  ��������		:	���õ�ǰ�����������
*  �����������	:	INT index	-	��ǰ�����������
*  ���ر���˵�� :	void
*  �㷨����		:	
*  ����˵�� 	: 
*--------------------------------------------------------------------------------
*/
void CViewBig::SetPrePos(INT index)
{
	m_nIndex = index;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	DrawFrame
*  ��������		:	Ϊ��ǰ���廭�߿�
*  �����������	:	BOOL isDraw - ���߿��ǲ����߿�ı�־
*  ���ر���˵�� :	void
*  �㷨����		:	
*  ����˵�� 	: 
*--------------------------------------------------------------------------------
*/
void CViewBig::DrawFrame(BOOL isDraw)
{
    CDC * pDC = GetDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, g_stuPaintSet.tranCol); 
	CPen * OldPen = pDC->SelectObject(&pen);		
     
	m_point[0].x = 1;
	m_point[0].y = 1;	
	m_point[1].x = 159;
	m_point[1].y = 1;	
	m_point[2].x = 159;
	m_point[2].y = 119;	
	m_point[3].x = 1;
	m_point[3].y = 119;	
	m_point[4].x = 1;
	m_point[4].y = 1;	
	pDC->SetBkMode(TRANSPARENT); 
	//���߿�
	if(isDraw && !m_bBig)
	{
		pDC->Polyline(m_point, 5); 
        m_bDrawedFrm = TRUE;
	}
	//����Ϊ���ģʽ�ػ�һ����ȡ���ѻ��ľ���
	else if(!isDraw && m_bDrawedFrm && !m_bBig)
	{
		pDC->SetROP2(R2_NOTXORPEN); 
		pDC->Polyline(m_point, 5); 
        m_bDrawedFrm = FALSE;
	}

}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	GetPrePos
*  ��������		:	�õ���ǰ�����������
*  �����������	:	
*  ���ر���˵�� :	INT	- ��ǰ�����������
*  �㷨����		:	
*  ����˵�� 	: 
*--------------------------------------------------------------------------------
*/
INT CViewBig::GetPrePos()
{
    return m_nIndex;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	SetPreFocus
*  ��������		:	���õ�ǰ����
*  �����������	:	BOOL bFocus - �Ƿ���н���
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:	���н��㴰�����ܻ����߿�
*--------------------------------------------------------------------------------
*/
void CViewBig::SetPreFocus(BOOL bFocus)
{
	m_bFocus = bFocus;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	GetPreFocus
*  ��������		:	�õ���ǰ���㴰���������
*  �����������	:	
*  ���ر���˵�� :	BOOL -	���ھ��н��㷵�� TRUE, ���򷵻� FALSE
*  �㷨����		:	
*  ����˵�� 	:	
*--------------------------------------------------------------------------------
*/
BOOL CViewBig::GetPreFocus()
{
	return m_bFocus;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	DrawBig
*  ��������		:	�ڵ�ǰ�������Դ�ͼ��ʽ��ʾͼƬ
*  �����������	:	
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:	
*--------------------------------------------------------------------------------
*/
void CViewBig::DrawBig()
{
	m_bBig = TRUE;
	GetParent()->Invalidate(); 
    Invalidate(TRUE);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	DrawSmall
*  ��������		:	�ڵ�ǰ��������Сͼ��ʽ��ʾͼƬ
*  �����������	:	
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:	
*--------------------------------------------------------------------------------
*/
void CViewBig::DrawSmall()
{
	m_bBig = FALSE;
	GetParent()->Invalidate(); 
    Invalidate(TRUE);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	HideWnd
*  ��������		:	���ص�ǰ����
*  �����������	:	
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:	
*--------------------------------------------------------------------------------
*/
void CViewBig::HideWnd()
{
   this->ShowWindow(SW_HIDE); 
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������  	:	ShjowWnd
*  ��������		:	��ʾ��ǰ����
*  �����������	:	
*  ���ر���˵�� :	
*  �㷨����		:	
*  ����˵�� 	:	
*--------------------------------------------------------------------------------
*/
void CViewBig::ShowWnd()
{
   this->ShowWindow(SW_SHOW); 
}
