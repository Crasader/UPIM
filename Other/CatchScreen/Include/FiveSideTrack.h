/**
*   FiveSideTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002. All Rights Reserved.
*   ��������ι켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/11    	 ���� CFiveSideTrack ��
*/
#if !defined(AFX_FIVESIDETRACK_H__DAFA2005_F7A8_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_FIVESIDETRACK_H__DAFA2005_F7A8_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CFiveSideTrack
*˵������������ι켣��
*�汾
*	Revision 1.0	2002/11/11      ���� CFiveSideTrack ��
*/
class CFiveSideTrack : public CTrack  
{
public:
	CFiveSideTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CFiveSideTrack();


protected:
	virtual BOOL CreatePos();
	void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;

};

#endif // !defined(AFX_FIVESIDETRACK_H__DAFA2005_F7A8_11D6_95DB_000795CFF65D__INCLUDED_)
