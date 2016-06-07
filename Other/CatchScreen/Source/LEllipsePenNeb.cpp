/**
*   LEllipsePenneb.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ���ϲ�����45����Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14   	 ʵ�� CLEllipsePenNeb ��
*/
#include "stdafx.h"
#include "..\Include\LEllipsePenNeb.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLEllipsePenNeb::CLEllipsePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha) 
		: CPenNeb(hDC, crColor, bAlpha)
{
	if (bAlpha)
	{
		// ����AlphaЧ����ת����ľ��ο�Ϊһ������
		m_PenNebSize.cx = nSize;
		m_PenNebSize.cy = nSize;
	}
	else
	{
		// ������ͨЧ����Ϊ�������
		m_PenNebSize.cx = nSize / 2;
		m_PenNebSize.cy = nSize;
	}
}

CLEllipsePenNeb::~CLEllipsePenNeb()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: NormalApply
*  ����		: ��ָ������ĵ�������ͨ��Ч��ͼ
*  ����		: CPoint& ptPoint	-	��ͼ�ĵ�
*  �㷨		: ֱ�ӻ���Բ
*--------------------------------------------------------------------------------
*/
void CLEllipsePenNeb::NormalApply(const CPoint& ptPoint) const
{
	HBRUSH hBrush = CreateSolidBrush(m_crPenNeb);
	HBRUSH hOldBrush = (HBRUSH) SelectObject(m_hDC, hBrush);
	HPEN hOldPen = (HPEN) SelectObject(m_hDC, GetStockObject(NULL_PEN));

	DrawRotateEllipse(m_hDC, 
		CRect(ptPoint.x - m_PenNebSize.cx / 2,
		ptPoint.y - m_PenNebSize.cy / 2, 
		ptPoint.x + m_PenNebSize.cx / 2, 
		ptPoint.y + m_PenNebSize.cy / 2),
		45);
	
	SelectObject(m_hDC, hOldPen);
	SelectObject(m_hDC, hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hOldBrush);
	DeleteObject(hBrush);
}


/*
*--------------------------------------------------------------------------------
*  ������: SetAlpha
*  ����	 : ���ñʼ�ͼ����ÿ�����ص��Alphaֵ
*  ����  : BYTE* pPixel - �ʼ�DIBͼ�������ָ��
*  �㷨  : ������Բ�ʼ⣬��͸�����м�Ϊ���150�������ܹ��ɵ���ȫ͸��
*  ˵��  : ���� Alpha ���ÿ�����ص����Ϊ 32 λ
*--------------------------------------------------------------------------------
*/
void CLEllipsePenNeb::SetAlpha(BYTE *pPixel)
{
	int nWidth = m_PenNebSize.cx;
	int nHeight = m_PenNebSize.cy;
	
	for (int y = 0; y < nHeight; y++)
		for (int x = 0; x < nWidth; x++, pPixel += 4)
		{
			BYTE alpha = 255;
			int dis;

			// ��ת��ĵ�
			CPoint pt(x, y);
			RotatePoint(45, CPoint(m_PenNebSize.cx / 2, m_PenNebSize.cy / 2), pt);
			pt.x -= nWidth / 4;
			dis = (int) ( sqrt( (float)(pt.x*2-nWidth/2) * (pt.x*2-nWidth/2)
				+ (pt.y-nHeight/2) * (pt.y-nHeight/2)) 
				* 150 / (max(nWidth, nHeight)/2) );
			
			alpha = (BYTE) max(min(150 - dis, 150), 0);


			pPixel[0] = pPixel[0] * alpha / 255;
			pPixel[1] = pPixel[1] * alpha / 255;
			pPixel[2] = pPixel[2] * alpha / 255;
			pPixel[3] = alpha;
		}
}


/*
*--------------------------------------------------------------------------------
*  ������	: SetSize
*  ����		: ���ñʼ�Ĵ�С
*  ����		: int nSize	-	�ʼ��С
*  �㷨		: ����45����Բ�ʼ�Ŀ����߶����
*--------------------------------------------------------------------------------
*/
void CLEllipsePenNeb::SetSize(int nSize)
{
	if (m_bAlpha)
	{
		// ����AlphaЧ����ת����ľ��ο�Ϊһ������
		m_PenNebSize.cx = nSize;
		m_PenNebSize.cy = nSize;
		CreateAlphaPen();
	}
	else
	{
		// ������ͨЧ����Ϊ�������
		m_PenNebSize.cx = nSize / 2;
		m_PenNebSize.cy = nSize;
	}
}


/*
*--------------------------------------------------------------------------------
*  ������	: CreatePenNeb
*  ����		: ������ʱ�ڱʵ�λͼ�ϻ����ʼ���״
*  �㷨		: ֱ�ӻ���Բ
*--------------------------------------------------------------------------------
*/
void CLEllipsePenNeb::CreatePenNeb()
{
	// �����ǻ���Բ����Ϊ�������
	CRect rect(m_PenNebSize.cx / 4, 0, 3 * m_PenNebSize.cx / 4, m_PenNebSize.cy);
	CPoint ellipsePts[13];
	EllipseToBezier(rect, ellipsePts);

	// Rotate
	RotateEllipse(45, CPoint(m_PenNebSize.cx / 2, m_PenNebSize.cy / 2) , ellipsePts, 13);
	
	BeginPath(m_hMemDC);		
	PolyBezier(m_hMemDC, ellipsePts, 13);
	EndPath(m_hMemDC);
	FillPath(m_hMemDC);
}