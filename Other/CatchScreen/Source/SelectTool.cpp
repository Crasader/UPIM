/**
*   SelectTool.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����ѡȡ���ߵĳ������
*======================================================
*   �汾
*   Revision 1.0	2002/11/14    	  ʵ��ѡȡ���ߵĳ������
*/
#include "stdafx.h"
#include "..\INCLUDE\SelectTool.h"
#include "..\INCLUDE\FloatDibWnd.h"
#include "..\Include\DefineMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSelectTool::CSelectTool(HWND hWnd)
{
	// ��ѡȡ�ͻ������ھ��
	m_hWnd = hWnd;
	m_hDC = GetDC(hWnd);
}

CSelectTool::~CSelectTool()
{
}


/*
*--------------------------------------------------------------------------------
*  ������: BeginSelect
*  ����	 : ��ʼ��������ѡȡ
*  ����  : CPoint ptPoint  - ѡȡ�������ʼ������
*  ˵��  : ѡȡʱ�Ȼ����߿�
*--------------------------------------------------------------------------------
*/
void CSelectTool::BeginSelect(const CPoint& ptPoint)
{
	m_ptSelectStartPoint = ptPoint;
	m_ptSelectEndPoint = ptPoint;

	// ������ʼ��ѡȡ��
	DrawRubber(m_ptSelectEndPoint);
}


/*
*--------------------------------------------------------------------------------
*  ������: ChangeSelect
*  ����	 : �ƶ����ı�ѡȡ����ķ�Χ
*  ����  : CPoint ptPoint  - ѡȡ�������ʱ����������
*  ˵��  : �ڴ˺������������һ��ѡȡʱ���������
*--------------------------------------------------------------------------------
*/
void CSelectTool::ChangeSelect(const CPoint& ptPoint)
{
	CPoint pt = ptPoint;

	// ����ѡ��Χֻ�ڻ�������
	CRect rcParent;
	GetClientRect(m_hWnd, &rcParent);

	if (pt.x <= 0)
		pt.x =0;
	if (pt.x >= rcParent.Width())
		pt.x = rcParent.Width();
	if (pt.y <= 0)
		pt.y =0;
	if (pt.y >= rcParent.Height())
		pt.y = rcParent.Height();

	// ����ǰһ�λ�����ѡȡ��
	DrawRubber(m_ptSelectEndPoint);

	// �����˴ε�ѡȡ��
	DrawRubber(pt);

	m_ptSelectEndPoint = pt;
}


/*
*--------------------------------------------------------------------------------
*  ������: EndSelect
*  ����	 : ��������ѡȡ
*  ����  : CPoint ptPoint  - ѡȡ����Ľ���������
*  ����ֵ: CFloatDibWnd	 -  ѡȡ���򸡶�����ָ�룬�ɵ��ú��������ͷŴ˴���
*--------------------------------------------------------------------------------
*/
CFloatDibWnd * CSelectTool::EndSelect(const CPoint& ptPoint)
{
	// ����ǰһ�λ�����ѡȡ��
	DrawRubber(m_ptSelectEndPoint);

	// ˢ�»������Է����δ�����Ͱѻ���ץ������
	::SendMessage(m_hWnd, WM_PAINT, 0, 0);

	CFloatDibWnd * pFloatWnd = NULL;

	if (m_ptSelectStartPoint != m_ptSelectEndPoint)
	{
		// �յ㲻�������
		CRect rect(m_ptSelectStartPoint, m_ptSelectEndPoint);

		pFloatWnd = new CFloatDibWnd(m_hWnd, rect);
		pFloatWnd->CreateWnd();

		CRect* rc = new CRect(rect);
		// ������Ϣ�������������Լ��������
		::SendMessage(m_hWnd, WM_CUTCAVASDIBRECT, WPARAM(rc), 0);
		delete rc;

		//δѡ����䰵
//		::SendMessage(m_hWnd, WM_DARKUNSELECTEDRECT, 0, 0);
	}

	return pFloatWnd;
}


/*
*--------------------------------------------------------------------------------
*  ������: DrawRubber
*  ����	 : ����ѡȡ������������Ϊ��ʾ
*  ����  : CPoint ptPoint  - ѡȡ����Ľ���������
*  ����ֵ: CFloatDibWnd	 -  ѡȡ���򸡶�����ָ�룬�ɵ��ú��������ͷŴ˴���
*--------------------------------------------------------------------------------
*/
void CSelectTool::DrawRubber(const CPoint& ptPoint) const
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(0x0, 0x0, 0x0));
	HPEN hOldPen = (HPEN) SelectObject(m_hDC, hPen);

	int nOldRop = SetROP2(m_hDC, R2_NOTXORPEN);

	// �����켣
	DrawTrack(m_ptSelectStartPoint, ptPoint);



	SetROP2(m_hDC, nOldRop);

	SelectObject(m_hDC, hOldPen);
	SelectObject(m_hDC, hOldBrush);	
	DeleteObject(hOldPen);
	DeleteObject(hPen);
	DeleteObject(hOldBrush);
}


/*
*--------------------------------------------------------------------------------
*  ������: DrawUnselectedRgn
*  ����	 : ʹδѡȡ����䰵
*  �㷨  :
*--------------------------------------------------------------------------------
*/
void CSelectTool::DarkUnselectedRgn()
{
	
 	CRect rect;
 	GetWindowRect(m_hWnd, &rect);
 
 	HDC hDarkMemDC = CreateCompatibleDC(m_hDC);
 	HBITMAP hDarkBitmap = CreateCompatibleBitmap(m_hDC, rect.Width(), rect.Height());
 	HBITMAP hOldBitmap = (HBITMAP) SelectObject(hDarkMemDC, hDarkBitmap);
 	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDarkMemDC, GetStockObject(NULL_BRUSH));
 	
 	Rectangle(hDarkMemDC, 0, 0, rect.Width(), rect.Height());
 

	BLENDFUNCTION blend = { AC_SRC_OVER, 0, 100, 0 };
 
 	AlphaBlend( m_hDC, 
 				0, 
 				0, 
 				rect.Width(),
 				rect.Height(),
 				hDarkMemDC, 
 				0, 
 				0, 
 				100, 
 				100,
 				blend);
 
 	DeleteObject(hOldBrush);
 	DeleteObject(hOldBitmap);
 	DeleteObject(hDarkBitmap);
 	DeleteObject(hDarkMemDC);
}
