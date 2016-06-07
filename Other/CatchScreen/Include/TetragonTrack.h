/**
*  TetragonTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2000-2001 . All Rights Reserved.
*   �����Ľ��ǹ켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/12     	 ���� CTetragonTrack ��
*/
#if !defined(AFX_TETRAGONTrack_H__0192398C_2E22_4218_A64E_0E97D78B1DFA__INCLUDED_)
#define AFX_TETRAGONTrack_H__0192398C_2E22_4218_A64E_0E97D78B1DFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CRectangleTrack
*˵���������Ľ��ǹ켣��
*�汾
*	Revision 1.0	2002/11/12     	 ���� CTetragonTrack ��
*/
class CTetragonTrack : public CTrack  
{
public:
	CTetragonTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CTetragonTrack();


protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();
	// ���Ľ���
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_TETRAGONTrack_H__0192398C_2E22_4218_A64E_0E97D78B1DFA__INCLUDED_)
