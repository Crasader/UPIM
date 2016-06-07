/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��ColorPen.cpp 
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ������������ڵ�ɫ���ϵ�ȡɫ�ؼ���ģ���ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-11-5   11:00  ��ΰ  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "..\Include\ColorPen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPen
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CColorPen()    ~CColorPen()
*  ��������     :���캯��       ��������
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/

CColorPen::CColorPen()
{
	m_bsuckepen=TRUE;
    m_bSelect=FALSE;
	m_ID=0;
}

CColorPen::~CColorPen()
{
}


BEGIN_MESSAGE_MAP(CColorPen, CWnd)
	//{{AFX_MSG_MAP(CColorPen)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPen message handlers
//////////////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnLButtonDown
*  ��������     :������ڿؼ��ϰ���ʱ
*  �����������	:
*   UINT nFlags��
*   CPoint point��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CColorPen::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    //�õ���ǰ����ɫ
     if (m_bsuckepen)
			{
				CRect rc;
				GetClientRect(&rc);
				rc.InflateRect(-2,-2);
				if (PtInRect(&rc,point))
				{
					CClientDC dc(this);
					m_pencolor = dc.GetPixel(point);
					m_bSelect=TRUE;
					::PostMessage(GetParent()->GetSafeHwnd(), UWM_SHOWPENCOLOR1, (long)this,0);
				}
				 
	 }//end if
	CWnd::OnLButtonDown(nFlags, point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnSetCursor
*  ��������     :������ڿؼ���ʱ��ʾ�Ĺ����ʽ
*  �����������	:
*     CWnd* pWnd:
*     UINT nHitTest:
*     UINT message:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
BOOL CColorPen::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	if(m_bsuckepen)
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURPICKER));
    	return TRUE;
	}
	else 
	{
     //	SetCursor(LoadCursor(NULL,IDC_ARROW));   //���������Ϊ��ͷ
	SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));   //���������Ϊ��ͷ
	}
	*/
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CColorPen::OnMouseHover(WPARAM wParam,  LPARAM)
{
	CRect rc,rc1,rc2;
	GetClientRect(rc);
	rc1.CopyRect(rc);
	rc2.CopyRect(rc);
	rc1.InflateRect(-1,-1);
	rc2.InflateRect(-2,-2);
	CClientDC dc(this);
	
	CPoint point(rc2.left+3,rc2.top+3);
	m_pencolor = dc.GetPixel(point);
	dc.FillSolidRect(rc,RGB(51,91,145));
	dc.FillSolidRect(rc1,RGB(255,255,255));
	dc.FillSolidRect(rc2,m_pencolor);
	return 0;
}

LRESULT CColorPen::OnMouseLeave(WPARAM wParam,  LPARAM)
{
	CRect rc,rc1,rc2;
	GetClientRect(rc);
	rc1.CopyRect(rc);
	rc2.CopyRect(rc);
	rc1.InflateRect(-1,-1);
	rc2.InflateRect(-2,-2);
	CClientDC dc(this);
	dc.FillSolidRect(rc,RGB(222,238,255));
	dc.FillSolidRect(rc1,RGB(51,91,145));
	dc.FillSolidRect(rc2,m_pencolor);
	return 0;
}

void CColorPen::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT csTME;
	csTME.cbSize = sizeof(csTME);
	csTME.dwFlags = TME_HOVER|TME_LEAVE;
	csTME.hwndTrack = this->m_hWnd;
	csTME.dwHoverTime = 10;
	::_TrackMouseEvent(&csTME);
}

void CColorPen::OnPaint()
{
	CWnd::OnPaint();
}



void CColorPen::SetColor(COLORREF c1,COLORREF c2,COLORREF c3)
{
	m_OutSide = c1;
	m_MiddleSide = c2;
	m_InSide = c3;
}
