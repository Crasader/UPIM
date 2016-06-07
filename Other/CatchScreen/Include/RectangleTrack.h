/**
*  RectangleTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2000-2001 . All Rights Reserved.
*   ������μ���
*======================================================
*   �汾
*   Revision 1.0	2002/11/12     	 ���� CRectangleTrack ��
*/
#if !defined(AFX_RETANGETrack_H__BF4480B8_16B2_49A2_B730_2F351A0ECB0A__INCLUDED_)
#define AFX_RETANGETrack_H__BF4480B8_16B2_49A2_B730_2F351A0ECB0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CRectangleTrack
*˵����������ι켣��
*�汾
*	Revision 1.0	2002/11/12     	 ���� CRectangleTrack ��
*/
class CRectangleTrack : public CTrack  
{
public:
	CRectangleTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CRectangleTrack();


protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();

	// ������
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_RETANGETrack_H__BF4480B8_16B2_49A2_B730_2F351A0ECB0A__INCLUDED_)
