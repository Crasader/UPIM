/**
*  RectangleTrack.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2000-2001 . All Rights Reserved.
*   ������ι켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/12    	 ʵ�� CRectangleTrack ��
*/
#include "stdafx.h"
#include "..\Include\RectangleTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangleTrack::CRectangleTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("����");
}

CRectangleTrack::~CRectangleTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: ��������
*  ����		:	CPoint& ptStart	-	�������Ͻ�����
*				CPoint& ptEnd	-	�������½�����
*  �㷨		: ֱ�ӻ�����
*--------------------------------------------------------------------------------
*/
void CRectangleTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;
	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y)
	{
		// �����յ���ͬ���ͻ�һ����
		SetPixel(hDC, ptStart.x, ptEnd.y, TRACK_PEN_COLOR);
		return;
	}
	if (ptStart.y == ptEnd.y && ptStart.x == ptEnd.x)
	{
		// ˮƽ�߻��Ǵ�ֱ��
		MoveToEx(hDC, ptStart.x, ptEnd.y, NULL);
		LineTo(hDC, ptEnd.x, ptEnd.y);
	}
	else
	{
		Rectangle(hDC, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
}


/*
*--------------------------------------------------------------------------------
*  ������	: CreatePos
*  ����		: ������켣�����е�ļ��ϣ����浽�б���ȥ
*  ����		: VOID
*  �㷨		: ͨ�� LineDDA �����ó����еĹ켣������
*  ǰ������ : �����Ѿ��趨�˹켣��ʼ���������ֹ������
*  �������� : �� m_listTrackPoints �б��б������й켣�������
*--------------------------------------------------------------------------------
*/
BOOL CRectangleTrack::CreatePos()
{
	if (m_ptTrackStartPoint.y == m_ptTrackEndPoint.y && m_ptTrackStartPoint.x == m_ptTrackEndPoint.x)
	{
		// ˮƽ�߻��Ǵ�ֱ��
		LineDDA(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y, m_ptTrackEndPoint.x, m_ptTrackEndPoint.y, CTrack::AddPosToList, (LPARAM) this);
	}
	else
	{
		CPoint ptVertex[4];
		
		ptVertex[0] = m_ptTrackStartPoint;
		ptVertex[1].x = m_ptTrackEndPoint.x;
		ptVertex[1].y = m_ptTrackStartPoint.y;
		ptVertex[2] = m_ptTrackEndPoint;
		ptVertex[3].x = m_ptTrackStartPoint.x;
		ptVertex[3].y = m_ptTrackEndPoint.y;
				
		// �����ε��ĸ��������������� LineDDA �õ��켣��
		LineDDA(ptVertex[0].x, ptVertex[0].y, ptVertex[1].x, ptVertex[1].y, CTrack::AddPosToList, (LPARAM) this);
		LineDDA(ptVertex[1].x, ptVertex[1].y, ptVertex[2].x, ptVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
		LineDDA(ptVertex[2].x, ptVertex[2].y, ptVertex[3].x, ptVertex[3].y, CTrack::AddPosToList, (LPARAM) this);
		LineDDA(ptVertex[3].x, ptVertex[3].y, ptVertex[0].x, ptVertex[0].y, CTrack::AddPosToList, (LPARAM) this);
	}
	return TRUE;
}
