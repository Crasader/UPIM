/**
*   Polygon.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   �����ι켣
*======================================================
*   �汾
*   Revision 1.0	2002/11/23    	 ʵ�� CPolygon ��
*/

#include "stdafx.h"
#include "..\INCLUDE\PolygonTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygonTrack::CPolygonTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
}

CPolygonTrack::~CPolygonTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: CreatePos
*  ����		: ������켣�����е�ļ��ϣ����浽�б���ȥ
*  �㷨		: �������ε����������������ߣ�ͨ�� LineDDA �����ó����еĹ켣������
*  ǰ������ : �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  �������� : �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CPolygonTrack::CreatePos()
{
	CPoint ptOutVertex[6];

	// ���ȷ�Բ���õ�������������
	SplitCircle(m_ptTrackStartPoint, m_ptTrackEndPoint, 6, ptOutVertex);

	// �������������ε�����������LineDDA���ÿ����
	LineDDA(ptOutVertex[0].x, ptOutVertex[0].y, ptOutVertex[1].x, ptOutVertex[1].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[1].x, ptOutVertex[1].y, ptOutVertex[2].x, ptOutVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[2].x, ptOutVertex[2].y, ptOutVertex[3].x, ptOutVertex[3].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[3].x, ptOutVertex[3].y, ptOutVertex[4].x, ptOutVertex[4].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[4].x, ptOutVertex[4].y, ptOutVertex[5].x, ptOutVertex[5].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[5].x, ptOutVertex[5].y, ptOutVertex[0].x, ptOutVertex[0].y, CTrack::AddPosToList, (LPARAM) this);

	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: ���������ε����ĺ�һ�����㣬����������
*  ����		:
*		CPoint &ptCenter	- �����ε����ĵ�����
*		CPoint &ptBegin		- �����ε�һ����������
*  �㷨		: ���ȷ�Բ�õ��������㣬���������Ӵ�������
*--------------------------------------------------------------------------------
*/
void CPolygonTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;

	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y)
	{
		// �����յ���ͬ���ͻ�һ����
		SetPixel(hDC, ptStart.x, ptEnd.y, TRACK_PEN_COLOR);
		return;
	}

	CPoint ptOutVertex[6];

	// ���ȷ�Բ���õ�������������
	SplitCircle(ptStart, ptEnd, 6, ptOutVertex);
	
	// ��������
	MoveToEx(hDC, ptOutVertex[0].x, ptOutVertex[0].y, NULL);
	LineTo(hDC, ptOutVertex[1].x, ptOutVertex[1].y);
	LineTo(hDC, ptOutVertex[2].x, ptOutVertex[2].y);
	LineTo(hDC, ptOutVertex[3].x, ptOutVertex[3].y);
	LineTo(hDC, ptOutVertex[4].x, ptOutVertex[4].y);
	LineTo(hDC, ptOutVertex[5].x, ptOutVertex[5].y);
	LineTo(hDC, ptOutVertex[0].x, ptOutVertex[0].y);
}