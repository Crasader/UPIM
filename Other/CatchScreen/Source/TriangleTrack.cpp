/**
*   TriangleTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ���������ι켣��״���ߣ���ʼ�� m_ptTractStartPoint Ϊ�����ε����ĵ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/11   	 ʵ�� CTriangleTrack ��
*/

#include "stdafx.h"
#include "..\include\TriangleTrack.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTriangleTrack::CTriangleTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("������");
}

CTriangleTrack::~CTriangleTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: ���������ε����ĺ�һ���㣬����������
*  ����		:	CPoint &ptCenter	- �����ε����ĵ�����	
*				CPoint &ptBegin		- �����ε�һ����������
*  �㷨		: ���ȷ�һ��Բ���õ��������㣬�������߼���
*--------------------------------------------------------------------------------
*/
void CTriangleTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;
	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y)
	{
		// �����յ���ͬ���ͻ�һ����
		SetPixel(hDC, ptStart.x, ptEnd.y, TRACK_PEN_COLOR);
		return;
	}

	CPoint ptVertex[4];

	// ���ȷ�Բ���õ�������������
	SplitCircle(ptStart, ptEnd, 3, ptVertex);
	ptVertex[3] = ptVertex[0];

	// ��������
	MoveToEx(hDC, ptVertex[0].x, ptVertex[0].y, NULL);
	PolylineTo(hDC, ptVertex, 4);
}


/*
*--------------------------------------------------------------------------------
*  ������	: CreatePos
*  ����		: ������켣�����е�ļ��ϣ����浽�б���ȥ
*  ����		: VOID
*  �㷨		: �������ε������������ߣ��ܹ� LineDDA �����ó����еĹ켣������
*  ǰ������ : �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  �������� : �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CTriangleTrack::CreatePos()
{
	CPoint ptVertex[3];

	// ���ȷ�Բ���õ�������������
	SplitCircle(m_ptTrackStartPoint, m_ptTrackEndPoint, 3, ptVertex);
	
	// �����ε����������������ߣ����� LineDDA �õ�ÿһ���켣��

	// ��һ����
	if (ptVertex[0] == ptVertex[1])
	{
		AddPoint(ptVertex[0].x, ptVertex[0].y);
	}
	else
	{
		LineDDA(ptVertex[0].x, ptVertex[0].y, ptVertex[1].x, ptVertex[1].y, CTrack::AddPosToList, (LPARAM) this);		
	}

	// �ڶ�����
	if (ptVertex[1] == ptVertex[2])
	{
		AddPoint(ptVertex[1].x, ptVertex[1].y);
	}
	else
	{
		LineDDA(ptVertex[1].x, ptVertex[1].y, ptVertex[2].x, ptVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
	}

	// ��������
	if (ptVertex[2] == ptVertex[0])
	{
		AddPoint(ptVertex[2].x, ptVertex[2].y);
	}
	else
	{
		LineDDA(ptVertex[2].x, ptVertex[2].y, ptVertex[0].x, ptVertex[0].y, CTrack::AddPosToList, (LPARAM) this);
	}
	
	return TRUE;
}
