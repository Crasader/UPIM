/**
*   Track.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002. All Rights Reserved.
*   �켣���ʵ���ļ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/11   	 ���� CTrack ���ʵ��
*/


#include "stdafx.h"
#include "..\Include\Track.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  ����
*	HDC hDC	 - �켣�滭�Ĵ����豸������
*--------------------------------------------------------------------------------
*/
CTrack::CTrack(HDC hDC, COLORREF crTrackColor)
{
	m_hDC = hDC;
	m_crTrackColor = crTrackColor;
}


CTrack::~CTrack()
{
	m_listTrackPoints.RemoveAll();
}

	
/*
*--------------------------------------------------------------------------------
*  ������: BeginTrack
*  ����	 : ��ʼ��¼�켣
*  ����  : CPoint& ptPoint	 -  �켣����ʼ�����
*  ��������: ���켣�����յ����Ϊ��ǰ����㣬������һ����
*--------------------------------------------------------------------------------
*/
void CTrack::BeginTrack(const CPoint& ptPoint)
{
	m_ptTrackStartPoint.x = ptPoint.x;
	m_ptTrackStartPoint.y = ptPoint.y;
	m_ptTrackEndPoint.x = ptPoint.x;
	m_ptTrackEndPoint.y = ptPoint.y;

	// �����µĹ켣
	PreDraw(ptPoint, ptPoint);
}


/*
*--------------------------------------------------------------------------------
*  ������: DrawTrack
*  ����	 : ����켣��״
*  ����  : CPoint ptPoint - ��ǰ�������
*  �㷨  : ������DC���ٵ��û�ͼ����PreDraw
*  ǰ������:	�����ȵ��� BeginDraw
*--------------------------------------------------------------------------------
*/
void CTrack::DrawTrack(const CPoint &ptPoint)
{
	// ������һ�λ��Ĺ켣
	PreDraw(m_ptTrackStartPoint, m_ptTrackEndPoint);
	
	// �����µĹ켣
	PreDraw(m_ptTrackStartPoint, ptPoint);
	
	// ���������
	m_ptTrackEndPoint = ptPoint;	
}


/*
*--------------------------------------------------------------------------------
*  ������: EndTrack
*  ����	 : ������¼�켣
*  ����  : CPoint& ptPoint	 - ��ǰ�������
*  ��������: ���浱ǰ����Ϊ�켣��ֹ�㣬ͬʱ�����켣��ļ���
*--------------------------------------------------------------------------------
*/
void CTrack::EndTrack(const CPoint& ptPoint)
{
	// ����ǰ�λ����Ĺ켣
	PreDraw(m_ptTrackStartPoint, ptPoint);

	m_ptTrackEndPoint = ptPoint;

 	//����켣��
 	PreCreatePos();
}


/*
*--------------------------------------------------------------------------------
*  ������: PreDraw
*  ����	 : ����켣��״
*  ����  : CPoint ptPoint	 - ��ǰ�������
*  �㷨  : ��һЩ������������жϣ�����ͳһ�����ٵ���������Ļ�켣���� Draw
*			���� Template Method ģʽ
*  ǰ������:	�����ȵ��� BeginDraw
*--------------------------------------------------------------------------------
*/
void CTrack::PreDraw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;
	CBrush brush(m_crTrackColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
	HPEN hPen = CreatePen(PS_SOLID, 1, m_crTrackColor);
	HPEN hOldPen = (HPEN) SelectObject(m_hDC, hPen);

	int nOldRop = SetROP2(m_hDC, R2_NOTXORPEN);

	// ����������Ļ��켣����
	Draw(ptStart, ptEnd);


	SetROP2(m_hDC, nOldRop);
	
	SelectObject(m_hDC, hOldPen);
	SelectObject(m_hDC, hOldBrush);	
	DeleteObject(hPen);
	DeleteObject(hOldPen);
	DeleteObject(hOldBrush);
}


/*
*--------------------------------------------------------------------------------
*  ������: PreCreatePos
*  ����	 : ��һ����������µĹ켣�㼯����������
*  �㷨  : ͨ�� LineDDA �����ó����еĹ켣������
*  ǰ������: �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  ��������: �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CTrack::PreCreatePos()
{
	m_listTrackPoints.RemoveAll();

	if (m_ptTrackStartPoint.x == m_ptTrackEndPoint.x && m_ptTrackStartPoint.y == m_ptTrackEndPoint.y)
	{
		// �����յ���ͬ���켣��һ����
		AddPoint(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y);
	}
	else
	{
		// �����Ĺ켣��״
		CreatePos();
	}

	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ������: GetIntersectPoint
*  ����	 : ������ֱ�ߵĽ�������
*  ����  :
*	[in]	CPoint &pt1Begin	- ֱ��һ����ʼ������
*	[in]	CPoint &pt1End		- ֱ��һ���յ�����
*	[in]	CPoint &pt2Begin	- ֱ�߶�����ʼ������
*	[in]	CPoint &pt2End		- ֱ�߶����յ�����
*	[out]	CPoint & ptIntersect	-	��������
*  �㷨:	ֱ�߷���	y = k * x + b
*		���㴦(x0, y0)
*					y0 = k1 * x + b1
*					y0 = k2 * x + b2
*		�����ֱ�ߵķ��̳��������ϵ�ʽ����
*--------------------------------------------------------------------------------
*/
void CTrack::GetIntersectPoint(const CPoint &pt1Begin, const CPoint &pt1End, const CPoint &pt2Begin, const CPoint &pt2End, CPoint& ptIntersect) const
{
	double k1, b1, k2, b2;
	
	BOOL bVer1, bVer2;
	bVer1 = CalLineEquation(pt1Begin, pt1End, &k1, &b1);
	bVer2 = CalLineEquation(pt2Begin, pt2End, &k2, &b2);

	double x, y;

	// ����������һ����ֱ��
	if (!bVer1 || !bVer2)	
	{
		if (!bVer1)
		{
			// ��һ��ֱ���Ǵ�ֱ��
			x = pt1Begin.x;
			y =  k2 * (double) x + b2;
		}
		else
		{
			// �ڶ������Ǵ�ֱ��
			x = pt2Begin.x;
			y = k1 * (double) x + b1;
		}
	}
	else
	{
		x = (b2 - b1) / (k1 - k2);
		y = k1 * (double) x + b1;
	}
	
	ptIntersect.x = (int) x;
	ptIntersect.y = (int) y;
}


/*
*--------------------------------------------------------------------------------
*  ������: CalLineEquation
*  ����	 : ��ֱ�ߵķ���ʽ y = k * x + b  �е� k �� b
*  ����  :
*	[in]	CPoint &pt1Begin	- ֱ��һ����ʼ������
*	[in]	CPoint &pt1End		- ֱ��һ���յ�����
*	[out]	double * k			- k ֵ
*	[out]	double * b			- b ֵ
*  ����ֵ:  BOOL	-	���ֱ���Ǵ�ֱ���򷵻� FALSE�� ���򷵻� TRUE
*  �㷨  :	k = (y2 - y1) / (x2 - x1)
*			b = y1 - k * x1
*--------------------------------------------------------------------------------
*/
BOOL CTrack::CalLineEquation(const CPoint &ptBegin, const CPoint &ptEnd, double * k, double * b) const
{
	if (ptBegin.x == ptEnd.x)
	{
		// ��ֱ��
		return FALSE;
	}
	else if (ptBegin.y == ptEnd.y)
	{
		//ˮƽ��
		*k = 0;
	}
	else
	{
		// б��
		*k = (double) ((ptBegin.y - ptEnd.y)) / (double) ((ptBegin.x - ptEnd.x));
	}
	*b = ptBegin.y - (*k) * (double) ptBegin.x;

	return TRUE;
}



/*
*--------------------------------------------------------------------------------
*  ������: SplitCircle
*  ����	 : ��Բ�ȷֳ�ָ�����������ÿ���������
*  ����  :
*	[in]  CPoint ptCenter		- Բ������
*	[in]  CPoint ptBegin		- ָ��һ����ʼ��������
*	[in]  int nCount			- �ȷַ���
*	[out] CPoint *ptVertex	- ���ض�����������
*  �㷨  : ��Բ�ֳܷ� nCount �������ɻ�������ɨ��Ƕȼ�����յ㼴��������
*--------------------------------------------------------------------------------
*/
BOOL CTrack::SplitCircle(const CPoint &ptCenter, const CPoint &ptBegin, int nCount, CPoint *ptVertex) const
{
	ASSERT(nCount > 2);

	// �Ƕ�ת���ȳ���
	const FLOAT piover180 = (FLOAT) 3.141592653586 / 180;

	CPoint point[4];
	point[0] = ptBegin;
	point[3] = ptBegin;

	int cx, cy, r;
	double a;

	cx = abs(ptBegin.x - ptCenter.x);
	cy = abs(ptBegin.y - ptCenter.y);
	
	// Բ�İ뾶��Ϊ��֤���ȣ�����ļ��㹫ʽ��ֱ���õ��ǹ�ʽ
	r = int(sqrt((float)cx * cx + (float)cy * cy));

	if (!r)
		return FALSE;

	// ���������ʼ�Ƕ� a
	if (ptBegin.x > ptCenter.x && ptBegin.y < ptCenter.y)
	{	
		// ��һ����
		a = acos(double(cx) / double(sqrt((float)cx * cx + (float)cy * cy))) / piover180;
	}
	else if (ptBegin.x < ptCenter.x && ptBegin.y < ptCenter.y)
	{
		// �ڶ�����
		a = asin(double(cx) / double(sqrt((float)cx * cx + (float)cy * cy))) / piover180;
		a = 90 + a;
	}
	else if (ptBegin.x < ptCenter.x && ptBegin.y > ptCenter.y)
	{
		// ��������
		a = acos(double(cx) / double(sqrt((float)cx * cx + (float)cy * cy))) / piover180;
		a = 180 + a;
	}
	else if (ptBegin.x > ptCenter.x && ptBegin.y > ptCenter.y)
	{
		// ��������
		a = asin(double(cx) / double(sqrt((float)cx * cx + (float)cy * cy))) / piover180;
		a = 270 + a;
	}
	else if (ptBegin.x == ptCenter.x && ptBegin.y < ptCenter.y)
	{
		// λ����Y��
		a = 90;
	}
	else if (ptBegin.x == ptCenter.x && ptBegin.y > ptCenter.y)
	{
		// λ�� -Y ��
		a = 270;
	}
	else if (ptBegin.y == ptCenter.y && ptBegin.x > ptCenter.x)
	{
		// λ����X��
		a = 0;
	}
	else if (ptBegin.y == ptCenter.y && ptBegin.x < ptCenter.x)
	{
		// λ�ڸ�X��
		a = 180;
	}


	// ÿ�λ�����ת�Ƕ�
	double fltArcAngle = 360.0 / (float) nCount;

	// ���������������
	for (int i = 0; i < nCount; i++)
	{
		ptVertex[i] = GetArcEndPoint(ptCenter, sqrt((float)cx * cx + (float)cy * cy), a, fltArcAngle * i);
	}
	
	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ������: GetArcEndPoint
*  ����  :����һ�λ����յ�����
*  ����  :
*	[in]  CPoint ptCenter		- ������Բ��Բ������
*	[in]  DWORD dwRadius		- ������Բ�İ뾶
*	[in]  FLOAT eStartAngle		- ������ʼ�Ƕ�
*	[in]  FLOAT eSweepAngle		- ����ɨ��Ƕ�
*  ����ֵ :	 CPoint	 -	�����յ�����
*  �㷨
*		
*--------------------------------------------------------------------------------
*/
CPoint CTrack::GetArcEndPoint(const CPoint &ptCenter, double dwRadius, double eStartAngle, double eSweepAngle) const
{
	// �Ƕ�ת���ȳ���
	const FLOAT piover180 = (FLOAT) 3.141592653586 / 180;

	// ȷ�����ֻ��һ��Բ
	if (eSweepAngle >= 360)
		eSweepAngle = 360;
	else if (eSweepAngle <= -360)
		eSweepAngle = -360;

	// ������ʼ�ǡ���ֹ�ǶȵĻ���
	double eEndAngle = (eStartAngle + eSweepAngle) * piover180;

	// ���������ʼ����ֹ�������
	int nXEnd, nYEnd;

	nXEnd = ptCenter.x + (int) (dwRadius * cos(eEndAngle));
	nYEnd = ptCenter.y - (int) (dwRadius * sin(eEndAngle));

	return CPoint(nXEnd, nYEnd);
}

/*
*--------------------------------------------------------------------------------
*  ������: AddPosToList
*  ����	 : ���켣���б��м���һ����
*  ����  :
*	[in]  int x				- ��� X ����
*	[in]  int y				- ��� Y ����
*	[in]  LPARAM lpData		- �켣�����ָ��
*  �㷨  : �ص����������ڼ������������е�� LineDDA �������á�
*--------------------------------------------------------------------------------
*/
void CALLBACK CTrack::AddPosToList(int x, int y, LPARAM lpData)
{
	CTrack * pTrack = (CTrack*) lpData;
	
	pTrack->AddPoint(x, y);
}


/*
*--------------------------------------------------------------------------------
*  ������: AddPoint
*  ����	 : ���켣���б��м���һ����
*  ����  :
*	[in]  int x				- ��� X ����
*	[in]  int y				- ��� Y ����
*  �㷨  : �������ڼ���㵽�켣������
*--------------------------------------------------------------------------------
*/
void CTrack::AddPoint(int x, int y)
{
	// ���ж��Ƿ񳬳���Χ
	if (x < 0 || y < 0)
		return;

	m_listTrackPoints.AddTail(CPoint(x, y));
}


/*
*--------------------------------------------------------------------------------
*  ������: GetHeadPosition
*  ����	 : �õ���һ�����ڹ켣���б��е�λ��
*  ����ֵ: POSITION	 -	�켣��һ�������б��е�λ�ã�����ȡ��һ����
*--------------------------------------------------------------------------------
*/
POSITION CTrack::GetHeadPosition()
{
	return m_listTrackPoints.GetHeadPosition();
}


/*
*--------------------------------------------------------------------------------
*  ������: GetNextPoint
*  ����	 : �õ���һ���켣�ϵĵ�
*  ����  : [in, out]  POSITION& rPos	-  ����ȡ�����б��е�λ��
*  ����ֵ: CPoint&	 -	�켣�ϵ������
*  ��������:	rPos = rPos + 1
*		����ѵ��б�β���� rPos = NULL
*--------------------------------------------------------------------------------
*/
CPoint& CTrack::GetNextPoint(POSITION& rPos)
{
	return m_listTrackPoints.GetNext(rPos);	
}


/*
*--------------------------------------------------------------------------------
*  ������	: SetTrackColor
*  ����		: ���ù켣����ɫ
*  ����		: [in]  COLORREF crTrackColor - �켣��ɫ
*  �������� : ���ù켣��ɫ
*--------------------------------------------------------------------------------
*/
void CTrack::SetTrackColor(COLORREF crTrackColor)
{
	m_crTrackColor = crTrackColor;
}
