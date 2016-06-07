/**
*   AbstractPen.cpp		
*   Version 2.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ�ֱʵĳ�����
*======================================================
*   �汾
*   Revision 1.0	2002/11/1     	 ʵ�� CAbstractPen ��
*	
*	Revision 2.0	2002/11/12    	 �����ʼ���켣����
*/


#include "stdafx.h"
#include <math.h>

#include "..\Include\PenNeb.h"
#include "..\Include\CirclePenNeb.h"
#include "..\Include\HEllipsePenNeb.h"
#include "..\Include\VEllipsePenNeb.h"
#include "..\Include\REllipsePenNeb.h"
#include "..\Include\LEllipsePenNeb.h"

#include "..\Include\AbstractPen.h"
#include "..\Include\Track.h"
#include "..\Include\RandomTrack.h"
#include "..\Include\LineTrack.h"
//#include "PentagonTrack.h"
#include "..\Include\RectangleTrack.h"
//#include "TriangleTrack.h"
//#include "TetragonTrack.h"
#include "..\Include\EllipseTrack.h"
//#include "FiveSideTrack.h"
//#include "PolygonTrack.h"
#include "..\Include\ArrowTrack.h"

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
*  ����: ���ñ����Ե�ȱʡֵ
*  ����: HDC hDC  -	�ñʻ滭���豸��������
*		 int nSize - �ʵĴ�С
*		 COLORREF crColor - �ʵ���ɫ
*  ȱʡֵ:	�ʿ�		-   12
*			�ʼ���״	-	Բ��
*			�ʵĹ켣	-	����켣
*			�ʵ���ɫ	-	��ɫ
*--------------------------------------------------------------------------------
*/
CAbstractPen::CAbstractPen(HDC hDC, int nSize, COLORREF crColor)
	: m_hDC(hDC), m_nPenSize(nSize), m_crPenColor(crColor)
{
	m_pPenNeb = NULL;
	m_bAlpha = FALSE;
	// ���ȳ�ʼ�� m_bAlpha
	SetPenStyle(PS_CIRCLE);

	m_pPenTrack = NULL;
	SetPenTrack(PT_RANDOM);
}


CAbstractPen::~CAbstractPen()
{
	if (m_pPenTrack)
		delete m_pPenTrack;
	m_pPenTrack = NULL;

	if (m_pPenNeb)
		delete m_pPenNeb;
	m_pPenNeb = NULL;
}


/*
*--------------------------------------------------------------------------------
*  ������: BeginDraw
*  ����	 : ��ʼ����滭״̬
*  ����  : CPoint ptPoint  - ��ǰ�������
*  ��������:	ί�и��켣���������Ӧ����
*--------------------------------------------------------------------------------
*/
void CAbstractPen::BeginDraw(const CPoint& ptPoint)
{	
	ASSERT(m_pPenTrack);

	if (m_PenTrack == PT_RANDOM)
	{
		//����켣��ÿ������ƶ�ʱ������һ�ι켣����ʼ�µ�һ�ι켣
		m_pPenTrack->BeginTrack(ptPoint);
		Apply(ptPoint);
	}
	else
	{
		// ������״�켣
		m_pPenTrack->BeginTrack(ptPoint);
	}
}


/*
*--------------------------------------------------------------------------------
*  ������: DrawPoint
*  ����	 : ���
*  ����  : CPoint ptPoint - ��ǰ�������
*  �㷨  : ί�и��켣������л��㴦��
*  ǰ������: �����ȵ��� BeginDraw
*--------------------------------------------------------------------------------
*/
void CAbstractPen::DrawPoint(const CPoint& ptPoint)
{
	ASSERT(m_pPenTrack);

	if (m_PenTrack == PT_RANDOM)
	{		
		// ����켣����ÿ������ƶ�ʱ����һ�ι켣

		//������һ�εĹ켣
		m_pPenTrack->EndTrack(ptPoint);
		FillTrack();

		//��ʼ��һ�ι켣
		m_pPenTrack->BeginTrack(ptPoint);
	}
	else
	{
		m_pPenTrack->DrawTrack(ptPoint);
	}
}


/*
*--------------------------------------------------------------------------------
*  ������: EndDraw
*  ����	 : �����滭
*  ����  : CPoint ptPoint  - ��ǰ�������
*  �㷨  : ί�и��켣������д���
*--------------------------------------------------------------------------------
*/
void CAbstractPen::EndDraw(const CPoint& ptPoint)
{
	ASSERT(m_pPenTrack);

	m_pPenTrack->EndTrack(ptPoint);

	//���켣�ϵĵ㼯��
	FillTrack();
}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenColor
*  ����	 : ���ñʵ���ɫ
*  ����  : COLORREF crColor	-  �ʵ���ɫ
*  �㷨	 : ί�и��ʼ�������ñʼ���ɫ��ͬʱ������ɫֵ
*--------------------------------------------------------------------------------
*/
void CAbstractPen::SetPenColor(COLORREF crColor)
{
	ASSERT(m_pPenNeb);

	m_crPenColor = crColor ;
	m_pPenNeb->SetColor(crColor) ;
	m_pPenTrack->SetTrackColor(crColor);
}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenSize
*  ����	 : ���ñʵĴ�С
*  ����  : int  nSize	-	�ʵĴ�С
*  �㷨	 : ί�и��ʼ�������ñʼ��С��ͬʱ����ʴ�Сֵ
*--------------------------------------------------------------------------------
*/
void CAbstractPen::SetPenSize(int nSize)
{
	ASSERT(m_pPenNeb);

	m_nPenSize = nSize;
	m_pPenNeb->SetSize(nSize);
}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenStyle
*  ����	 : ���ñʵĴ�С
*  ����  : PEN_STYLE PenStyle	-	�ʼ���״
*  �㷨	 : ɾ���ɵıʼ�����½��±ʼ����
*--------------------------------------------------------------------------------
*/
void CAbstractPen::SetPenStyle(PEN_STYLE PenStyle)
{
	if (m_pPenNeb)
		delete m_pPenNeb;

	switch (PenStyle)
	{
	case PS_CIRCLE:
		m_pPenNeb = new CCirclePenNeb(m_hDC, m_nPenSize, m_crPenColor, m_bAlpha);
		break;

	case PS_HELLIPSE:
		m_pPenNeb = new CHEllipsePenNeb(m_hDC, m_nPenSize, m_crPenColor, m_bAlpha);
		break;

	case PS_VELLIPSE:
		m_pPenNeb = new CVEllipsePenNeb(m_hDC, m_nPenSize, m_crPenColor, m_bAlpha);
		break;

	case PS_RELLIPSE:
		m_pPenNeb = new CREllipsePenNeb(m_hDC, m_nPenSize, m_crPenColor, m_bAlpha);
		break;

	case PS_LELLIPSE:
		m_pPenNeb = new CLEllipsePenNeb(m_hDC, m_nPenSize, m_crPenColor, m_bAlpha);
		break;

	default:
		ASSERT(0);
	}	
	m_pPenNeb->InitPenNeb();
}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenTrack
*  ����	 : ���ñʵĹ켣
*  ����  : [in]  PEN_TRACK PenTrack	- �ʵĹ켣��״
*  ����ֵ: ����켣���ͺϷ����� TRUE�����򷵻� FALSE
*  �㷨  : ɾ���ɵıʹ켣�����½��µıʹ켣����
*--------------------------------------------------------------------------------
*/
BOOL CAbstractPen::SetPenTrack(PEN_TRACK PenTrack)
{	
	if (m_pPenTrack)
		delete m_pPenTrack;
	m_pPenTrack = NULL;

	m_PenTrack = PenTrack;

	switch (PenTrack)
	{
	case PT_RANDOM:
		// ����켣
		m_pPenTrack = new CRandomTrack(m_hDC, m_crPenColor);
		break;

	case PT_LINE:
		// ֱ��
		m_pPenTrack = new CLineTrack(m_hDC, m_crPenColor);
		break;

	case PT_ELLIPSE:
		// ��Բ
		m_pPenTrack = new CEllipseTrack(m_hDC, m_crPenColor);
		break;
		
// 	case PT_TRIANGLE:
// 		// ������
// 		m_pPenTrack = new CTriangleTrack(m_hDC, m_crPenColor);
// 		break;

	case PT_RECTANGLE:
		// ����
		m_pPenTrack = new CRectangleTrack(m_hDC, m_crPenColor);
		break;

// 	case PT_TETRAGON:
// 		// �Ľ���	
// 		m_pPenTrack = new CTetragonTrack(m_hDC, m_crPenColor);
// 		break;

// 	case PT_PENTAGON:
// 		// �����
// 		m_pPenTrack = new CPentagonTrack(m_hDC, m_crPenColor);
// 		break;

// 	case PT_FIVESIDE:
// 		// �����
// 		m_pPenTrack = new CFiveSideTrack(m_hDC, m_crPenColor);
// 		break;

// 	case PT_POLYGON:
// 		// �����
// 		m_pPenTrack = new CPolygonTrack(m_hDC, m_crPenColor);
// 		break;
	case PT_ARROW:
		m_pPenTrack = new CArrowTrack(m_hDC, m_crPenColor);
		break;

	default:
		;
	}

	return m_pPenTrack ? TRUE : FALSE;
}


/*
*--------------------------------------------------------------------------------
*  ������: GetCursor
*  ����	 : ��ʾ���ֱʵĹ��
*  ����ֵ: ���ش��ֱ�����Ӧ�Ĺ����
*--------------------------------------------------------------------------------
*/
HCURSOR CAbstractPen::GetCursor() const
{	
	return m_hCursor;
}


/*
*--------------------------------------------------------------------------------
*  ������: FillTrack
*  ����	 : �ñ����켣�ϵ�ÿһ����
*  �㷨	 : ɨ��켣�㼯�ϣ���ÿһ�����϶��õ�ǰ�ʻ���
*  ˵��	 : Ϊ�������ٶȣ������Ż������������ڵ�֮�����С��ָ��
*			��Сʱ�����˵㣬ֱ�����ڴ˾���֮�������
*--------------------------------------------------------------------------------
*/
void CAbstractPen::FillTrack()
{
	ASSERT(m_pPenTrack);

	POSITION pos;
	pos = m_pPenTrack->GetHeadPosition();

	// ��С���
	int nInterval = m_nPenSize / 10;
	CPoint ptLast(0,0);
	// ��һ�λ��㲻�����
	BOOL	bFirst = TRUE;

	while (pos)
	{	
		CPoint& point = m_pPenTrack->GetNextPoint(pos);
		int x = point.x - ptLast.x;
		int y = point.y - ptLast.y;
		int dis = (int) (sqrt((float)x * x + y * y));						

		if (dis > nInterval || bFirst)
		{
			Apply(point);
			ptLast = point;
			bFirst = FALSE;
		}
	}
}


/*
*--------------------------------------------------------------------------------
*  ������: Apply
*  ����	 : ��ָ����������Ե�ǰ��Ч����
*  ����  : [in] CPoint& ptPoint		-	ָ���������
*  �㷨  : ί�и��ʼ���״����
*--------------------------------------------------------------------------------
*/
void CAbstractPen::Apply(const CPoint& ptPoint) const
{
	m_pPenNeb->Apply(ptPoint);
}
