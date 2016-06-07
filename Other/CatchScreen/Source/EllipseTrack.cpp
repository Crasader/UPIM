/**
*   EllipseTrack.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ�ָ�����Բ�켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/11   	 ʵ�� CEllipseTrack ��
*/
#include "stdafx.h"
#include "..\Include\EllipseTrack.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ROUND(a)	((int) (a + 0.5))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEllipseTrack::CEllipseTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("��Բ��");
}

CEllipseTrack::~CEllipseTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: ������Բ�켣
*  ����		:
*		CPoint& ptStart	-	��Բ��Χ�������Ͻ�����
*		CPoint& ptEnd	-	��Բ��Χ�������½�����
*--------------------------------------------------------------------------------
*/
void CEllipseTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;

	if (ptStart.y == ptEnd.y || ptStart.x == ptEnd.x)
	{
		// ˮƽ�߻��Ǵ�ֱ��
		MoveToEx(hDC, ptStart.x, ptEnd.y, NULL);
		LineTo(hDC, ptEnd.x, ptEnd.y);
	}
	else
	{
		Ellipse(hDC, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
}


/*
*--------------------------------------------------------------------------------
*  ������: CreatePos
*  ����	 : �������Բ�켣�����е�ļ��ϣ����浽�б���ȥ
*  �㷨  : ������Բ��������Բ�ϵ�ÿһ����
*  ǰ������: �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  ��������: �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CEllipseTrack::CreatePos()
{
	if (m_ptTrackStartPoint.y == m_ptTrackEndPoint.y && m_ptTrackStartPoint.x == m_ptTrackEndPoint.x)
	{
		// ˮƽ�߻��Ǵ�ֱ��
		LineDDA(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y, m_ptTrackEndPoint.x, m_ptTrackEndPoint.y, CTrack::AddPosToList, (LPARAM) this);
	}
	else
	{
		int xCenter, yCenter;
		double a, b;
		
		xCenter = (m_ptTrackEndPoint.x + m_ptTrackStartPoint.x) / 2;
		yCenter = (m_ptTrackEndPoint.y + m_ptTrackStartPoint.y) / 2;
		
		// ��Բ X �᳤��
		a = abs(m_ptTrackEndPoint.x - m_ptTrackStartPoint.x) / 2;
		// ��Բ Y �᳤��
		b = abs(m_ptTrackEndPoint.y - m_ptTrackStartPoint.y) / 2;
				
		double b2 = b * b;
		double a2 = a * a;
	
		// ���ĵ�Ϊ(xCenter, yCenter)��ɨ�� X ���� Y ֵ
		int x, y;		
		for (x = (int) -a; x <= (int) a; x++)
		{
			y = (int) sqrt(b2 - (b2 / a2) * (x * x));
			AddPoint(x + xCenter, y + yCenter);
		}
		// ��Գ��ᣬ��������Ϊ���������������
		for (x = (int) -a; x <= (int) a; x++)
		{
			y = (int) sqrt(b2 - (b2 / a2) * (x * x));
			AddPoint(x + xCenter, yCenter - y);
		}


		// ���ĵ�Ϊ(xCenter, yCenter)��ɨ�� Y ���� X ֵ
		for (y = (int) b; y >= (int) -b; y--)
		{
			x = (int) sqrt(a2 - (a2 / b2) * (y * y));
			if ( y != (int) sqrt(b2 - (b2 / a2) * (x * x)) )
			{
				AddPoint(xCenter - x, yCenter + y);
			}
		}
		// ��Գ��ᣬ��������Ϊ���������������
		for (y = (int) -b; y <= (int) b; y++)
		{
			x = (int) sqrt(a2 - (a2 / b2) * (y * y));
			if ( y != (int) sqrt(b2 - (b2 / a2) * (x * x)) )
			{
				AddPoint(x + xCenter, y + yCenter);
			}
		}
	}

	return TRUE;
}


void CEllipseTrack::CalEllipsePath(int xCenter, int yCenter, int Rx, int Ry)
{
//	int Rx, Ry, xCenter, yCenter;
	int Rx2, Ry2, twoRx2, twoRy2;


	Rx = abs(m_ptTrackEndPoint.x - xCenter);
	Ry = abs(m_ptTrackEndPoint.y - yCenter);

	Rx2 = Rx * Rx;
	Ry2 = Ry * Ry;
	twoRx2 = 2 * Rx2;
	twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;

	void ellipseGetPoints(int, int, int, int);

	AddPoint(x, y);;

	p = ROUND(Ry2 - (Rx2 + Ry) + (0.25 * Rx2));
	while (px < py)
	{
		x++;
		px += twoRy2;
		if(p<0)
			p += Ry2 + px;
		else
		{
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		AddPoint(x, y);;
	}

	p = ROUND(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y -1)
		      - Rx2 * Ry2);
	while (y > 0)
	{
		y--;
		py -= twoRx2;
		if (p > 0)
			p += Rx2 - py;
		else
		{
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		AddPoint(x, y);
	}
}

void ellipseGetPoints(int xCenter, int yCenter, int x, int y)
{
	static CList<CPoint, CPoint> MyPoint;
	MyPoint.AddTail(CPoint(xCenter + x, yCenter + y));
	MyPoint.AddTail(CPoint(xCenter - x, yCenter + y));
	MyPoint.AddTail(CPoint(xCenter - x, yCenter - y));
	MyPoint.AddTail(CPoint(xCenter + x, yCenter - y));
}
