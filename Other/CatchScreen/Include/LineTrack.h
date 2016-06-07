/**
*   EllipseTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����ֱ�߹켣
*======================================================
*   �汾
*   Revision 1.0	2002/11/11   	 ���� CLineTrack ��
*/
#if !defined(AFX_LINETrack_H__212CA942_F6EF_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_LINETrack_H__212CA942_F6EF_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"

/*
*����: CLineTrack
*˵��������ֱ�߹켣��
*�汾
*	Revision 1.0	2002/11/11    	 ���� CLineTrack ��
*/
class CLineTrack : public CTrack  
{
public:
	CLineTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CLineTrack();


protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();

	// ��ֱ��
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;

};

#endif // !defined(AFX_LINETrack_H__212CA942_F6EF_11D6_95DB_000795CFF65D__INCLUDED_)
