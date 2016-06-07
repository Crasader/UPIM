/**
*   Polygon.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ���������ι켣
*======================================================
*   �汾
*   Revision 1.0	2002/11/23    	 ���� CPolygon ��
*/
#if !defined(AFX_POLYGONTRACK_H__3C0A9CEB_C301_44FF_B85C_FD0932F78C39__INCLUDED_)
#define AFX_POLYGONTRACK_H__3C0A9CEB_C301_44FF_B85C_FD0932F78C39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CPolygonTrack
*˵�������������ι켣��
*�汾
*	Revision 1.0	2002/11/23     	 ���� CPolygonTrack ��
*/
class CPolygonTrack : public CTrack  
{
public:
	CPolygonTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CPolygonTrack();


protected:
	virtual BOOL CreatePos();
	void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_POLYGONTRACK_H__3C0A9CEB_C301_44FF_B85C_FD0932F78C39__INCLUDED_)
