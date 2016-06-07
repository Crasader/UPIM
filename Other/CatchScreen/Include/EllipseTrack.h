/**
*   EllipseTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002p. All Rights Reserved.
*   ������Բ�ι켣
*======================================================
*   �汾
*   Revision 1.0	2002/11/11  	 ���� CEllipseTrack ��
*/
#if !defined(AFX_ELLIPSETRACK_H__8E8BA802_F6E1_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_ELLIPSETRACK_H__8E8BA802_F6E1_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"

/*
*����: CEllipseTrack
*˵�������������Բ�켣��
*�汾
*	Revision 1.0	2002/11/11      ���� CEllipseTrack ��
*/
class CEllipseTrack : public CTrack  
{
public:
	CEllipseTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CEllipseTrack();


protected:
	void CalEllipsePath(int xCenter, int yCenter, int Rx, int Ry);
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();
	// ������
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_ELLIPSETRACK_H__8E8BA802_F6E1_11D6_95DB_000795CFF65D__INCLUDED_)
