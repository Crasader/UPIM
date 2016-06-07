/**
*   EllipseTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ����Բ�ι켣
*======================================================
*   �汾
*   Revision 1.0	2002/11/11    	 ���� CLineTrack ��
*/
#include "stdafx.h"
#include "..\Include\LineTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineTrack::CLineTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("ֱ��");
}

CLineTrack::~CLineTrack()
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
void CLineTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
	HDC hDC = m_hDC;

	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y)
	{
		// �����յ���ͬ���ͻ�һ����
		SetPixel(hDC, ptStart.x, ptEnd.y, TRACK_PEN_COLOR);
		return;
	}

	MoveToEx(hDC, ptStart.x, ptStart.y, NULL);
	LineTo(hDC, ptEnd.x, ptEnd.y);
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
BOOL CLineTrack::CreatePos()
{
	// б��	
	LineDDA(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y, m_ptTrackEndPoint.x, m_ptTrackEndPoint.y, CTrack::AddPosToList, (LPARAM) this);

	return TRUE;
}