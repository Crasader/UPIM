/**
*  RandomTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2000-2001 . All Rights Reserved.
*   ��������켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/15     	 ���� CRandomTrack ��
*/

#if !defined(AFX_RANDOMTrack_H__AC1D78AA_7752_4B41_B980_83A89DAB6846__INCLUDED_)
#define AFX_RANDOMTrack_H__AC1D78AA_7752_4B41_B980_83A89DAB6846__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CRandomTrack
*˵������������켣��
*�汾
*	Revision 1.0	2002/11/15     	 ���� CRandomTrack ��
*/
class CRandomTrack : public CTrack  
{
public:
	CRandomTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CRandomTrack();


protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();

	// ��ֱ��
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_RANDOMTrack_H__AC1D78AA_7752_4B41_B980_83A89DAB6846__INCLUDED_)
