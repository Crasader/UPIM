/**
*   PentagonTrack.cpp	
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ������ǹ켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/11  	 ʵ�� CPentagonTrack ��
*/
#include "stdafx.h"
#include "..\include\PentagonTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPentagonTrack::CPentagonTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("�����");
}

CPentagonTrack::~CPentagonTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: ������Բ�켣
*  ����		:
*		CPoint& ptStart	-	��Բ��Χ�������Ͻ�����
*		CPoint& ptEnd	-	��Բ��Χ�������½�����
*  �㷨		: ��ȷ�Բ�õ�������㣬���ɴ����Ľ������ߵõ�����ڲ�����
*--------------------------------------------------------------------------------
*/
void CPentagonTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;

	CPoint ptOutVertex[5], ptInnerVertex[5];

	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y)
	{
		// �����յ���ͬ���ͻ�һ����
		SetPixel(hDC, ptStart.x, ptEnd.y, TRACK_PEN_COLOR);
		return;
	}

	// ��ȷ�Բ���õ������������
	SplitCircle(ptStart, ptEnd, 5, ptOutVertex);
	
	// �õ���Բ���������
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[2], ptOutVertex[1], ptOutVertex[4], ptInnerVertex[0]);
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[2], ptOutVertex[1], ptOutVertex[3], ptInnerVertex[1]);
	GetIntersectPoint(ptOutVertex[1], ptOutVertex[3], ptOutVertex[2], ptOutVertex[4], ptInnerVertex[2]);
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[3], ptOutVertex[2], ptOutVertex[4], ptInnerVertex[3]);
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[3], ptOutVertex[1], ptOutVertex[4], ptInnerVertex[4]);
	
	// �������
	MoveToEx(hDC, ptOutVertex[0].x, ptOutVertex[0].y, NULL);
	LineTo(hDC, ptInnerVertex[0].x, ptInnerVertex[0].y);
	LineTo(hDC, ptOutVertex[1].x, ptOutVertex[1].y);
	LineTo(hDC, ptInnerVertex[1].x, ptInnerVertex[1].y);
	LineTo(hDC, ptOutVertex[2].x, ptOutVertex[2].y);
	LineTo(hDC, ptInnerVertex[2].x, ptInnerVertex[2].y);
	LineTo(hDC, ptOutVertex[3].x, ptOutVertex[3].y);
	LineTo(hDC, ptInnerVertex[3].x, ptInnerVertex[3].y);
	LineTo(hDC, ptOutVertex[4].x, ptOutVertex[4].y);
	LineTo(hDC, ptInnerVertex[4].x, ptInnerVertex[4].y);
	LineTo(hDC, ptOutVertex[0].x, ptOutVertex[0].y);

}


/*
*--------------------------------------------------------------------------------
*  ������	: CreatePos
*  ����		: ������켣�����е�ļ��ϣ����浽�б���ȥ
*  �㷨		: ������ǵ��ⲿ���������ڲ���������������ߣ�
*				�ܹ� LineDDA �����ó����еĹ켣������
*  ǰ������ : �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  �������� : �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CPentagonTrack::CreatePos()
{
	CPoint ptOutVertex[5], ptInnerVertex[5];

	// ��ȷ�Բ���õ������������
	SplitCircle(m_ptTrackStartPoint, m_ptTrackEndPoint, 5, ptOutVertex);

	// �õ���Բ���������
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[2], ptOutVertex[1], ptOutVertex[4], ptInnerVertex[0]);
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[2], ptOutVertex[1], ptOutVertex[3], ptInnerVertex[1]);
	GetIntersectPoint(ptOutVertex[1], ptOutVertex[3], ptOutVertex[2], ptOutVertex[4], ptInnerVertex[2]);
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[3], ptOutVertex[2], ptOutVertex[4], ptInnerVertex[3]);
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[3], ptOutVertex[1], ptOutVertex[4], ptInnerVertex[4]);

	// ������ǵ��ⲿ�嶥����ڲ��嶥������������ LineDDA �õ��켣��
	LineDDA(ptOutVertex[0].x, ptOutVertex[0].y, ptInnerVertex[0].x, ptInnerVertex[0].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[0].x, ptInnerVertex[0].y, ptOutVertex[1].x, ptOutVertex[1].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[1].x, ptOutVertex[1].y, ptInnerVertex[1].x, ptInnerVertex[1].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[1].x, ptInnerVertex[1].y, ptOutVertex[2].x, ptOutVertex[2].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[2].x, ptOutVertex[2].y, ptInnerVertex[2].x, ptInnerVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[2].x, ptInnerVertex[2].y, ptOutVertex[3].x, ptOutVertex[3].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[3].x, ptOutVertex[3].y, ptInnerVertex[3].x, ptInnerVertex[3].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[3].x, ptInnerVertex[3].y, ptOutVertex[4].x, ptOutVertex[4].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[4].x, ptOutVertex[4].y, ptInnerVertex[4].x, ptInnerVertex[4].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[4].x, ptInnerVertex[4].y, ptOutVertex[0].x, ptOutVertex[0].y, CTrack::AddPosToList, (LPARAM) this);
	
	return TRUE;
}