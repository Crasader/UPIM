/**
*  RandomTrack.cpp
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2000-2001 . All Rights Reserved.
*   ʵ������켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/15     	 ʵ�� CRandomTrack ��
*/
#include "stdafx.h"
#include "..\Include\RandomTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRandomTrack::CRandomTrack(HDC hDC, COLORREF crTrackColor) : CTrack(hDC, crTrackColor)
{
	m_strTrackName = _T("����");
}


CRandomTrack::~CRandomTrack()
{

}


/*
*--------------------------------------------------------------------------------
*  ������	: Draw
*  ����		: ������Բ�켣
*  ����		: CPoint& ptStart	-	��Բ��Χ�������Ͻ�����
*			  CPoint& ptEnd	-	��Բ��Χ�������½�����
*  �㷨		: ����켣�����켣�㣬ֱ���ñʻ���
*--------------------------------------------------------------------------------
*/
void CRandomTrack::Draw(const CPoint &ptStart, const CPoint &ptEnd) const
{
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
BOOL CRandomTrack::CreatePos()
{
	// ��������ƶ��¼���ʱ����
	LineDDA(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y, m_ptTrackEndPoint.x, m_ptTrackEndPoint.y, CTrack::AddPosToList, (LPARAM) this);

	return TRUE;
}