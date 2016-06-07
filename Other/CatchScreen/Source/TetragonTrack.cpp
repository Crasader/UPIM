/**
*  TetragonTrack.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2000-2001 . All Rights Reserved.
*   ʵ���Ľ��ǹ켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/12   	 ʵ�� CTetragonTrack ��
*/
#include "stdafx.h"
#include "..\include\TetragonTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTetragonTrack::CTetragonTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("�Ľ���");
}


CTetragonTrack::~CTetragonTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: �����Ľ��ǵ����ĺ�һ�����㣬�����Ľ���
*  ����		:	CPoint &ptCenter	- �Ľ��ǵ����ĵ�����	
*				CPoint &ptBegin		- �Ľ��ǵ�һ����������
*  �㷨		: ��Բ�ȷ�Ϊ12�ݣ������ĸ������໥���ߵõ��ĸ��ཻ�㼴�ڲ�����
*--------------------------------------------------------------------------------
*/
void CTetragonTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;
	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y)
	{
		// �����յ���ͬ���ͻ�һ����
		SetPixel(hDC, ptStart.x, ptEnd.y, TRACK_PEN_COLOR);
		return;
	}

	CPoint ptOutVertex[12], ptInnerVertex[4];

	// 12 �ȷ�Բ���õ� 12 ����������
	SplitCircle(ptStart, ptEnd, 12, ptOutVertex);
	
	// �õ��ڲ��ĸ�����
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[5], ptOutVertex[3], ptOutVertex[10], ptInnerVertex[0]);
	GetIntersectPoint(ptOutVertex[3], ptOutVertex[8], ptOutVertex[6], ptOutVertex[1], ptInnerVertex[1]);
	GetIntersectPoint(ptOutVertex[6], ptOutVertex[11], ptOutVertex[9], ptOutVertex[4], ptInnerVertex[2]);
	GetIntersectPoint(ptOutVertex[9], ptOutVertex[2], ptOutVertex[0], ptOutVertex[7], ptInnerVertex[3]);

	// ���Ľ���
	MoveToEx(hDC, ptOutVertex[0].x, ptOutVertex[0].y, NULL);
	LineTo(hDC, ptInnerVertex[0].x, ptInnerVertex[0].y);
	LineTo(hDC, ptOutVertex[3].x, ptOutVertex[3].y);
	LineTo(hDC, ptInnerVertex[1].x, ptInnerVertex[1].y);
	LineTo(hDC, ptOutVertex[6].x, ptOutVertex[6].y);
	LineTo(hDC, ptInnerVertex[2].x, ptInnerVertex[2].y);
	LineTo(hDC, ptOutVertex[9].x, ptOutVertex[9].y);
	LineTo(hDC, ptInnerVertex[3].x, ptInnerVertex[3].y);
	LineTo(hDC, ptOutVertex[0].x, ptOutVertex[0].y);
}


/*
*--------------------------------------------------------------------------------
*  ������	: CreatePos
*  ����		: ������켣�����е�ļ��ϣ����浽�б���ȥ
*  ����		: VOID
*  �㷨		: ���Ľ��ǵ��ⲿ�ĸ�������ڲ��ĸ������������ߣ�
*				ͨ�� LineDDA �����ó����еĹ켣������
*  ǰ������ : �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  �������� : �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CTetragonTrack::CreatePos()
{
	CPoint ptOutVertex[12], ptInnerVertex[4];

	// 12�ȷ�Բ���õ�12����������
	SplitCircle(m_ptTrackStartPoint, m_ptTrackEndPoint, 12, ptOutVertex);

	// �õ���Բ���ĸ�����
	GetIntersectPoint(ptOutVertex[0], ptOutVertex[5], ptOutVertex[3], ptOutVertex[10], ptInnerVertex[0]);
	GetIntersectPoint(ptOutVertex[3], ptOutVertex[8], ptOutVertex[6], ptOutVertex[1], ptInnerVertex[1]);
	GetIntersectPoint(ptOutVertex[6], ptOutVertex[11], ptOutVertex[9], ptOutVertex[4], ptInnerVertex[2]);
	GetIntersectPoint(ptOutVertex[9], ptOutVertex[2], ptOutVertex[0], ptOutVertex[7], ptInnerVertex[3]);

	// ���Ľ��ǵ��ⲿ�Ķ�����ڲ��Ķ������������� LineDDA �õ��켣��
	LineDDA(ptOutVertex[0].x, ptOutVertex[0].y, ptInnerVertex[0].x, ptInnerVertex[0].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[0].x, ptInnerVertex[0].y, ptOutVertex[3].x, ptOutVertex[3].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[3].x, ptOutVertex[3].y, ptInnerVertex[1].x, ptInnerVertex[1].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[1].x, ptInnerVertex[1].y, ptOutVertex[6].x, ptOutVertex[6].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[6].x, ptOutVertex[6].y, ptInnerVertex[2].x, ptInnerVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[2].x, ptInnerVertex[2].y, ptOutVertex[9].x, ptOutVertex[9].y, CTrack::AddPosToList, (LPARAM) this);

	LineDDA(ptOutVertex[9].x, ptOutVertex[9].y, ptInnerVertex[3].x, ptInnerVertex[3].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptInnerVertex[3].x, ptInnerVertex[3].y, ptOutVertex[0].x, ptOutVertex[0].y, CTrack::AddPosToList, (LPARAM) this);

	return TRUE;
}