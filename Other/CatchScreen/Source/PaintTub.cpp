/**
*   PaintTub.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ������Ͱ��
*======================================================
*   �汾
*	Revision 1.0	2002/11/12    	 ʵ�� CPaintTub ��
*/

#include "stdafx.h"
#include "..\\include\\PaintTub.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPaintTub::CPaintTub(HDC hDC, int nSize, COLORREF crColor) : CAbstractPen(hDC, nSize, crColor)
{
	m_strPenName = _T("����Ͱ");
//	m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_PAINTTUB));
    m_hCursor = AfxGetApp()->LoadCursor(IDC_PAINTTUB);
}


CPaintTub::~CPaintTub()
{

}


/*
*--------------------------------------------------------------------------------
*  ������:	BeginDraw
*  ����	 :	�õ�ǰ��ˢ��ɫ���������
*  ����	 :	CPoint ptPoint	 -   ��ǰ�������
*  �㷨  :	���غ��������� API �����������
*--------------------------------------------------------------------------------
*/
void CPaintTub::BeginDraw(const CPoint& ptPoint)
{
	HDC hDC = m_hDC;

	// �õ���ǰ��������ɫ
	COLORREF crCurPos = GetPixel(hDC, ptPoint.x, ptPoint.y);

	HBRUSH hBrush = CreateSolidBrush(m_crPenColor);
	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDC, hBrush);

	// �����ɫ, Windows API
	ExtFloodFill(hDC, ptPoint.x, ptPoint.y, crCurPos, FLOODFILLSURFACE);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
	DeleteObject(hBrush);
}


/*
*--------------------------------------------------------------------------------
*  ������:	DrawPoint
*  ����	 :	ʲô���鶼����
*  ����	 :	CPoint ptPoint	 -   ��ǰ�������
*  �㷨  :	���غ�������Ϊ���ڰ������ʱ������䣬������ƶ�ʱʲô�²���
*--------------------------------------------------------------------------------
*/
void CPaintTub::DrawPoint(const CPoint& ptPoint)
{	
}


/*
*--------------------------------------------------------------------------------
*  ������:	EndDraw
*  ����	 :	ʲô���鶼����
*  ����	 :	CPoint ptPoint	 -   ��ǰ�������
*  �㷨  :	���غ�������Ϊ���ڰ������ʱ������䣬���ɿ����ʱʲô�²���
*--------------------------------------------------------------------------------
*/
void CPaintTub::EndDraw(const CPoint& ptPoint)
{	
}
